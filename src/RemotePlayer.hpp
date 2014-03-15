#ifndef __REMOTEPLAYER_H
#define __REMOTEPLAYER_H

#include "OgrePlayer.hpp"
#include "PlayerAnimation.hpp"

#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>

#include <OgreBulletDynamicsRigidBody.h>
#include "Shapes/OgreBulletCollisionsBoxShape.h"

class RemotePlayer : public OgrePlayer{

	public:
		//Methods
		RemotePlayer(
			std::string name,
			OgreBulletDynamics::DynamicsWorld *world,
			BombManager *bombManager
		);
		~RemotePlayer();

		void generateGraphics();
		bool frameRenderingQueued(const Ogre::FrameEvent &evt);

		void win();
		void die();

	private:
		// Atributes
		PlayerAnimation *mPlayerAnimationState;
		double mBombCooldown;
};

#endif //__REMOTEPLAYER_H
