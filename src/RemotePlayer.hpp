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
			OgreBulletDynamics::DynamicsWorld *world
		);
		~RemotePlayer();

		void injectPlayerInput(NetworkMessage::PlayerInput *message);
		void generateGraphics();
		bool frameRenderingQueued(const Ogre::FrameEvent &evt);

};

#endif //__REMOTEPLAYER_H
