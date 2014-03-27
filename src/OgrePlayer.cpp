/*
This source file is part of pairOculus, a student project aiming at creating a
simple 3D multiplayer game for the Oculus Rift.

Repository can be found here : https://github.com/Target6/pairOculus

Copyright (c) 2013 Target6

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "OgrePlayer.hpp"

OgrePlayer::OgrePlayer(
	std::string name,
	OgreBulletDynamics::DynamicsWorld *world,
	BombManager* bombManager
):
	Player(name),
	mWorld(world),
	mBody(0),
	mBombManager(bombManager),
	mEntity(0),
	mAccelForward(0),
	mAccelBack(0),
	mAccelLeft(0),
	mAccelRight(0),
	mAccelUp(0),
	mAccelDown(0),
	mVelocity(Ogre::Vector3::ZERO),
	mGraphicsSetUp(false),
	mWasTeleported(false),
	mYawCorrection(0),
	mPitchCorrection(0),
	mRollCorrection(0),
	mPositionCorrection(Ogre::Vector3::ZERO),
	mBombCooldown(1),
	mBombCooldownLeft(0)
{
	mTopSpeed = 10;
}

void OgrePlayer::injectPlayerInput(NetworkMessage::PlayerInput *message){

	mYaw = message->getYaw();
	mPitch = message->getPitch();
	mRoll = message->getRoll();

	mX = message->getX();
	mY = message->getY();
	mZ = message->getZ();

	mGoingForward = message->getGoingForward();
	mGoingBack = message->getGoingBack();
	mGoingLeft = message->getGoingLeft();
	mGoingRight = message->getGoingRight();
	mGoingUp = message->getGoingUp();
	mGoingDown = message->getGoingDown();

	mPuttingBomb = message->getPuttingBomb();

	resetCorrection();

	mWasTeleported = true;

}

Ogre::Vector3 OgrePlayer::computeHitboxSize(){

	if(mEntity){
		Ogre::AxisAlignedBox boundingB = mEntity->getBoundingBox();
		Ogre::Vector3 size = boundingB.getSize();
		size /= 20;
		size.x /= 2;
		size.z /= 2;

		return size;
	}

	return Ogre::Vector3::ZERO;

}

void OgrePlayer::generateHitbox(
	Ogre::Vector3 size,
	Ogre::SceneNode *bodyNode
){

	using namespace OgreBulletCollisions;
	using namespace Ogre;

	BoxCollisionShape *boxShape = new BoxCollisionShape(size);
	mBody = new OgreBulletDynamics::RigidBody(mNickname + "Box", mWorld);

	Vector3 position(
		mX,
		mY,
		mZ
	);

	mBody->setShape(
		bodyNode,
		boxShape,
		0.6f,
		0.0f,
		50.0f,
		position
	);

	mBody->disableDeactivation();
	mBody->getBulletRigidBody()->setAngularFactor(btVector3(0, 0, 0));
	mBody->getBulletRigidBody()->setGravity(btVector3(0, -98.1 * 2, 0));

}

void OgrePlayer::computeAcceleration(){

	if(mGoingForward && mAccelForward < mTopAccel) mAccelForward += 1;
	else if(!mGoingForward && mAccelForward > 0) mAccelForward -= 1;

	if(mGoingLeft && mAccelLeft < mTopAccel) mAccelLeft += 1;
	else if(!mGoingLeft && mAccelLeft > 0) mAccelLeft -= 1;

	if(mGoingBack && mAccelBack < mTopAccel) mAccelBack += 1;
	else if(!mGoingBack && mAccelBack > 0) mAccelBack -= 1;

	if(mGoingRight && mAccelRight < mTopAccel) mAccelRight += 1;
	else if(!mGoingRight && mAccelRight > 0) mAccelRight -= 1;

	if(mGoingUp && mAccelUp < mTopAccel) mAccelUp += 1;
	else if(!mGoingUp && mAccelUp > 0) mAccelUp -= 1;

	if(mGoingDown && mAccelDown < mTopAccel) mAccelDown += 1;
	else if(!mGoingDown && mAccelDown > 0) mAccelDown -= 1;

}

void OgrePlayer::computeVelocity(const Ogre::FrameEvent &evt){

	mVelocity = Ogre::Vector3::ZERO;

	if(mGoingForward || mAccelForward)
		mVelocity += mAccelForward * getForwardDirection();
	if(mGoingLeft || mAccelLeft)
		mVelocity -= mAccelLeft * getRightDirection();
	if(mGoingBack || mAccelBack)
		mVelocity -= mAccelBack * getForwardDirection();
	if(mGoingRight || mAccelRight)
		mVelocity += mAccelRight * getRightDirection();

	//mVelocity.y = mBody->getLinearVelocity().y;

	if(mGoingUp || mAccelUp)
		mVelocity += mAccelUp * getUpDirection();
	if(mGoingDown || mAccelDown)
		mVelocity -= mAccelDown * getUpDirection();

}

void OgrePlayer::computeNodePosition(const Ogre::FrameEvent &evt){

	if(mWasTeleported){
		mWasTeleported = false;
	}
	else{

		if(mGraphicsSetUp){
			mX = mBody->getSceneNode()->getPosition().x;
			mY = mBody->getSceneNode()->getPosition().y;
			mZ = mBody->getSceneNode()->getPosition().z;
		}

		mX += mVelocity.x * evt.timeSinceLastFrame * mTopSpeed;
		mY += mVelocity.y * evt.timeSinceLastFrame * mTopSpeed;
		mZ += mVelocity.z * evt.timeSinceLastFrame * mTopSpeed;

		mYaw += mYawCorrection.valueDegrees();
		mPitch += mPitchCorrection.valueDegrees();
		mRoll += mRollCorrection.valueDegrees();

		mX += mPositionCorrection.x;
		mY += mPositionCorrection.y;
		mZ += mPositionCorrection.z;

	}

	if(mGraphicsSetUp){

		mBody->getBulletRigidBody()->proceedToTransform(
			btTransform(
				btQuaternion(Ogre::Degree(mYaw + 180).valueRadians(), 0, 0),
				btVector3(mX, mY, mZ)
			)
		);

		mBody->setLinearVelocity(Ogre::Vector3::ZERO);

	}

}

void OgrePlayer::handleBombCreation(const Ogre::FrameEvent &evt){

	mBombCooldownLeft -= evt.timeSinceLastFrame;

	if(mPuttingBomb && mBombCooldownLeft <= 0) {
		mBombManager->add(mNickname + "bomb", Ogre::Vector3(getX() ,getY() ,getZ()) + getForwardDirection());
		mBombCooldownLeft = mBombCooldown;
	}

}

void OgrePlayer::resetCorrection(){

	mYawCorrection = 0;
	mPitchCorrection = 0;
	mRollCorrection = 0;
	mPositionCorrection = Ogre::Vector3::ZERO;

}

Ogre::Vector3 OgrePlayer::getForwardDirection(){
	using namespace Ogre;
	return Quaternion(Degree(mYaw), Vector3::UNIT_Y) * Vector3::UNIT_Z * -1;
}

Ogre::Vector3 OgrePlayer::getUpDirection(){
	return Ogre::Vector3::UNIT_Y;
}

Ogre::Vector3 OgrePlayer::getRightDirection(){
	using namespace Ogre;
	return Quaternion(Degree(mYaw), Vector3::UNIT_Y) * Vector3::UNIT_X;
}
