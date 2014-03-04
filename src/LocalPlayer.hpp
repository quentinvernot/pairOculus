#ifndef __LOCALPLAYER_H
#define __LOCALPLAYER_H

#include "Player.hpp"
#include "CameraManager.hpp"
#include "NetworkMessage/PlayerInput.hpp"

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
		LocalPlayer(std::string name, CameraManager *cameraManager=0);
		~LocalPlayer();

		bool injectMouseMove(const OIS::MouseEvent &arg);
		bool injectMouseDown(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		bool injectMouseUp(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		bool injectKeyDown(const OIS::KeyEvent &arg);
		bool injectKeyUp(const OIS::KeyEvent &arg);
		void injectPlayerInput(NetworkMessage::PlayerInput *message);

		bool frameRenderingQueued(const Ogre::FrameEvent &evt);

		bool hadUsefulInput();

		Ogre::Vector3 getForwardDirection();
		Ogre::Vector3 getUpDirection();
		Ogre::Vector3 getRightDirection();

	private:
		//Attributes
		CameraManager *mCameraManager;

		int mAccelForward;
		int mAccelBack;
		int mAccelLeft;
		int mAccelRight;
		int mAccelUp;
		int mAccelDown;

		bool mInputWasUseful;

		Ogre::Degree mYawCorrection;
		Ogre::Degree mPitchCorrection;
		Ogre::Degree mRollCorrection;
		Ogre::Vector3 mPositionCorrection;

};

#endif //__LOCALPLAYER_H