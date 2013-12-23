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

class GameWindow{

	public:
		//Methods
		GameWindow();
		GameWindow(
			CameraManager *_cameraManager,
			Ogre::RenderWindow *_ogreWindow
		);
		~GameWindow();
		void switchViewMode();
		void setViewMode(Ogre::String mode);
		Ogre::RenderWindow *getWindow();

	private:
		//Methods
		void createSimpleViewport();
		void createOculusViewports();
		void destroyViewports();

		//Attributes
		CameraManager *cameraManager;
		Ogre::RenderWindow *ogreWindow;
		Ogre::String viewMode;

};

#endif //__GAMEWINDOW_H
