#ifndef __BOMBMANAGER_H
#define __BOMBMANAGER_H

#include "Bomb.hpp"
#include "ExplosionManager.hpp"
#include "ExplosionListener.hpp"

#include <deque>

#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreSceneManager.h>

class BombManager{

	public:
		//Methods
		BombManager(
			OgreBulletDynamics::DynamicsWorld *world,
			ExplosionManager *explosionManager
		);
		~BombManager();

		void add(
			std::string owner,
			Ogre::Vector3 position
		);
		void detonate(unsigned int i);

		void frameRenderingQueued();
		unsigned int size();
		Bomb *operator[](unsigned int i);

		void setExplosionListener(ExplosionListener *el);

	private:
		//Attributes
		OgreBulletDynamics::DynamicsWorld *mWorld;
		ExplosionManager *mExplosionManager;
		unsigned int mBombPlaced;
		std::deque<Bomb*> mNewBombs;
		std::deque<Bomb*> mActiveBombs;

		ExplosionListener *mExplosionListener;

};

#endif //__BOMBMANAGER_H
