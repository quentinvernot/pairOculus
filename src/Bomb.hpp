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

#ifndef __BOMB_HPP
#define __BOMB_HPP

#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreSceneManager.h>

#include <OgreBulletDynamicsRigidBody.h>
#include "Shapes/OgreBulletCollisionsSphereShape.h"

/// A bomb, with graphics and physics applied.
class Bomb{

	public:
		//Methods
		/// Constructor.
		Bomb(
			std::string owner,
			Ogre::Vector3 position,
			OgreBulletDynamics::DynamicsWorld *world
		);
		/// Destructor.
		~Bomb();

		/// Returns whether or not the timer is exhausted.
		bool hasExploded();
		/// Loads the bomb's model, displays it, and generates the hitbox.
		void generateGraphics();
		/// Detonates the bomb.
		void detonate();

		/// Injects the simulation time into the timer.
		void frameRenderingQueued(const Ogre::FrameEvent &evt);

		/// Returns the bomb's name.
		std::string getName();
		/// Returns the bomb's position.
		Ogre::Vector3 getPosition();
		/// Returns the bomb's range.
		int getRange();

	private:
		//Attributes
		/// The bomb's explosion range.
		int mRange;
		/// The bomb's time to live.
		double mTTL;
		/** The bomb's name
		 *  \remarks
		 *  	The name is used to give unique entities/nodes names.
		 */
		std::string mName;
		/// The bomb's position at it's creation.
		Ogre::Vector3 mPosition;

		/// The game's dynamics world.
		OgreBulletDynamics::DynamicsWorld *mWorld;
		/// The bomb's RigidBody.
		OgreBulletDynamics::RigidBody *mBody;

		/// Flag indicating whether or not the bobm's graphics were generated.
		bool mGraphicsSetUp;

};

#endif //__BOMB_HPP
