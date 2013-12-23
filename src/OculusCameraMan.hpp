#ifndef __OCULUSCAMERAMAN_H
#define __OCULUSCAMERAMAN_H

#include <OgreCamera.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

namespace OculusUtils{

	enum OculusCameraStyle   // enumerator values for different styles of camera movement
	{
		CS_FREELOOK,
		CS_FP,
		CS_TP,
		CS_ORBIT,
		CS_MANUAL
	};

	class OculusCameraMan{

		public:
			OculusCameraMan(Ogre::Camera* leftCam, Ogre::Camera* rightCam);
			virtual ~OculusCameraMan();
			virtual void setCameras(Ogre::Camera* leftCam, Ogre::Camera* rightCam);
			virtual void setLeftCamera(Ogre::Camera* cam);
			virtual void setRightCamera(Ogre::Camera* cam);
			virtual Ogre::Camera* getLeftCamera();
			virtual Ogre::Camera* getRightCamera();
			virtual void setTarget(Ogre::SceneNode* target);
			virtual Ogre::SceneNode* getTarget();
			virtual void setYawPitchDist(Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Real dist);
			virtual void setTopSpeed(Ogre::Real topSpeed);
			virtual Ogre::Real getTopSpeed();
			virtual void setStyle(OculusCameraStyle style);
			virtual OculusCameraStyle getStyle();
			virtual void manualStop();
			virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
			virtual void injectKeyDown(const OIS::KeyEvent& evt);
			virtual void injectKeyUp(const OIS::KeyEvent& evt);
			#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
			virtual void injectMouseMove(const OIS::MultiTouchEvent& evt);
			#else
			virtual void injectMouseMove(const OIS::MouseEvent& evt);
			#endif
			#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
			virtual void injectMouseDown(const OIS::MultiTouchEvent& evt);
			#else
			virtual void injectMouseDown(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
			#endif
			#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
			virtual void injectMouseUp(const OIS::MultiTouchEvent& evt);
			#else
			virtual void injectMouseUp(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
			#endif


		protected:

			Ogre::Camera *mLeftCamera;
			Ogre::Camera *mRightCamera;
			OculusCameraStyle mStyle;
			Ogre::SceneNode *mTarget;
			bool mOrbiting;
			bool mZooming;

			Ogre::Real mTopSpeed;
			Ogre::Real mTopAccel;
			Ogre::Vector3 mVelocity;

			bool mGoingForward;
			bool mGoingBack;
			bool mGoingLeft;
			bool mGoingRight;
			bool mGoingUp;
			bool mGoingDown;

			int mAccelForward;
			int mAccelBack;
			int mAccelLeft;
			int mAccelRight;
			int mAccelUp;
			int mAccelDown;

			bool mFastMove;

			Ogre::Radian mNodeYaw;
			Ogre::Radian mNodePitch;
			Ogre::Radian mNodeRoll;
			Ogre::Vector3 mNodePosition;
			Ogre::Vector3 mLeftCameraOffset;
			Ogre::Vector3 mRightCameraOffset;

	};

}

#endif // __OCULUSCAMERAMAN_H
