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

#ifndef __EXPLOSIONMANAGER_HPP
#define __EXPLOSIONMANAGER_HPP

#include "Explosion.hpp"

#include <deque>

#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreSceneManager.h>

class ExplosionManager{

	public:
		//Methods
		/// Constructor.
		ExplosionManager(OgreBulletDynamics::DynamicsWorld *world);
		/// Destructor.
		~ExplosionManager();

		/// Adds Explosions at the specified position.
		void add(std::string owner, Ogre::Vector3 position);
		/// Adapts the explosions velocities and deletes them when necessery.
		void frameRenderingQueued(const Ogre::FrameEvent &evt);

		/// Returns the current number of active Explosions.
		unsigned int size();
		Explosion *operator[](unsigned int i);

	private:
		//Attributes
		/// The Game's DynamicsWorld.
		OgreBulletDynamics::DynamicsWorld *mWorld;
		/// Amount of Explosions created when ExplosionManager::add is called.
		unsigned int mExplosionsPerDetonation;
		/// Number of Explosion created since the start.
		unsigned int mExplosionCreated;
		/// List of new Explosions, without graphics.
		std::deque<Explosion*> newExplosions;
		/// List of active Explosions.
		std::deque<Explosion*> activeExplosions;

};

#endif //__EXPLOSIONMANAGER_HPP
