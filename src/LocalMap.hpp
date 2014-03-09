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

	private:
		//Methodes
		void viewMap();

		//Attributes
		Ogre::SceneManager *mSceneMgr;
		OgreBulletDynamics::DynamicsWorld *mWorld;

};

#endif // LOCALMAP_H
