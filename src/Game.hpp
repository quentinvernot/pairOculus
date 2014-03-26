/*
This source file is part of pairOculus, a student project aiming at creating a
simple 3D multiplayer game for the Oculus Rift.

Repository can be found here : https://github.com/Target6/pairOculus

Copyright (c) 2013 Target6

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef __GAME_HPP
#define __GAME_HPP

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
#include "PlayerEventListener.hpp"
#include "BombManager.hpp"
#include "ExplosionManager.hpp"
#include "LocalMap.hpp"

#include "GameClient/Listener.hpp"

/** The main class. Handles the game function and logic.
 * 
 */
class Game : public Ogre::FrameListener, public PlayerEventListener{

	public:
		//Methods
		/// Constructor.
		Game(std::string nickname="Player 1", std::string address="");
		/// Destructor.
		~Game();

		/// Starts the game : launches the setup and starts rendering.
		void go();
		/// Signals the game to stop.
		void shutDown();

		/// Injects mouse move inputs into the game.
		bool injectMouseMove(const OIS::MouseEvent &arg);
		/// Injects mouse button down inputs into the game.
		bool injectMouseDown(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		/// Injects mouse button up inputs into the game.
		bool injectMouseUp(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		/// Injects keyboard key down inputs into the game.
		bool injectKeyDown(const OIS::KeyEvent &arg);
		/// Injects keyboard key up inputs into the game.
		bool injectKeyUp(const OIS::KeyEvent &arg);
		/// Injects sensor fusion head move inputs into the game.
		bool injectHeadMove(const Ogre::Vector3 &evt);

		/// Injects client close event into the game.
		void injectClientClose();
		/** Injects network JOINACCEPT message into the game.
		 *  Creates the LocalPlayer, fille the PlayerList and creates the
		 *  LocalMap.
		 *  Sets the mGameSetUp flag to true.
		 */
		void injectJoinAccept(NetworkMessage::JoinAccept *message);
		/// Injects network JOINREFUSE message into the game. Shuts down.
		void injectJoinRefuse(NetworkMessage::JoinRefuse *message);
		/// Injects network PLAYERJOINED message into the game.
		void injectPlayerJoined(NetworkMessage::PlayerJoined *message);
		/// Injects network PLAYERLEFT message into the game.
		void injectPlayerLeft(NetworkMessage::PlayerLeft *message);
		/// Injects network GAMESTART message into the game. Starts the game.
		void injectGameStart(NetworkMessage::GameStart *message);
		/// Injects network GAMEEND message into the game. Ends the game.
		void injectGameEnd(NetworkMessage::GameEnd *message);
		/// Injects network PLAYERINPUT message into the game.
		void injectPlayerInput(NetworkMessage::PlayerInput *message);
		/// Injects network PLAYERKILLED message into the game.
		void injectPlayerKilled(NetworkMessage::PlayerKilled *message);

		/** Method called when the local player receives a useful input.
		 *  Sends a PLAYERINPUT to the server accordingly.
		 */
		bool playerInput();
		/** Method called when the local player dies.
		 *  Sends a PLAYERKILLED to the server accordingly.
		 */
		bool playerDied();

	private:
		//Methods
		/**
		 *  Main setup : sets up Ogre, creates the listeners, sets up the game's
		 *  physics and either sets up the whole game in solo mode or connects 
		 *  to the server.
		 */
		bool setup();
		/// Chooses the SceneManager.
		void chooseSceneManager();
		/**
		 *  Shows the Ogre configuration dialog and starts the render window if
		 *  successful.
		 */
		bool configure();
		/**
		 *  Creates the network listeners, conects to the server, and send the 
		 *  Initial JOIN message.
		 */
		bool networkSetup();
		/// Sets up the whole game in offline mode.
		bool offlineSetup();
		/// Sets up bullet's physics, including the debug drawer.
		bool bulletSetup();

		/// Sets up the client's listeners.
		void createNetworkListener();
		/// Sets up the input listeners. 
		void createFrameListener();
		/** Creates the scene.
		 *  \remarks
		 *  	This generates the graphics and hitbox of previously inert items
		 *  	such as the LocalMap or the OgrePlayers.
		 */
		void createScene();
		/// Destroys the scene.
		void destroyScene();

		/// Sets up Ogre's ressources.
		void setupResources();
		/// Creates Ogre's ressource listeners.
		void createResourceListener();
		/// Loads Ogre's ressources (models, materials, etc...)
		void loadResources();

		/**
		 *  Method called as the next frame's rendering commands have been
		 *  issued to the GPU, but before uppdating the render window's buffer.
		 *  This method refreshes the inputs, calls every rendered items to 
		 *  allow them to move and checks if the game need to shut down.
		 * 
		 *  \return false if the game needs to shut down, true if it doesn't.
		 */
		bool frameRenderingQueued(const Ogre::FrameEvent &evt);

		//Attributes
		/// Ogre's root class.
		Ogre::Root *mOgreRoot;
		/// Ogre's ressource.cfg file path.
		Ogre::String mOgreResourcesCfg;
		/// Ogre's plugin.cfg file path.
		Ogre::String mOgrePluginsCfg;
		/// The game's scene manager.
		Ogre::SceneManager *mSceneMgr;

		/// The game's physics world.
		OgreBulletDynamics::DynamicsWorld *mWorld;
		/// The game's debugdrawer (outlines the hitboxes when active).
		OgreBulletCollisions::DebugDrawer *debugDrawer;

		/// The game's CameraManager.
		CameraManager *mCameraManager;
		/// The game's GameWindow.
		GameWindow *mGameWindow;
		/// The game's input manager.
		Input *mInput;

		/// The LocalPlayer's nickname.
		std::string mNickname;
		/// The LocalPlayer.
		LocalPlayer *mLocalPlayer;
		/// The game's player list.
		OgrePlayerList *mPlayerList;
		/// The game's BombManager.
		BombManager *mBombManager;
		/// The game's LocalMap.
		LocalMap *mLocalMap;

		/// The server's address.
		std::string mAddress;
		/// The server's port.
		std::string mPort;
		/// The game's NetworkMessageFactory.
		NetworkMessage::NetworkMessageFactory *mNMFactory;
		/// The game's client instance.
		GameClient::Listener *mGCListener;

		/// Flag indicating whether or not the game is in online mode.
		bool mOnlineMode;
		/// Flag indicating whether or not the game has connected to a server.
		bool mServerJoined;
		/// Flag indicating whether or not the game is set up.
		bool mGameSetUp;
		/// Flag indicating whether or not the game scene is created.
		bool mSceneCreated;
		/// Flag indicating whether or not the game is running.
		bool mGameRunning;
		/// Flag indicating whether or not the game is over.
		bool mGameEnded;
		/// Flag indicating whether or not the game is shutting down.
		bool mShutDownFlag;

};

#endif //__GAME_HPP
