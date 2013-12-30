#ifndef __CAMERAMANAGER_H
#define __CAMERAMANAGER_H

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include "SimpleCamera.hpp"
#include "OculusCamera.hpp"

class CameraManager{

	public:
		//Methods
		CameraManager(Ogre::SceneManager *_sceneMgr);
		~CameraManager();

		void move(const Ogre::Vector3 vec);
		void yaw(Ogre::Radian ang);
		void pitch(Ogre::Radian ang);
		void roll(Ogre::Radian ang);
		Ogre::Vector3 getDirection();
		Ogre::Vector3 getUp();
		Ogre::Vector3 getRight();

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

};

#endif //__CAMERAMANAGER_H
