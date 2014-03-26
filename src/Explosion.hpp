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

#ifndef __EXPLOSION_HPP
#define __EXPLOSION_HPP

#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreSceneManager.h>

#include <OgreBulletDynamicsRigidBody.h>
#include "Shapes/OgreBulletCollisionsSphereShape.h"

/** A harmless explosion 'particule' meant to disperse from a central point.
 *  This object has a 3D model and a hitbox and will bounce on walls and follow
 *  corridors. It has almost no mass and shouldn't interfere with other objects.
 *  It will travel a certain distance and should be destroyed after that.
 */
class Explosion{

	public:
		//Methods
		/// Constructor.
		Explosion(
			std::string owner,
			Ogre::Vector3 position,
			Ogre::Vector3 velocity,
			OgreBulletDynamics::DynamicsWorld *world
		);
		/// Destructor.
		~Explosion();

		/// Generates the explosion's graphics.
		void generateGraphics();
		/// Computes the remaining distance the object can travel.
		bool frameRenderingQueued(const Ogre::FrameEvent &evt);

		/// Returns the remaining distance until destruction.
		double getRange();

	private:
		//Attributes
		/// Distance left until destruction.
		double mRange;
		/// Entity's name.
		std::string mName;
		/// Position at creation.
		Ogre::Vector3 mPosition;
		/// Velocity vector (in units/s).
		Ogre::Vector3 mVelocity;

		/// The Game's DynamicsWorld.
		OgreBulletDynamics::DynamicsWorld *mWorld;
		/// The bomb's RigidBody.
		OgreBulletDynamics::RigidBody *mBody;

		/// Flag indicating whether or not the bobm's graphics were generated.
		bool mGraphicsSetUp;

};

#endif //__EXPLOSION_HPP
