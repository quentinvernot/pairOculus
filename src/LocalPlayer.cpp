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

#include "LocalPlayer.hpp"

LocalPlayer::LocalPlayer(
	std::string name,
	OgreBulletDynamics::DynamicsWorld *world,
	BombManager *bombManager,
	CameraManager *cameraManager
):
	OgrePlayer(name, world, bombManager),
	mCameraManager(cameraManager),
	mPlayerEventListener(0),
	mStartingTarget(Ogre::Vector3::ZERO),
	mHadUsefullInput(false)
{
}

LocalPlayer::~LocalPlayer(){
}

void LocalPlayer::generateGraphics(){

	if(mGraphicsSetUp)
		return;

	using namespace Ogre;

	mEntity = mWorld->getSceneManager()->createEntity("bomberman.mesh");
	mEntity->setCastShadows(true);
	Vector3 size = computeHitboxSize();

	SceneNode *bodyNode = mWorld->getSceneManager()->getRootSceneNode()->createChildSceneNode();

	generateHitbox(size, bodyNode);

	mGraphicsSetUp = true;

}

void LocalPlayer::lookAt(Ogre::Vector3 vec){

	mCameraManager->lookAt(vec);

	mYaw = mCameraManager->getOrientation().getYaw().valueDegrees();
	mPitch = mCameraManager->getOrientation().getPitch().valueDegrees();
	mRoll = mCameraManager->getOrientation().getRoll().valueDegrees();

	mStartingTarget = vec;

}

bool LocalPlayer::mouseMoved(const OIS::MouseEvent &arg){

	mYawCorrection += Ogre::Degree(-arg.state.X.rel * 0.15f);

	if(mCameraManager->getCameraMode() != OCULUS){

		mPitchCorrection += Ogre::Degree(-arg.state.Y.rel * 0.15f);
		if(
			(Ogre::Degree(mPitch) + mPitchCorrection).valueDegrees() < -90 ||
			(Ogre::Degree(mPitch) + mPitchCorrection).valueDegrees() > 90
		)
			mPitchCorrection = 0;

	}

	mHadUsefullInput = true;

	return true;

}

bool LocalPlayer::keyPressed(const OIS::KeyEvent &arg){

	if(mIsDead || mHasWon)
		return true;

	if (arg.key == OIS::KC_Z || arg.key == OIS::KC_UP)
		mGoingForward = true;
	else if (arg.key == OIS::KC_S || arg.key == OIS::KC_DOWN)
		mGoingBack = true;
	else if (arg.key == OIS::KC_Q || arg.key == OIS::KC_LEFT)
		mGoingLeft = true;
	else if (arg.key == OIS::KC_D || arg.key == OIS::KC_RIGHT)
		mGoingRight = true;
	else if (arg.key == OIS::KC_E || arg.key == OIS::KC_SPACE)
		mPuttingBomb = true;
	else if (arg.key == OIS::KC_PGUP)
		mGoingUp = true;
	else if (arg.key == OIS::KC_PGDOWN)
		mGoingDown = true;
	else if (arg.key == OIS::KC_LSHIFT)
		mFastMove = true;

	if(
		arg.key == OIS::KC_Z ||
		arg.key == OIS::KC_UP ||
		arg.key == OIS::KC_S ||
		arg.key == OIS::KC_DOWN ||
		arg.key == OIS::KC_Q ||
		arg.key == OIS::KC_LEFT ||
		arg.key == OIS::KC_D ||
		arg.key == OIS::KC_RIGHT ||
		arg.key == OIS::KC_E ||
		arg.key == OIS::KC_SPACE ||
		arg.key == OIS::KC_PGUP ||
		arg.key == OIS::KC_PGDOWN
	)
		mHadUsefullInput = true;

	return true;

}

bool LocalPlayer::keyReleased(const OIS::KeyEvent &arg){

	if(mIsDead || mHasWon)
		return true;

	if (arg.key == OIS::KC_Z || arg.key == OIS::KC_UP)
		mGoingForward = false;
	else if (arg.key == OIS::KC_S || arg.key == OIS::KC_DOWN)
		mGoingBack = false;
	else if (arg.key == OIS::KC_Q || arg.key == OIS::KC_LEFT)
		mGoingLeft = false;
	else if (arg.key == OIS::KC_D || arg.key == OIS::KC_RIGHT)
		mGoingRight = false;
	else if (arg.key == OIS::KC_E || arg.key == OIS::KC_SPACE)
		mPuttingBomb = false;
	else if (arg.key == OIS::KC_PGUP)
		mGoingUp = false;
	else if (arg.key == OIS::KC_PGDOWN)
		mGoingDown = false;
	else if (arg.key == OIS::KC_LSHIFT)
		mFastMove = false;

	if(
		arg.key == OIS::KC_Z ||
		arg.key == OIS::KC_UP ||
		arg.key == OIS::KC_S ||
		arg.key == OIS::KC_DOWN ||
		arg.key == OIS::KC_Q ||
		arg.key == OIS::KC_LEFT ||
		arg.key == OIS::KC_D ||
		arg.key == OIS::KC_RIGHT ||
		arg.key == OIS::KC_E ||
		arg.key == OIS::KC_SPACE ||
		arg.key == OIS::KC_PGUP ||
		arg.key == OIS::KC_PGDOWN
	)
		mHadUsefullInput = true;

	return true;

}

bool LocalPlayer::headMoved(const Ogre::Vector3 &evt){

	mYawCorrection += Ogre::Radian(evt.x);
	mPitchCorrection  += Ogre::Radian(evt.y);
	mRollCorrection += Ogre::Radian(evt.z);
	mHadUsefullInput = true;

	return true;

}

bool LocalPlayer::frameRenderingQueued(const Ogre::FrameEvent &evt){

	computeAcceleration();
	computeVelocity(evt);
	computeNodePosition(evt);

	handleBombCreation(evt);

	mCameraManager->setPosition(Ogre::Vector3(mX, mY + 0.7, mZ));

	mCameraManager->yaw(mYawCorrection);
	mCameraManager->pitch(mPitchCorrection);
	mCameraManager->roll(mRollCorrection);

	resetCorrection();

	if(mPlayerEventListener && mHadUsefullInput){
		mPlayerEventListener->playerInput();
		mHadUsefullInput = false;
	}

	return true;

}

void LocalPlayer::setPlayerEventListener(PlayerEventListener *pel){
	mPlayerEventListener = pel;
}

void LocalPlayer::win(){

	if(mIsDead)
		return;

	mHasWon = true;

	mGoingForward = false;
	mGoingBack = false;
	mGoingLeft = false;
	mGoingRight = false;
	mPuttingBomb = false;
	mGoingUp = false;
	mGoingDown = false;
	mFastMove = false;

	mX = mStartingX;
	mY = mStartingY + 10;
	mZ = mStartingZ;

	mWasTeleported = true;

	if(mPlayerEventListener)
		mPlayerEventListener->playerInput();

}

void LocalPlayer::die(){

	if(mHasWon)
		return;

	mIsDead = true;

	mGoingForward = false;
	mGoingBack = false;
	mGoingLeft = false;
	mGoingRight = false;
	mPuttingBomb = false;
	mGoingUp = false;
	mGoingDown = false;
	mFastMove = false;

	mX = mStartingX;
	mY = mStartingY + 10;
	mZ = mStartingZ;

	mWasTeleported = true;

	if(mPlayerEventListener){
		mPlayerEventListener->playerInput();
		mPlayerEventListener->playerDied();
	}

}
