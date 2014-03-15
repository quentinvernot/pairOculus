#include "LocalPlayer.hpp"

LocalPlayer::LocalPlayer(
	std::string name,
	OgreBulletDynamics::DynamicsWorld *world,
	BombManager *bombManager,
	CameraManager *cameraManager
):
	OgrePlayer(name, world, bombManager),
	mCameraManager(cameraManager),
	mBombCooldown(0),
	mPlayerEventListener(0)
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

bool LocalPlayer::injectMouseMove(const OIS::MouseEvent &arg){

	mYawCorrection += Ogre::Degree(-arg.state.X.rel * 0.15f);
	if(mCameraManager->getCameraMode() != "oculus")
		mPitchCorrection += Ogre::Degree(-arg.state.Y.rel * 0.15f);

	if(mPlayerEventListener)
		mPlayerEventListener->playerInput();

	return true;

}

bool LocalPlayer::injectMouseDown(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
	return true;
}

bool LocalPlayer::injectMouseUp(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
	return true;
}

bool LocalPlayer::injectKeyDown(const OIS::KeyEvent &arg){

	if(mIsDead || mHasWon)
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
		mPlayerEventListener &&
		(
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
	)
		mPlayerEventListener->playerInput();


	return true;

}

bool LocalPlayer::injectKeyUp(const OIS::KeyEvent &arg){

	if(mIsDead || mHasWon)
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
		mPlayerEventListener &&
		(
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
	)
		mPlayerEventListener->playerInput();

	return true;

}

bool LocalPlayer::injectHeadMove(const Ogre::Vector3 &evt){

	mYawCorrection += Ogre::Radian(evt.x);
	mPitchCorrection  += Ogre::Radian(evt.y);
	mRollCorrection += Ogre::Radian(evt.z);

	if(mPlayerEventListener)
		mPlayerEventListener->playerInput();

	return true;

}

bool LocalPlayer::frameRenderingQueued(const Ogre::FrameEvent &evt){

	computeAcceleration();
	computeVelocity(evt);
	computeNodePosition(evt);

	mBombCooldown -= evt.timeSinceLastFrame;

	if(mPuttingBomb && mBombCooldown <= 0) {
		mBombManager->add(mNickname + "bomb", Ogre::Vector3(getX() ,getY() ,getZ()) + getForwardDirection());
		mBombCooldown = 1;
	}

	mCameraManager->setPosition(
		Ogre::Vector3(mX, mY + 0.7, mZ)
	);

	mCameraManager->yaw(mYawCorrection);
	mCameraManager->pitch(mPitchCorrection);
	mCameraManager->roll(mRollCorrection);

	resetCorrection();

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
