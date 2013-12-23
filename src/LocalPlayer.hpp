#ifndef __LOCALPLAYER_H
#define __LOCALPLAYER_H

#include "Player.hpp"
#include "CameraManager.hpp"

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

class LocalPlayer : public Player{

	public:
		//Methods
		LocalPlayer(Ogre::String _name, CameraManager *_cameraManager);
		~LocalPlayer();

		bool injectMouseMoved(const OIS::MouseEvent &arg);
		bool injectMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		bool injectMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		bool injectKeyDown(const OIS::KeyEvent &arg);
		bool injectKeyUp(const OIS::KeyEvent &arg);

		bool frameRenderingQueued(const Ogre::FrameEvent &evt);

	private:
		//Attributes
		CameraManager *cameraManager;

};

#endif //__LOCALPLAYER_H
