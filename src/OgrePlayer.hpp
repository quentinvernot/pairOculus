/*
This source file is part of pairOculus, a student project aiming at creating a
simple 3D multiplayer game for the Oculus Rift.

Repository can be found here : https://github.com/Target6/pairOculus 

Copyright (c) 2013 Target6

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef __OGREPLAYER_HPP
#define __OGREPLAYER_HPP

#include "Player.hpp"
#include "BombManager.hpp"
#include "NetworkMessage/PlayerInput.hpp"

#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>

#include <OgreBulletDynamicsRigidBody.h>
#include "Shapes/OgreBulletCollisionsBoxShape.h"

/** Extension of Player adding the 3D representation, hitbox and movement logic.
 *  \remarks
 * 		This is a pure abstract class meant to be differentiated into a player 
 * 		controlled by a user on the local machine, and a player controlled by a 
 * 		user on another instance (i.e. on another machine).
 */
class OgrePlayer : public Player{

	public:
		//Methods
		/// Constructor.
		OgrePlayer(
			std::string name,
			OgreBulletDynamics::DynamicsWorld *world,
			BombManager *bombManager
		);
		/// Default destructor.
		virtual ~OgrePlayer(){};

		/// Treats inputs coming from another instance.
		void injectPlayerInput(NetworkMessage::PlayerInput *message);
		/** Should generate the Player's graphics.
		 *  Should load the Player's 3D model and generate the associated 
		 *  animations and hitbox.
		 */
		virtual void generateGraphics()=0;
		/// Should move the player at each frame and adapt the graphics.
		virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt)=0;

	protected:
		//Methods
		/// Computes the size of the hitbox of the player's 3D model.
		Ogre::Vector3 computeHitboxSize();
		/// Creates the hitbox.
		void generateHitbox(
			Ogre::Vector3 size,
			Ogre::SceneNode *bodyNode
		);

		/// Computes the acceleration in all directions.
		void computeAcceleration();
		/// Computes the velocity vector.
		void computeVelocity(const Ogre::FrameEvent &evt);
		/// Computes the player's position and moves it.
		void computeNodePosition(const Ogre::FrameEvent &evt);
		/// Handles the creation of a bomb.
		void handleBombCreation(const Ogre::FrameEvent &evt);
		/// Resets the correctors.
		void resetCorrection();

		/** Returns the forward direction vector on a flat plane.
		 *  Returns the vector representing the direction towards which the 
		 *  player is looking, projected on the x0z plane and normalized.
		 */
		Ogre::Vector3 getForwardDirection();
		/// Returns the up direction vector on a flat plane (always the Y axis).
		Ogre::Vector3 getUpDirection();
		/** Returns the right direction vector on a flat plane.
		 *  Returns the vector representing the player's right, projected on the
		 *  x0z plane and normalized.
		 */
		Ogre::Vector3 getRightDirection();

		//Attributes
		/// The game's DynamicsWorld
		OgreBulletDynamics::DynamicsWorld *mWorld;
		/// The player's body
		OgreBulletDynamics::RigidBody *mBody;

		/// The game's BombManager
		BombManager *mBombManager;

		/// The player model entity
		Ogre::Entity *mEntity;

		/// Current amount of forward momentum.
		double mAccelForward;
		/// Current amount of backward momentum.
		double mAccelBack;
		/// Current amount of leftward momentum.
		double mAccelLeft;
		/// Current amount of rightward momentum.
		double mAccelRight;
		/// Current amount of upward momentum.
		double mAccelUp;
		/// Current amount of downward momentum.
		double mAccelDown;

		/// Current velocity vector.
		Ogre::Vector3 mVelocity;

		/// Flag indicating whether or not the graphics have been set up.
		bool mGraphicsSetUp;
		/// Flag indicating whether or not the player was just teleported.
		bool mWasTeleported;

		/// Instant correction of the yaw.
		Ogre::Degree mYawCorrection;
		/// Instant correction of the pitch.
		Ogre::Degree mPitchCorrection;
		/// Instant correction of the roll.
		Ogre::Degree mRollCorrection;
		/// Instant correction of the player's position.
		Ogre::Vector3 mPositionCorrection;

		/// Time until the player can place the next bomb.
		double mBombCooldown;
		/// Current time left until the player can place the next bomb.
		double mBombCooldownLeft;

};

#endif //__OGREPLAYER_HPP
