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

#include "Explosion.hpp"

Explosion::Explosion(
	std::string name,
	Ogre::Vector3 position,
	Ogre::Vector3 velocity,
	OgreBulletDynamics::DynamicsWorld *world
):
	mRange(6),
	mName(name),
	mPosition(position),
	mVelocity(velocity),
	mWorld(world),
	mBody(0),
	mGraphicsSetUp(false)
{
}

Explosion::~Explosion(){
	mWorld->getSceneManager()->destroyEntity(mName + "ExplosionEntity");
	delete mBody;
}

void Explosion::generateGraphics(){

	if(mGraphicsSetUp)
		return;
	
	using namespace OgreBulletCollisions;
	using namespace Ogre;

	Ogre::SceneManager *sceneMgr = mWorld->getSceneManager();
	Entity *entity = sceneMgr->createEntity(mName + "ExplosionEntity", "sphere.mesh");
	entity->setMaterialName("Examples/Smoke");
	AxisAlignedBox boundingB = entity->getBoundingBox();
	Vector3 size = boundingB.getSize();
	size /= 40000;
	SceneNode *bodyNode = sceneMgr->getRootSceneNode()->createChildSceneNode(mName + "ExplosionBodyNode");
	SceneNode *entityNode = bodyNode->createChildSceneNode(mName + "ExplosionEntityNode");
	entityNode->attachObject(entity);
	entityNode->scale(0.0005, 0.0005, 0.0005);
	entityNode->setPosition(0, -size.x, 0);
	SphereCollisionShape *boxShape = new SphereCollisionShape(size.x);
	mBody = new OgreBulletDynamics::RigidBody(mName + "SphereExplosion", mWorld);

	mBody->setShape(
		bodyNode,
		boxShape,
		0.0f,
		0.0f,
		0.001f,
		mPosition
	);

	mBody->disableDeactivation();
	mBody->getBulletRigidBody()->setAngularFactor(1.0f);
	mBody->getBulletRigidBody()->setGravity(btVector3(0, 0, 0));
	mBody->setLinearVelocity(mVelocity);

	mGraphicsSetUp = true;

}

bool Explosion::frameRenderingQueued(const Ogre::FrameEvent &evt){

	mRange -= mVelocity.length() * evt.timeSinceLastFrame;
	return true;

}

double Explosion::getRange(){return mRange;}
