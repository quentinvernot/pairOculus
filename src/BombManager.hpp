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

#ifndef __BOMBMANAGER_HPP
#define __BOMBMANAGER_HPP

#include "Bomb.hpp"
#include "ExplosionManager.hpp"
#include "ExplosionListener.hpp"

#include <deque>

#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreSceneManager.h>

/** The Bomb's manager.
 *  Creates the Bombs and their graphics and injects the game time in their 
 *  timers at each frame. Also deletes the Bombs when their timer runs out.
 */
class BombManager{

	public:
		//Methods
		/// Constructor.
		BombManager(OgreBulletDynamics::DynamicsWorld *world);
		/// Destructor.
		~BombManager();

		/** Adds a new Bomb to the list.
		 *  \param owner : the name of the bomb's owner.
		 *  \param position : the Bomb's starting position.
		 */
		void add(
			std::string owner,
			Ogre::Vector3 position
		);

		/// Detonates the Bomb at the specified index.
		void detonate(unsigned int i);

		/// Generates the new Bombs graphics and injects the simulation time.
		void frameRenderingQueued(const Ogre::FrameEvent &evt);
		/// Returns the number of currently active Bombs.
		unsigned int size();
		Bomb *operator[](unsigned int i);

		/// Sets the ExplosionListener, it will be alerted when a Bomb explodes.
		void setExplosionListener(ExplosionListener *el);

	private:
		//Attributes
		/// The Game's DynamicsWorld.
		OgreBulletDynamics::DynamicsWorld *mWorld;
		/// The ExplosionManager.
		ExplosionManager *mExplosionManager;
		/// Number of placed Bombs since the start (active or not).
		unsigned int mBombPlaced;
		/// List of new Bombs, with no generated graphics.
		std::deque<Bomb*> mNewBombs;
		/// List of active Bombs.
		std::deque<Bomb*> mActiveBombs;

		/// The ExplosionListener.
		ExplosionListener *mExplosionListener;

};

#endif //__BOMBMANAGER_HPP
