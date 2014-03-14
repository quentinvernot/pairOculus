#ifndef __OGREPLAYER_H
#define __OGREPLAYER_H

#include "Player.hpp"
#include "BombManager.hpp"
#include "NetworkMessage/PlayerInput.hpp"

#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>

#include <OgreBulletDynamicsRigidBody.h>
#include "Shapes/OgreBulletCollisionsBoxShape.h"

class OgrePlayer : public Player{

	public:
		//Methods
		OgrePlayer(
			std::string name,
			OgreBulletDynamics::DynamicsWorld *world
		);
		virtual ~OgrePlayer(){};

		virtual void generateGraphics()=0;
		virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt)=0;

	protected:
		//Methods
		virtual Ogre::Vector3 computeHitboxSize();
		virtual void generateHitbox(
			Ogre::Vector3 size,
			Ogre::SceneNode *bodyNode
		);

		virtual void computeAcceleration();
		virtual void computeVelocity(const Ogre::FrameEvent &evt);
		virtual void computeNodePosition(const Ogre::FrameEvent &evt);
		virtual void resetCorrection();
		
		Ogre::Vector3 getForwardDirection();
		Ogre::Vector3 getUpDirection();
		Ogre::Vector3 getRightDirection();

		//Attributes
		OgreBulletDynamics::DynamicsWorld *mWorld;
		OgreBulletDynamics::RigidBody *mBody;

		Ogre::Entity *mEntity;

		int mAccelForward;
		int mAccelBack;
		int mAccelLeft;
		int mAccelRight;
		int mAccelUp;
		int mAccelDown;

		Ogre::Vector3 mVelocity;

		bool mGraphicsSetUp;
		bool mHadInputUseful;

		Ogre::Degree mYawCorrection;
		Ogre::Degree mPitchCorrection;
		Ogre::Degree mRollCorrection;
		Ogre::Vector3 mPositionCorrection;
		Ogre::Quaternion mOrientationCorrection;

};

#endif //__OGREPLAYER_H
