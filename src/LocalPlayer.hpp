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

#include <OgreBulletDynamicsRigidBody.h>
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h"
#include "Shapes/OgreBulletCollisionsBoxShape.h"

class LocalPlayer : public Player{

	public:
		//Methods
		LocalPlayer(
			std::string name,
			Ogre::SceneManager *sceneMgr,
			OgreBulletDynamics::DynamicsWorld *world,
			CameraManager *cameraManager=0
		);
		~LocalPlayer();

		void generateGraphics();

		bool injectMouseMove(const OIS::MouseEvent &arg);
		bool injectMouseDown(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		bool injectMouseUp(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		bool injectKeyDown(const OIS::KeyEvent &arg);
		bool injectKeyUp(const OIS::KeyEvent &arg);
		void injectPlayerInput(NetworkMessage::PlayerInput *message);

		bool frameRenderingQueued(const Ogre::FrameEvent &evt);

		bool hadUsefulInput();
		
		double getNodePositionX();
		double getNodePositionY();
		double getNodePositionZ();
		void setNodePositionX(double nodePositionX);
		void setNodePositionY(double nodePositionY);
		void setNodePositionZ(double nodePositionZ);

		Ogre::Vector3 getForwardDirection();
		Ogre::Vector3 getUpDirection();
		Ogre::Vector3 getRightDirection();

	private:
		//Attributes
		Ogre::SceneManager *mSceneMgr;
		OgreBulletDynamics::DynamicsWorld *mWorld;

		OgreBulletDynamics::RigidBody *mBody;

		CameraManager *mCameraManager;

		Ogre::Vector3 mPreviousVelocity;

		int mAccelForward;
		int mAccelBack;
		int mAccelLeft;
		int mAccelRight;
		int mAccelUp;
		int mAccelDown;

		bool mGraphicsSetUp;
		bool mHadInputUseful;

		Ogre::Degree mYawCorrection;
		Ogre::Degree mPitchCorrection;
		Ogre::Degree mRollCorrection;
		Ogre::Vector3 mPositionCorrection;

};

#endif //__LOCALPLAYER_H
