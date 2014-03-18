#ifndef __CAMERAMANAGER_H
#define __CAMERAMANAGER_H

#include <OgreCamera.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>

#include "SimpleCamera.hpp"
#include "OculusCamera.hpp"

class CameraManager{

	public:
		//Methods
		CameraManager(Ogre::SceneManager *sceneMgr);
		~CameraManager();

		void move(const Ogre::Vector3 vec);
		void yaw(Ogre::Radian ang);
		void pitch(Ogre::Radian ang);
		void roll(Ogre::Radian ang);

		void setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z);
		void setPosition(Ogre::Vector3 pos);
		Ogre::Quaternion getOrientation();
		void setOrientation(Ogre::Quaternion ori);
		void lookAt(Ogre::Vector3 vec);

		void increaseIPD();
		void decreaseIPD();

		Ogre::Vector3 getDirection();
		Ogre::Vector3 getUp();
		Ogre::Vector3 getRight();

		Ogre::Vector3 getForwardDirection();
		Ogre::Vector3 getUpDirection();
		Ogre::Vector3 getRightDirection();

		void switchCameraMode();
		Ogre::String getCameraMode();
		void setCameraMode(Ogre::String mode);

		Ogre::Camera *getCamera();
		Ogre::Camera *getOculusCameraLeft();
		Ogre::Camera *getOculusCameraRight();

	private:
		//Methods
		void createSimpleCamera();
		void createOculusCamera();
		void destroyCameras();

		//Arguments
		Ogre::SceneManager *mSceneMgr;
		Ogre::String mCameraMode;

		SimpleCamera *mSimpleCamera;
		OculusCamera *mOculusCamera;
		
		Ogre::Radian mNodeYaw;
		Ogre::Radian mNodePitch;
		Ogre::Radian mNodeRoll;
		Ogre::Vector3 mNodePosition;

};

#endif //__CAMERAMANAGER_H
