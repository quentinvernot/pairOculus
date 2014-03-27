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

#ifndef __LOCALPLAYER_HPP
#define __LOCALPLAYER_HPP

#include "OgrePlayer.hpp"
#include "CameraManager.hpp"
#include "PlayerEventListener.hpp"

#include "MouseMoveListener.hpp"
#include "KeyboardPressListener.hpp"
#include "KeyboardReleaseListener.hpp"
#include "HeadMoveListener.hpp"

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

/** Extension of OgrePlayer for a locally controlled player.
 * 	\remarks
 *  	This player takes its inputs from the mouse, keyboard and the Oculus 
 *  	Rift. It also manages the camera's position and orientation.
 */
class LocalPlayer : 
	public OgrePlayer,
	public MouseMoveListener,
	public KeyboardPressListener,
	public KeyboardReleaseListener,
	public HeadMoveListener
{

	public:
		//Methods
		/// Constructor
		LocalPlayer(
			std::string name,
			OgreBulletDynamics::DynamicsWorld *world,
			BombManager *bombManager,
			CameraManager *cameraManager
		);
		/// Destructor
		~LocalPlayer();

		/** Generates the Player's graphics.
		 *  Loads the Player's 3D model and generates the associated hitbox.
		 *  No model is displayed since the game uses a 1st person camera.
		 */
		void generateGraphics();

		/** Sets the orientation to look at the given coordinates.
		 *  \remarks 
		 * 		The target is stored.
		 */
		void lookAt(Ogre::Vector3 vec);

		/// Treats the mouse's movements.
		bool mouseMoved(const OIS::MouseEvent &arg);
		/// Treats the keyboard's pressed keys.
		bool keyPressed(const OIS::KeyEvent &arg);
		/// Treats the keyboard's released keys.
		bool keyReleased(const OIS::KeyEvent &arg);
		/// Treats the Oculus Rift's head move.
		bool headMoved(const Ogre::Vector3 &evt);

		/** Moves the player at each frame and adapt the graphics.
		 *  \remarks
		 * 		This also moves the camera.
		 */
		bool frameRenderingQueued(const Ogre::FrameEvent &evt);

		/// Sets the player's PlayerEventListener.
		void setPlayerEventListener(PlayerEventListener *pel);

		/** Sets the player as the winner and moves it to its starting position.
		 *  \remarks
		 * 		The player's movements are disabled.
		 */
		void win();
		/** Sets the player as dead and moves it to its starting position.
		 *  \remarks
		 * 		The player's movements are disabled.
		 */
		void die();

	private:
		//Attributes
		/// The game's CameraManager
		CameraManager *mCameraManager;
		/// The player's PlayerEventListener
		PlayerEventListener *mPlayerEventListener;
		/// The player's target when 'lookAt()' was last called.
		Ogre::Vector3 mStartingTarget;
		/// Indicating that a usefull input was recieved during the last frame.
		bool mHadUsefullInput;

};

#endif //__LOCALPLAYER_HPP
