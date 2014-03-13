#ifndef __LOCALPLAYER_H
#define __LOCALPLAYER_H

#include "OgrePlayer.hpp"
#include "CameraManager.hpp"

#include <OgreCamera.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <OgreBulletDynamicsRigidBody.h>
#include "Shapes/OgreBulletCollisionsBoxShape.h"

class LocalPlayer : public OgrePlayer{

	public:
		//Methods
		LocalPlayer(
			std::string name,
			OgreBulletDynamics::DynamicsWorld *world,
			CameraManager *cameraManager
		);
		~LocalPlayer();

		void generateGraphics();

		void lookAt(Ogre::Vector3 vec);

		bool injectMouseMove(const OIS::MouseEvent &arg);
		bool injectMouseDown(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		bool injectMouseUp(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		bool injectKeyDown(const OIS::KeyEvent &arg);
		bool injectKeyUp(const OIS::KeyEvent &arg);
		bool injectHeadMove(const Ogre::Vector3 &evt);

		bool frameRenderingQueued(const Ogre::FrameEvent &evt);

		bool hadUsefulInput();

	private:
		//Attributes
		CameraManager *mCameraManager;

};

#endif //__LOCALPLAYER_H
