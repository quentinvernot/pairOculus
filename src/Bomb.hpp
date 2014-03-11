#ifndef __BOMB_H
#define __BOMB_H

#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreSceneManager.h>

#include <OgreBulletDynamicsRigidBody.h>
#include "Shapes/OgreBulletCollisionsSphereShape.h"

class Bomb{

	public:
		//Methods
		Bomb(
			std::string owner,
			Ogre::Vector3 position,
			OgreBulletDynamics::DynamicsWorld *world
		);
		~Bomb();

		bool hasExploded(time_t now);
		void generateGraphics();

	private:
		//Attributes
		int mRange;
		int mTTL;
		clock_t mCreationTime;
		std::string mName;
		Ogre::Vector3 mPosition;

		OgreBulletDynamics::DynamicsWorld *mWorld;
		OgreBulletDynamics::RigidBody *mBody;

		bool mGraphicsSetUp;

};

#endif //__BOMB_H
