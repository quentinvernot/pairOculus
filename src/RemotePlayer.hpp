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

#ifndef __REMOTEPLAYER_HPP
#define __REMOTEPLAYER_HPP

#include "OgrePlayer.hpp"
#include "PlayerAnimation.hpp"

#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>

#include <OgreBulletDynamicsRigidBody.h>
#include "Shapes/OgreBulletCollisionsBoxShape.h"

/** Extension of OgrePlayer for a remotely controlled player.
 *  \remarks
 *  	This player takes its inputs from the network only.
 */
class RemotePlayer : public OgrePlayer{

	public:
		//Methods
		/// Constructor
		RemotePlayer(
			std::string name,
			OgreBulletDynamics::DynamicsWorld *world,
			BombManager *bombManager
		);
		/// Destructor
		~RemotePlayer();

		/** Generates the Player's graphics.
		 *  Loads the Player's 3D model and generates the associated hitbox.
		 *  Attaches the model to the body and creates the associated animations
		 */
		void generateGraphics();
		/// Moves the player at each frame and adapt the graphics.
		bool frameRenderingQueued(const Ogre::FrameEvent &evt);

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
		// Atributes
		/// The player's animations
		PlayerAnimation *mPlayerAnimationState;

};

#endif //__REMOTEPLAYER_HPP
