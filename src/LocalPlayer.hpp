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
		LocalPlayer(std::string name, CameraManager *cameraManager);
		~LocalPlayer();

		bool injectMouseMove(const OIS::MouseEvent &arg);
		bool injectMouseDown(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		bool injectMouseUp(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		bool injectKeyDown(const OIS::KeyEvent &arg);
		bool injectKeyUp(const OIS::KeyEvent &arg);

		bool frameRenderingQueued(const Ogre::FrameEvent &evt);

	private:
		//Attributes
		CameraManager *mCameraManager;

		int mAccelForward;
		int mAccelBack;
		int mAccelLeft;
		int mAccelRight;
		int mAccelUp;
		int mAccelDown;

};

#endif //__LOCALPLAYER_H
