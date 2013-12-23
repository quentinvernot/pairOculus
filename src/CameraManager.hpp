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

#include <SdkCameraMan.h>
#include "OculusCameraMan.hpp"

class CameraManager{

	public:
		//Methods
		CameraManager(Ogre::SceneManager *_sceneMgr);
		~CameraManager();

		void switchCameraMode();
		Ogre::String getCameraMode();
		void setCameraMode(Ogre::String mode);

		bool injectMouseMoved(const OIS::MouseEvent &arg);
		bool injectMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		bool injectMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		bool injectKeyDown(const OIS::KeyEvent &arg);
		bool injectKeyUp(const OIS::KeyEvent &arg);

		bool frameRenderingQueued(const Ogre::FrameEvent &evt);

		Ogre::Camera *getCamera();
		Ogre::Camera *getOculusCameraLeft();
		Ogre::Camera *getOculusCameraRight();

	private:
		//Methods
		void createCamera();
		void createOculusCamera();
		void destroyCameras();

		//Arguments
		Ogre::SceneManager *sceneMgr;
		Ogre::Camera *camera;
		Ogre::Camera *cameraLeft;
		Ogre::Camera *cameraRight;

		Ogre::String cameraMode;

		OgreBites::SdkCameraMan* cameraMan;
		OculusUtils::OculusCameraMan* oculusCameraMan;

};

#endif //__CAMERAMANAGER_H
