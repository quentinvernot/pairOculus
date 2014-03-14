#ifndef __EXPLOSION_H
#define __EXPLOSION_H

#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreSceneManager.h>

#include <OgreBulletDynamicsRigidBody.h>
#include "Shapes/OgreBulletCollisionsSphereShape.h"

class Explosion{

	public:
		//Methods
		Explosion(
			std::string owner,
			Ogre::Vector3 position,
			Ogre::Vector3 velocity,
			OgreBulletDynamics::DynamicsWorld *world
		);
		~Explosion();

		void generateGraphics();
		bool frameRenderingQueued(const Ogre::FrameEvent &evt);

		Ogre::Vector3 getPosition();
		double getRange();
		OgreBulletDynamics::RigidBody *getBody();

	private:
		//Attributes
		double mRange;
		std::string mName;
		Ogre::Vector3 mPosition;
		Ogre::Vector3 mVelocity;

		OgreBulletDynamics::DynamicsWorld *mWorld;
		OgreBulletDynamics::RigidBody *mBody;

		bool mGraphicsSetUp;

};

#endif //__EXPLOSION_H
