#include "LocalPlayer.hpp"

LocalPlayer::LocalPlayer(std::string name, CameraManager *cameraManager):
	Player(name),
	mCameraManager(cameraManager),
	mAccelForward(0),
	mAccelBack(0),
	mAccelLeft(0),
	mAccelRight(0),
	mAccelUp(0),
	mAccelDown(0),
	mHadInputUseful(false),
	mYawCorrection(0),
	mPitchCorrection(0),
	mRollCorrection(0),
	mPositionCorrection(Ogre::Vector3::ZERO)
{
}

LocalPlayer::~LocalPlayer(){
}

bool LocalPlayer::injectMouseMove(const OIS::MouseEvent &arg){

	mNodeYaw += (-arg.state.X.rel * 0.15f);
	mNodePitch += (-arg.state.Y.rel * 0.15f);
	//mNodeRoll = Ogre::Degree(-arg.state.Z.rel * 0.15f);

	if(mCameraManager){

		mCameraManager->yaw(mYawCorrection);
		mYawCorrection = 0;
		mCameraManager->pitch(mPitchCorrection);
		mPitchCorrection = 0;
		mCameraManager->roll(mRollCorrection);
		mRollCorrection = 0;

		mCameraManager->yaw(Ogre::Degree(-arg.state.X.rel * 0.15f));
		mCameraManager->pitch(Ogre::Degree(-arg.state.Y.rel * 0.15f));

	}
	
	mHadInputUseful = true;

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

	if(
		arg.key == OIS::KC_Z ||
		arg.key == OIS::KC_UP ||
		arg.key == OIS::KC_S ||
		arg.key == OIS::KC_DOWN ||
		arg.key == OIS::KC_Q ||
		arg.key == OIS::KC_LEFT ||
		arg.key == OIS::KC_D ||
		arg.key == OIS::KC_RIGHT ||
		arg.key == OIS::KC_PGUP ||
		arg.key == OIS::KC_PGDOWN
	)
		mHadInputUseful = true;

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

	if(
		arg.key == OIS::KC_Z ||
		arg.key == OIS::KC_UP ||
		arg.key == OIS::KC_S ||
		arg.key == OIS::KC_DOWN ||
		arg.key == OIS::KC_Q ||
		arg.key == OIS::KC_LEFT ||
		arg.key == OIS::KC_D ||
		arg.key == OIS::KC_RIGHT ||
		arg.key == OIS::KC_PGUP ||
		arg.key == OIS::KC_PGDOWN
	)
		mHadInputUseful = true;

	return true;

}

void LocalPlayer::injectPlayerInput(NetworkMessage::PlayerInput *message){

	if(mCameraManager){
		mYawCorrection += Ogre::Degree(message->getNodeYaw() - mNodeYaw);
		mPitchCorrection += Ogre::Degree(message->getNodePitch() - mNodePitch);
		mRollCorrection += Ogre::Degree(message->getNodeRoll() - mNodeRoll);
	}

	mNodeYaw = message->getNodeYaw();
	mNodePitch = message->getNodePitch();
	mNodeRoll = message->getNodeRoll();
	
	mPositionCorrection.x += message->getNodePositionX() - mNodePositionX;
	mPositionCorrection.y += message->getNodePositionY() - mNodePositionY;
	mPositionCorrection.z += message->getNodePositionZ() - mNodePositionZ;

	mNodePositionX = message->getNodePositionX();
	mNodePositionY = message->getNodePositionY();
	mNodePositionZ = message->getNodePositionZ();

	mGoingForward = message->getGoingForward();
	mGoingBack = message->getGoingBack();
	mGoingLeft = message->getGoingLeft();
	mGoingRight = message->getGoingRight();
	mGoingUp = message->getGoingUp();
	mGoingDown = message->getGoingDown();

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

	Ogre::Vector3 velocity = Ogre::Vector3::ZERO;

	if(mGoingForward || mAccelForward)
		velocity += mAccelForward * getForwardDirection() / mTopAccel;
	if(mGoingLeft || mAccelLeft)
		velocity -= mAccelLeft * getRightDirection() / mTopAccel;
	if(mGoingBack || mAccelBack)
		velocity -= mAccelBack * getForwardDirection() / mTopAccel;
	if(mGoingRight || mAccelRight)
		velocity += mAccelRight * getRightDirection() / mTopAccel;

	if(mGoingUp || mAccelUp)
		velocity += mAccelUp * getUpDirection()  / mTopAccel;
	if(mGoingDown || mAccelDown)
		velocity -= mAccelDown * getUpDirection()  / mTopAccel;

	if(mCameraManager){
		mCameraManager->move(mPositionCorrection);
		mPositionCorrection = Ogre::Vector3::ZERO;
		mCameraManager->move(velocity * evt.timeSinceLastFrame * mTopSpeed);
	}

	mNodePositionX += (velocity.x * evt.timeSinceLastFrame * mTopSpeed);
	mNodePositionY += (velocity.y * evt.timeSinceLastFrame * mTopSpeed);
	mNodePositionZ += (velocity.z * evt.timeSinceLastFrame * mTopSpeed);

	return true;

}

bool LocalPlayer::hadUsefulInput(){

	if(!mHadInputUseful)
		return false;
	
	mHadInputUseful = false;
	return true;

}

Ogre::Vector3 LocalPlayer::getForwardDirection(){
	using namespace Ogre;
	return Quaternion(Degree(mNodeYaw), Vector3::UNIT_Y) * Vector3::UNIT_Z * -1;
}

Ogre::Vector3 LocalPlayer::getUpDirection(){
	return Ogre::Vector3::UNIT_Y;
}

Ogre::Vector3 LocalPlayer::getRightDirection(){
	using namespace Ogre;
	return Quaternion(Degree(mNodeYaw), Vector3::UNIT_Y) * Vector3::UNIT_X;
}
