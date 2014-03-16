#ifndef __EXPLOSIONMANAGER_H
#define __EXPLOSIONMANAGER_H

#include "Explosion.hpp"

#include <deque>

#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreSceneManager.h>

class ExplosionManager{

	public:
		//Methods
		ExplosionManager(OgreBulletDynamics::DynamicsWorld *world);
		~ExplosionManager();

		void add(std::string owner, Ogre::Vector3 position);
		void frameRenderingQueued(const Ogre::FrameEvent &evt);

		unsigned int size();
		Explosion *operator[](unsigned int i);

	private:
		//Attributes
		OgreBulletDynamics::DynamicsWorld *mWorld;
		unsigned int mExplosionsPerDetonation;
		unsigned int mExplosionCreated;
		std::deque<Explosion*> newExplosions;
		std::deque<Explosion*> activeExplosions;

};

#endif //__EXPLOSIONMANAGER_H
