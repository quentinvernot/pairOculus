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
	mOrientationCorrection(Ogre::Quaternion::ZERO)
{
	mTopSpeed = 10;
}

void OgrePlayer::injectPlayerInput(NetworkMessage::PlayerInput *message){

	mYawCorrection += Ogre::Degree(message->getNodeYaw() - mNodeYaw);
	mPitchCorrection += Ogre::Degree(message->getNodePitch() - mNodePitch);
	mRollCorrection += Ogre::Degree(message->getNodeRoll() - mNodeRoll);

	mNodePositionX = message->getNodePositionX();
	mNodePositionY = message->getNodePositionY();
	mNodePositionZ = message->getNodePositionZ();

	mGoingForward = message->getGoingForward();
	mGoingBack = message->getGoingBack();
	mGoingLeft = message->getGoingLeft();
	mGoingRight = message->getGoingRight();
	mGoingUp = message->getGoingUp();
	mGoingDown = message->getGoingDown();

	mPuttingBomb = message->getPuttingBomb();

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
		mNodePositionX,
		mNodePositionY,
		mNodePositionZ
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
	mBody->getBulletRigidBody()->setGravity(btVector3(0, 0, 0));

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

	if(mGoingUp || mAccelUp)
		mVelocity += mAccelUp * getUpDirection();
	if(mGoingDown || mAccelDown)
		mVelocity -= mAccelDown * getUpDirection();

}

void OgrePlayer::computeNodePosition(const Ogre::FrameEvent &evt){

	if(mWasTeleported){
		mWasTeleported = false;
	}
	else if(mGraphicsSetUp){
		mNodePositionX = mBody->getSceneNode()->getPosition().x;
		mNodePositionY = mBody->getSceneNode()->getPosition().y;
		mNodePositionZ = mBody->getSceneNode()->getPosition().z;
	}

	mNodePositionX += mVelocity.x * evt.timeSinceLastFrame * mTopSpeed;
	mNodePositionY += mVelocity.y * evt.timeSinceLastFrame * mTopSpeed;
	mNodePositionZ += mVelocity.z * evt.timeSinceLastFrame * mTopSpeed;

	mNodeYaw += mYawCorrection.valueDegrees();
	mNodePitch += mPitchCorrection.valueDegrees();
	mNodeRoll += mRollCorrection.valueDegrees();

	mNodePositionX += mPositionCorrection.x;
	mNodePositionY += mPositionCorrection.y;
	mNodePositionZ += mPositionCorrection.z;

	if(mGraphicsSetUp){

		mBody->getBulletRigidBody()->proceedToTransform(
			btTransform(
				btQuaternion(Ogre::Degree(mNodeYaw + 180).valueRadians(), 0, 0),
				btVector3(mNodePositionX, mNodePositionY, mNodePositionZ)
			)
		);

		mBody->setLinearVelocity(Ogre::Vector3::ZERO);

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
	return Quaternion(Degree(mNodeYaw), Vector3::UNIT_Y) * Vector3::UNIT_Z * -1;
}

Ogre::Vector3 OgrePlayer::getUpDirection(){
	return Ogre::Vector3::UNIT_Y;
}

Ogre::Vector3 OgrePlayer::getRightDirection(){
	using namespace Ogre;
	return Quaternion(Degree(mNodeYaw), Vector3::UNIT_Y) * Vector3::UNIT_X;
}
