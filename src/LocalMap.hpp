#ifndef LOCALMAP_H
#define LOCALMAP_H

#include <OgreManualObject.h>

#include <OgreBulletDynamicsRigidBody.h>
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h"
#include "Shapes/OgreBulletCollisionsBoxShape.h"

#include "Map.hpp"
#include "FloorPanel.hpp"
#include "BlockFactory.hpp"

class LocalMap : public Map {

	public:
		LocalMap(
			Ogre::SceneManager *sceneMgr,
			OgreBulletDynamics::DynamicsWorld *world,
			unsigned int height,
			unsigned int width,
			time_t seed=time(0)
		);
		virtual ~LocalMap();

		void generate();

		Ogre::Vector3 getMapCenter();
		void createExplosion(Ogre::Vector3 pos, int range);

	private:
		//Methodes
		int getRow(Ogre::Vector3 pos);
		int getCol(Ogre::Vector3 pos);
		void viewMap();
		
		void destroyBlock(unsigned int i, unsigned int j);

		//Attributes
		Ogre::SceneManager *mSceneMgr;
		OgreBulletDynamics::DynamicsWorld *mWorld;
		OgreBulletDynamics::RigidBody ***mBodies;

};

#endif // LOCALMAP_H
