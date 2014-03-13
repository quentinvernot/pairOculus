#ifndef __OGREPLAYER_H
#define __OGREPLAYER_H

#include "Player.hpp"
#include "BombManager.hpp"
#include "NetworkMessage/PlayerInput.hpp"

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
		void injectPlayerInput(NetworkMessage::PlayerInput *message);
		virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt)=0;

		Ogre::Vector3 getForwardDirection();
		Ogre::Vector3 getUpDirection();
		Ogre::Vector3 getRightDirection();

	protected:
		//Attributes
		OgreBulletDynamics::DynamicsWorld *mWorld;
		OgreBulletDynamics::RigidBody *mBody;

		int mAccelForward;
		int mAccelBack;
		int mAccelLeft;
		int mAccelRight;
		int mAccelUp;
		int mAccelDown;

		bool mGraphicsSetUp;
		bool mHadInputUseful;

		Ogre::Degree mYawCorrection;
		Ogre::Degree mPitchCorrection;
		Ogre::Degree mRollCorrection;
		Ogre::Vector3 mPositionCorrection;
		Ogre::Quaternion mOrientationCorrection;

};

#endif //__OGREPLAYER_H
