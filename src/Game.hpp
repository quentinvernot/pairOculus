#ifndef __GAME_H
#define __GAME_H

#include <iostream>
#include <deque>

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

#include <OgreBulletDynamicsRigidBody.h>
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h"
#include "Shapes/OgreBulletCollisionsBoxShape.h"

#include "CameraManager.hpp"
#include "Input.hpp"
#include "GameWindow.hpp"

#include "LocalPlayer.hpp"
#include "RemotePlayer.hpp"
#include "OgrePlayerList.hpp"
#include "LocalMap.hpp"

#include "GameClient/Listener.hpp"

class Game : public Ogre::FrameListener{

	public:
		//Methods
		Game(std::string nickname, std::string address="", std::string port="");
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
		bool injectHeadMove(const Ogre::Vector3 &evt);
		void injectClientClose();
		void injectJoinAccept(NetworkMessage::JoinAccept *message);
		void injectJoinRefuse(NetworkMessage::JoinRefuse *message);
		void injectPlayerJoined(NetworkMessage::PlayerJoined *message);
		void injectPlayerLeft(NetworkMessage::PlayerLeft *message);
		void injectGameStart(NetworkMessage::GameStart *message);
		void injectGameEnd(NetworkMessage::GameEnd *message);
		void injectPlayerInput(NetworkMessage::PlayerInput *message);

	private:
		//Methods
		bool setup();
		void chooseSceneManager();
		bool configure();
		bool networkSetup();
		bool offlineSetup();
		bool bulletSetup();

		void createNetworkListener();
		void createFrameListener();
		void createScene();
		void destroyScene();

		void setupResources();
		void createResourceListener();
		void loadResources();

		bool frameRenderingQueued(const Ogre::FrameEvent &evt);

		void sendPlayerInput();

		//Attributes
		Ogre::Root *mOgreRoot;
		Ogre::String mOgreResourcesCfg;
		Ogre::String mOgrePluginsCfg;
		Ogre::SceneManager *mSceneMgr;

		OgreBulletDynamics::DynamicsWorld *mWorld;
		OgreBulletCollisions::DebugDrawer *debugDrawer;

		CameraManager *mCameraManager;
		GameWindow *mGameWindow;
		Input *mInput;

		std::string mNickname;
		LocalPlayer *mLocalPlayer;
		OgrePlayerList *mPlayerList;
		BombManager *mBombManager;
		LocalMap *mLocalMap;

		std::string mAddress;
		std::string mPort;
		NetworkMessage::NetworkMessageFactory *mNMFactory;
		GameClient::Listener *mGCListener;

		bool mOnlineMode;
		bool mServerJoined;
		bool mGameSetUp;
		bool mSceneCreated;
		bool mGameRunning;
		bool mShutDownFlag;

};

#endif //__GAME_H
