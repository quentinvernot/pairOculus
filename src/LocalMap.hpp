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

#ifndef LOCALMAP_H
#define LOCALMAP_H

#include <deque>

#include <OgreManualObject.h>

#include <OgreBulletDynamicsRigidBody.h>
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h"
#include "Shapes/OgreBulletCollisionsBoxShape.h"

#include "Map.hpp"
#include "FloorPanel.hpp"
#include "BlockFactory.hpp"
#include "BombManager.hpp"
#include "ExplosionListener.hpp"
#include "OgrePlayerList.hpp"

/**	Physical representation of the map
 */
class LocalMap : public Map, public ExplosionListener {

	public:
		/// Constructor
		LocalMap(
			OgreBulletDynamics::DynamicsWorld *world,
			OgrePlayerList *playerList,
			BombManager *bombManager,
			unsigned int height,
			unsigned int width,
			time_t seed=time(0)
		);
		/// Destructor
		virtual ~LocalMap();

		///	Generate the map's graphics and physics
		void generate();

		/// Get the center of the map
		Ogre::Vector3 getMapCenter();
		/// Create an explosion
		bool bombExploded(Ogre::Vector3 position, int range);
		/// Add map's stuff to render for next frame
		void frameRenderingQueued(const Ogre::FrameEvent &evt);

	private:
		//Methodes
		/// Get the row associated to a position
		int getRow(Ogre::Vector3 pos);
		/// Get the col associated to a position
		int getCol(Ogre::Vector3 pos);

		/// When there is an explosion destruct all objects in range
		void createExplosion(Ogre::Vector3 pos, int range);
		/// Destroy a block and show an animation
		void destroyBlock(unsigned int i, unsigned int j);
		/// Kill player and detonate bomb in the cell
		void searchAndDestroyObjects(int row, int col);

		//Attributes
		/// World view by bullet
		OgreBulletDynamics::DynamicsWorld *mWorld;
		/// Bullet's bodies
		OgreBulletDynamics::RigidBody ***mBodies;
		/// The PlayerList
		OgrePlayerList *mPlayerList;
		/// The Game's BombManager
		BombManager *mBombManager;

		/// List of curently crumbling blocks
		std::deque<Ogre::SceneNode *> mCrumblingBlocks;

};

#endif // LOCALMAP_H
