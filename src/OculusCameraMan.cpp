#include "OculusCameraMan.hpp"

namespace OculusUtils{

	OculusCameraMan::OculusCameraMan(Ogre::Camera *leftCam, Ogre::Camera *rightCam):
		mLeftCamera(0),
		mRightCamera(0),
		mTarget(0),
		mOrbiting(false),
		mZooming(false),
		mTopSpeed(30),
		mTopAccel(10),
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
		mNodePosition(0,0,50),
		mLeftCameraOffset(-0.32, 0.5, -0.5),
		mRightCameraOffset(0.32, 0.5, -0.5)
	{

		setLeftCamera(leftCam);
		setRightCamera(rightCam);
		setStyle(CS_FREELOOK);

		mLeftCamera->setPosition(mNodePosition);
		mLeftCamera->move(mLeftCameraOffset);
		mRightCamera->setPosition(mNodePosition);
		mRightCamera->move(mRightCameraOffset);

	}

	OculusCameraMan::~OculusCameraMan() {}

	/*-----------------------------------------------------------------------------
	| Swaps the camera on our camera man for another camera.
	-----------------------------------------------------------------------------*/
	void OculusCameraMan::setCameras(Ogre::Camera *leftCam, Ogre::Camera *rightCam){
		mLeftCamera = leftCam;
		mRightCamera = rightCam;
	}

	void OculusCameraMan::setLeftCamera(Ogre::Camera *cam){
		mLeftCamera = cam;
	}

	void OculusCameraMan::setRightCamera(Ogre::Camera *cam){
		mRightCamera = cam;
	}

	Ogre::Camera *OculusCameraMan::getLeftCamera(){
		return mLeftCamera;
	}

	Ogre::Camera *OculusCameraMan::getRightCamera(){
		return mRightCamera;
	}

	/*-----------------------------------------------------------------------------
	| Sets the target we will revolve around. Only applies for orbit style.
	-----------------------------------------------------------------------------*/
	void OculusCameraMan::setTarget(Ogre::SceneNode *target){

		if (target != mTarget){

			mTarget = target;

			if(target){
				setYawPitchDist(Ogre::Degree(0), Ogre::Degree(15), 150);
				mLeftCamera->setAutoTracking(true, mTarget);
			}
			else
				mLeftCamera->setAutoTracking(false);

		}

	}

	Ogre::SceneNode* OculusCameraMan::getTarget(){
		return mTarget;
	}

	/*-----------------------------------------------------------------------------
	| Sets the spatial offset from the target. Only applies for orbit style.
	-----------------------------------------------------------------------------*/
	void OculusCameraMan::setYawPitchDist(Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Real dist){
		mLeftCamera->setPosition(mTarget->_getDerivedPosition());
		mLeftCamera->setOrientation(mTarget->_getDerivedOrientation());
		mLeftCamera->yaw(yaw);
		mLeftCamera->pitch(-pitch);
		mLeftCamera->moveRelative(Ogre::Vector3(0, 0, dist));
	}

	/*-----------------------------------------------------------------------------
	| Sets the camera's top speed. Only applies for free-look style.
	-----------------------------------------------------------------------------*/
	void OculusCameraMan::setTopSpeed(Ogre::Real topSpeed){
		mTopSpeed = topSpeed;
	}

	Ogre::Real OculusCameraMan::getTopSpeed(){
		return mTopSpeed;
	}

	/*-----------------------------------------------------------------------------
	| Sets the movement style of our camera man.
	-----------------------------------------------------------------------------*/
	void OculusCameraMan::setStyle(OculusCameraStyle style){

		if (mStyle != CS_ORBIT && style == CS_ORBIT){

			setTarget(mTarget ? mTarget : mLeftCamera->getSceneManager()->getRootSceneNode());
			mLeftCamera->setFixedYawAxis(true);
			manualStop();
			setYawPitchDist(Ogre::Degree(0), Ogre::Degree(15), 150);

		}
		else if (mStyle != CS_FREELOOK && style == CS_FREELOOK){
			mLeftCamera->setAutoTracking(false);
			mLeftCamera->setFixedYawAxis(true);
		}
		else if (mStyle != CS_FP && style == CS_FP){
			mLeftCamera->setAutoTracking(false);
			mLeftCamera->setFixedYawAxis(true);
		}
		else if (mStyle != CS_MANUAL && style == CS_MANUAL){
			mLeftCamera->setAutoTracking(false);
			manualStop();
		}

		mStyle = style;

	}

	OculusCameraStyle OculusCameraMan::getStyle(){
		return mStyle;
	}

	/*-----------------------------------------------------------------------------
	| Manually stops the camera when in free-look mode.
	-----------------------------------------------------------------------------*/
	void OculusCameraMan::manualStop(){

		if (mStyle == CS_FREELOOK){
			mGoingForward = false;
			mGoingBack = false;
			mGoingLeft = false;
			mGoingRight = false;
			mGoingUp = false;
			mGoingDown = false;
			mVelocity = Ogre::Vector3::ZERO;
		}

	}

	bool OculusCameraMan::frameRenderingQueued(const Ogre::FrameEvent &evt){

		if (mStyle == CS_FREELOOK){

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

			if(mGoingForward || mAccelForward) mVelocity += mAccelForward * mLeftCamera->getDirection() / mTopAccel;
			if(mGoingLeft || mAccelLeft) mVelocity -= mAccelLeft * mLeftCamera->getRight() / mTopAccel;
			if(mGoingBack || mAccelBack) mVelocity -= mAccelBack * mLeftCamera->getDirection() / mTopAccel;
			if(mGoingRight || mAccelRight) mVelocity += mAccelRight * mLeftCamera->getRight() / mTopAccel;

			mVelocity.y = 0;

			if(mGoingUp || mAccelUp) mVelocity += mAccelUp * Ogre::Vector3::UNIT_Y  / mTopAccel;
			if(mGoingDown || mAccelDown) mVelocity -= mAccelDown * Ogre::Vector3::UNIT_Y  / mTopAccel;

			mLeftCamera->move(mVelocity * evt.timeSinceLastFrame * mTopSpeed);
			mRightCamera->move(mVelocity * evt.timeSinceLastFrame * mTopSpeed);

			mNodePosition += (mVelocity * evt.timeSinceLastFrame * mTopSpeed);

		}
		return true;

	}

	/*-----------------------------------------------------------------------------
	| Processes key presses for free-look style movement.
	-----------------------------------------------------------------------------*/
	void OculusCameraMan::injectKeyDown(const OIS::KeyEvent &evt){

		if (mStyle == CS_FREELOOK){

			if (evt.key == OIS::KC_Z || evt.key == OIS::KC_UP) mGoingForward = true;
			else if (evt.key == OIS::KC_S || evt.key == OIS::KC_DOWN) mGoingBack = true;
			else if (evt.key == OIS::KC_Q || evt.key == OIS::KC_LEFT) mGoingLeft = true;
			else if (evt.key == OIS::KC_D || evt.key == OIS::KC_RIGHT) mGoingRight = true;
			else if (evt.key == OIS::KC_PGUP) mGoingUp = true;
			else if (evt.key == OIS::KC_PGDOWN) mGoingDown = true;
			else if (evt.key == OIS::KC_LSHIFT) mFastMove = true;

		}

	}

	/*-----------------------------------------------------------------------------
	| Processes key releases for free-look style movement.
	-----------------------------------------------------------------------------*/
	void OculusCameraMan::injectKeyUp(const OIS::KeyEvent &evt){

		if (mStyle == CS_FREELOOK){

			if (evt.key == OIS::KC_Z || evt.key == OIS::KC_UP) mGoingForward = false;
			else if (evt.key == OIS::KC_S || evt.key == OIS::KC_DOWN) mGoingBack = false;
			else if (evt.key == OIS::KC_Q || evt.key == OIS::KC_LEFT) mGoingLeft = false;
			else if (evt.key == OIS::KC_D || evt.key == OIS::KC_RIGHT) mGoingRight = false;
			else if (evt.key == OIS::KC_PGUP) mGoingUp = false;
			else if (evt.key == OIS::KC_PGDOWN) mGoingDown = false;
			else if (evt.key == OIS::KC_LSHIFT) mFastMove = false;

		}

	}

	/*-----------------------------------------------------------------------------
	| Processes mouse movement differently for each style.
	-----------------------------------------------------------------------------*/
	#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
	void OculusCameraMan::injectMouseMove(const OIS::MultiTouchEvent &evt)
	#else
	void OculusCameraMan::injectMouseMove(const OIS::MouseEvent &evt)
	#endif
	{

		if (mStyle == CS_ORBIT){

			Ogre::Real dist = (mLeftCamera->getPosition() - mTarget->_getDerivedPosition()).length();

			if (mOrbiting){   // yaw around the target, and pitch locally

				mLeftCamera->setPosition(mTarget->_getDerivedPosition());

				mLeftCamera->yaw(Ogre::Degree(-evt.state.X.rel * 0.25f));
				mLeftCamera->pitch(Ogre::Degree(-evt.state.Y.rel * 0.25f));

				mLeftCamera->moveRelative(Ogre::Vector3(0, 0, dist));

				// don't let the camera go over the top or around the bottom of the target
			}
			else if (mZooming)  // move the camera toward or away from the target
				// the further the camera is, the faster it moves
				mLeftCamera->moveRelative(Ogre::Vector3(0, 0, evt.state.Y.rel * 0.004f * dist));
			else if (evt.state.Z.rel != 0)  // move the camera toward or away from the target
				// the further the camera is, the faster it moves
				mLeftCamera->moveRelative(Ogre::Vector3(0, 0, -evt.state.Z.rel * 0.0008f * dist));

		}
		else if (mStyle == CS_FREELOOK){

			mNodeYaw = Ogre::Degree(-evt.state.X.rel * 0.15f);
			mNodePitch = Ogre::Degree(-evt.state.Y.rel * 0.15f);
			//mNodeRoll = Ogre::Degree(-evt.state.Z.rel * 0.15f);

			mLeftCamera->yaw(mNodeYaw);
			mLeftCamera->pitch(mNodePitch);

			mRightCamera->yaw(mNodeYaw);
			mRightCamera->pitch(mNodePitch);

			mLeftCameraOffset =
				Ogre::Quaternion(
					Ogre::Degree(mNodeYaw),
					Ogre::Vector3::UNIT_Y
				) * mLeftCameraOffset;

			mRightCameraOffset =
				Ogre::Quaternion(
					Ogre::Degree(mNodeYaw),
					Ogre::Vector3::UNIT_Y
				) * mRightCameraOffset;

			mLeftCameraOffset =
				Ogre::Quaternion(
					Ogre::Degree(mNodePitch),
					Ogre::Vector3::UNIT_X
				) * mLeftCameraOffset;

			mRightCameraOffset =
				Ogre::Quaternion(
					Ogre::Degree(mNodePitch),
					Ogre::Vector3::UNIT_X
				) * mRightCameraOffset;

			mLeftCamera->setPosition(mNodePosition);
			mLeftCamera->move(mLeftCameraOffset);
			mRightCamera->setPosition(mNodePosition);
			mRightCamera->move(mRightCameraOffset);

			//mNodePosition += (mVelocity * evt.timeSinceLastFrame * mTopSpeed);


		}

	}

	/*-----------------------------------------------------------------------------
	| Processes mouse presses. Only applies for orbit style.
	| Left button is for orbiting, and right button is for zooming.
	-----------------------------------------------------------------------------*/
	#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
	void OculusCameraMan::injectMouseDown(const OIS::MultiTouchEvent &evt){

		if (mStyle == CS_ORBIT)
			mOrbiting = true;

	}
	#else
	void OculusCameraMan::injectMouseDown(const OIS::MouseEvent &evt, OIS::MouseButtonID id){

		if (mStyle == CS_ORBIT){
			if (id == OIS::MB_Left) mOrbiting = true;
			else if (id == OIS::MB_Right) mZooming = true;
		}

	}
	#endif

	/*-----------------------------------------------------------------------------
	| Processes mouse releases. Only applies for orbit style.
	| Left button is for orbiting, and right button is for zooming.
	-----------------------------------------------------------------------------*/
	#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
	void OculusCameraMan::injectMouseUp(const OIS::MultiTouchEvent &evt){

		if (mStyle == CS_ORBIT)
			mOrbiting = false;

	}
	#else
	void OculusCameraMan::injectMouseUp(const OIS::MouseEvent &evt, OIS::MouseButtonID id){

		if (mStyle == CS_ORBIT){
			if (id == OIS::MB_Left) mOrbiting = false;
			else if (id == OIS::MB_Right) mZooming = false;
		}

	}
	#endif
}
