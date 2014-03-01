#ifndef __GAMEWINDOW_H
#define __GAMEWINDOW_H

#include "CameraManager.hpp"

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreCompositorManager.h>

#include <OISEvents.h>
#include <OISKeyboard.h>

class GameWindow{

	public:
		//Methods
		GameWindow();
		GameWindow(
			CameraManager *cameraManager,
			Ogre::RenderWindow *ogreWindow
		);
		~GameWindow();
		void switchViewMode();
		void setViewMode(Ogre::String mode);
		Ogre::RenderWindow *getWindow();
		
		bool injectKeyDown(const OIS::KeyEvent &arg);

	private:
		//Methods
		void createSimpleViewport();
		void createOculusViewports();
		void destroyViewports();

		//Attributes
		CameraManager *mCameraManager;
		Ogre::RenderWindow *mOgreWindow;
		Ogre::String mViewMode;

};

#endif //__GAMEWINDOW_H
