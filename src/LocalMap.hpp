#ifndef LOCALMAP_H
#define LOCALMAP_H

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

class LocalMap : public Map, public ExplosionListener {

	public:
		LocalMap(
			OgreBulletDynamics::DynamicsWorld *world,
			OgrePlayerList *playerList,
			BombManager *bombManager,
			unsigned int height,
			unsigned int width,
			time_t seed=time(0)
		);
		virtual ~LocalMap();

		void generate();

		Ogre::Vector3 getMapCenter();
		bool bombExploded(Ogre::Vector3 position, int range);

	private:
		//Methodes
		int getRow(Ogre::Vector3 pos);
		int getCol(Ogre::Vector3 pos);
		void viewMap();

		void createExplosion(Ogre::Vector3 pos, int range);
		void destroyBlock(unsigned int i, unsigned int j);
		void searchAndDestroyObjects(int row, int col);

		//Attributes
		OgreBulletDynamics::DynamicsWorld *mWorld;
		OgreBulletDynamics::RigidBody ***mBodies;
		OgrePlayerList *mPlayerList;
		BombManager *mBombManager;

};

#endif // LOCALMAP_H
