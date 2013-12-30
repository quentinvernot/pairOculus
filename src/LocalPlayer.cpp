#include "LocalPlayer.hpp"

LocalPlayer::LocalPlayer(Ogre::String name, CameraManager *cameraManager):
	mTopSpeed(300),
	mTopAccel(100),
	mVelocity(Ogre::Vector3::ZERO),
	mGoingForward(false),
	mGoingBack(false),
	mGoingLeft(false),
	mGoingRight(false),
	mGoingUp(false),
	mGoingDown(false),
	mAccelForward(0),
	mAccelBack(0),
	mAccelLeft(0),
	mAccelRight(0),
	mAccelUp(0),
	mAccelDown(0),
	mFastMove(false),
	mNodeYaw(0),
	mNodePitch(0),
	mNodeRoll(0),
	mNodePosition(0,0,50)
{

	mName = name;
	mCameraManager = cameraManager;

}

LocalPlayer::~LocalPlayer(){
}

bool LocalPlayer::injectMouseMove(const OIS::MouseEvent &arg){

	mNodeYaw = Ogre::Degree(-arg.state.X.rel * 0.15f);
	mNodePitch = Ogre::Degree(-arg.state.Y.rel * 0.15f);
	//mNodeRoll = Ogre::Degree(-arg.state.Z.rel * 0.15f);

	mCameraManager->yaw(mNodeYaw);
	mCameraManager->pitch(mNodePitch);

	return true;

}

bool LocalPlayer::injectMouseDown(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
	return true;
}

bool LocalPlayer::injectMouseUp(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
	return true;
}

bool LocalPlayer::injectKeyDown(const OIS::KeyEvent &arg){

	if (arg.key == OIS::KC_Z || arg.key == OIS::KC_UP)
		mGoingForward = true;
	else if (arg.key == OIS::KC_S || arg.key == OIS::KC_DOWN)
		mGoingBack = true;
	else if (arg.key == OIS::KC_Q || arg.key == OIS::KC_LEFT)
		mGoingLeft = true;
	else if (arg.key == OIS::KC_D || arg.key == OIS::KC_RIGHT)
		mGoingRight = true;
	else if (arg.key == OIS::KC_PGUP)
		mGoingUp = true;
	else if (arg.key == OIS::KC_PGDOWN)
		mGoingDown = true;
	else if (arg.key == OIS::KC_LSHIFT)
		mFastMove = true;

	return true;

}

bool LocalPlayer::injectKeyUp(const OIS::KeyEvent &arg){

	if (arg.key == OIS::KC_Z || arg.key == OIS::KC_UP)
		mGoingForward = false;
	else if (arg.key == OIS::KC_S || arg.key == OIS::KC_DOWN)
		mGoingBack = false;
	else if (arg.key == OIS::KC_Q || arg.key == OIS::KC_LEFT)
		mGoingLeft = false;
	else if (arg.key == OIS::KC_D || arg.key == OIS::KC_RIGHT)
		mGoingRight = false;
	else if (arg.key == OIS::KC_PGUP)
		mGoingUp = false;
	else if (arg.key == OIS::KC_PGDOWN)
		mGoingDown = false;
	else if (arg.key == OIS::KC_LSHIFT)
		mFastMove = false;

	return true;

}

bool LocalPlayer::frameRenderingQueued(const Ogre::FrameEvent &evt){

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

	Ogre::Vector3 mVelocity = Ogre::Vector3::ZERO;

	if(mGoingForward || mAccelForward)
		mVelocity += mAccelForward * mCameraManager->getDirection() / mTopAccel;
	if(mGoingLeft || mAccelLeft)
		mVelocity -= mAccelLeft * mCameraManager->getRight() / mTopAccel;
	if(mGoingBack || mAccelBack)
		mVelocity -= mAccelBack * mCameraManager->getDirection() / mTopAccel;
	if(mGoingRight || mAccelRight)
		mVelocity += mAccelRight * mCameraManager->getRight() / mTopAccel;

	mVelocity.y = 0;

	if(mGoingUp || mAccelUp)
		mVelocity += mAccelUp * Ogre::Vector3::UNIT_Y  / mTopAccel;
	if(mGoingDown || mAccelDown)
		mVelocity -= mAccelDown * Ogre::Vector3::UNIT_Y  / mTopAccel;

	mCameraManager->move(mVelocity * evt.timeSinceLastFrame * mTopSpeed);

	mNodePosition += (mVelocity * evt.timeSinceLastFrame * mTopSpeed);

	return true;

}
