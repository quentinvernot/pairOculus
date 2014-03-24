/*
This source file is part of pairOculus, a student project aiming at creating a
simple 3D multiplayer game for the Oculus Rift.

Repository can be found here : https://github.com/Target6/pairOculus

Copyright (c) 2013 Zykino

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

#ifndef PLAYERANIMATION_H
#define PLAYERANIMATION_H

#include <OgreEntity.h>
#include <OgreSceneManager.h>

/** Animations for the players.
 * Set the player's animations up.
 */
class PlayerAnimation {
	public:
		// Methodes
		/// Constructor.
		PlayerAnimation (Ogre::SceneManager *sceneMgr, Ogre::Entity *entity);
		/// Default destructor.
		~PlayerAnimation ();

		// Setup
		/// Set the head rotate animation up.
		void setupHeadAnimation ();
		/// Set the run animation up.
		void setupRunAnimation ();
		/// Set the idle animation up.
		void setupIdleAnimation ();

		// Enable/disable Animations
		/// Stop all the animations applied to the player.
		void stopAnimation ();
		/// Apply the idle position.
		void doIdleAnimation ();
		/// Apply the head animation.
		void doHeadAnimation ();
		/// Apply the run animation.
		void doRunAnimation ();
		/// Get the player's animation state.
		Ogre::AnimationState *getPlayerAnimationState();
	private:
		//Attributes
		/// The game's SceneManager
		Ogre::SceneManager *mSceneMgr;
		/// The player's body
		Ogre::Entity *mEntity;

		/// The player's animation state
		Ogre::AnimationState *mPlayerAnimationState;
};
#endif /* PLAYERANIMATION_H */
