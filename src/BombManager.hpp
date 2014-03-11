#ifndef __BOMBMANAGER_H
#define __BOMBMANAGER_H

#include "Bomb.hpp"
#include "LocalMap.hpp"

#include <deque>

#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreSceneManager.h>

class BombManager{

	public:
		//Methods
		BombManager(
			OgreBulletDynamics::DynamicsWorld *world,
			LocalMap *map
		);
		~BombManager();

		void add(
			std::string owner,
			Ogre::Vector3 position
		);
		void frameRenderingQueued();

	private:
		//Attributes
		OgreBulletDynamics::DynamicsWorld *mWorld;
		LocalMap *mMap;
		unsigned int mBombPlaced;
		std::deque<Bomb*> newBombs;
		std::deque<Bomb*> activeBombs;

};

#endif //__BOMBMANAGER_H
