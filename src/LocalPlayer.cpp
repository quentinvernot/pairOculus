#include "LocalPlayer.hpp"

LocalPlayer::LocalPlayer(std::string name, CameraManager *cameraManager):
	Player(name),
	mCameraManager(cameraManager),
	mAccelForward(0),
	mAccelBack(0),
	mAccelLeft(0),
	mAccelRight(0),
	mAccelUp(0),
	mAccelDown(0)
{
}

LocalPlayer::~LocalPlayer(){
}

bool LocalPlayer::injectMouseMove(const OIS::MouseEvent &arg){

	mNodeYaw = (-arg.state.X.rel * 0.15f);
	mNodePitch = (-arg.state.Y.rel * 0.15f);
	//mNodeRoll = Ogre::Degree(-arg.state.Z.rel * 0.15f);

	mCameraManager->yaw(Ogre::Degree(mNodeYaw));
	mCameraManager->pitch(Ogre::Degree(mNodePitch));

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
		mVelocity += mAccelForward * mCameraManager->getForwardDirection() / mTopAccel;
	if(mGoingLeft || mAccelLeft)
		mVelocity -= mAccelLeft * mCameraManager->getRightDirection() / mTopAccel;
	if(mGoingBack || mAccelBack)
		mVelocity -= mAccelBack * mCameraManager->getForwardDirection() / mTopAccel;
	if(mGoingRight || mAccelRight)
		mVelocity += mAccelRight * mCameraManager->getRightDirection() / mTopAccel;

	if(mGoingUp || mAccelUp)
		mVelocity += mAccelUp * mCameraManager->getUpDirection()  / mTopAccel;
	if(mGoingDown || mAccelDown)
		mVelocity -= mAccelDown * mCameraManager->getUpDirection()  / mTopAccel;

	mCameraManager->move(mVelocity * evt.timeSinceLastFrame * mTopSpeed);

	mNodePositionX += (mVelocity.x * evt.timeSinceLastFrame * mTopSpeed);
	mNodePositionY += (mVelocity.y * evt.timeSinceLastFrame * mTopSpeed);
	mNodePositionZ += (mVelocity.z * evt.timeSinceLastFrame * mTopSpeed);

	return true;

}
