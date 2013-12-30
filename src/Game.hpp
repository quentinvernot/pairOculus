#ifndef __GAME_H
#define __GAME_H

#include <iostream>

#include <boost/bind.hpp>
#include <boost/function.hpp>

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

#include "CameraManager.hpp"
#include "LocalPlayer.hpp"
#include "Input.hpp"
#include "GameWindow.hpp"

class Game : public Ogre::FrameListener{

	public:
		//Methods
		Game();
		~Game();

		void go();
		void shutDown();

		bool injectMouseMove(const OIS::MouseEvent &arg);
		bool injectMouseDown(
			const OIS::MouseEvent &arg, OIS::MouseButtonID id
		);
		bool injectMouseUp(
			const OIS::MouseEvent &arg, OIS::MouseButtonID id
		);
		bool injectKeyDown(const OIS::KeyEvent &arg);
		bool injectKeyUp(const OIS::KeyEvent &arg);

	private:
		//Methods
		bool setup();
		bool configure();
		void chooseSceneManager();

		void createFrameListener();
		void createScene();
		void destroyScene();

		void setupResources();
		void createResourceListener();
		void loadResources();

		bool frameRenderingQueued(const Ogre::FrameEvent &evt);

		//Attributes
		Ogre::Root *ogreRoot;
		Ogre::String ogreResourcesCfg;
		Ogre::String ogrePluginsCfg;
		Ogre::SceneManager *sceneMgr;

		CameraManager *cameraManager;
		LocalPlayer *localPlayer;
		GameWindow *gameWindow;
		Input *input;

		bool shutDownFlag;

};

#endif //__GAME_H
