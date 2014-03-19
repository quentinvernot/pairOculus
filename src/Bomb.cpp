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

#include "Bomb.hpp"

Bomb::Bomb(
	std::string name,
	Ogre::Vector3 position,
	OgreBulletDynamics::DynamicsWorld *world
):
	mRange(3),
	mTTL(3),
	mName(name),
	mPosition(position),
	mWorld(world),
	mBody(0),
	mGraphicsSetUp(false)
{
}

Bomb::~Bomb(){
	mWorld->getSceneManager()->destroyEntity(mName + "BombEntity");
	delete mBody;
}

bool Bomb::hasExploded(){
	return (mTTL < 0);
}

void Bomb::generateGraphics(){

	if(mGraphicsSetUp)
		return;
	
	using namespace OgreBulletCollisions;
	using namespace Ogre;

	Ogre::SceneManager *sceneMgr = mWorld->getSceneManager();
	Entity *entity = sceneMgr->createEntity(mName + "BombEntity", "bomb.mesh");
	entity->setCastShadows(true);
	AxisAlignedBox boundingB = entity->getBoundingBox();
	Vector3 size = boundingB.getSize();
	size /= 10;
	SceneNode *bodyNode = sceneMgr->getRootSceneNode()->createChildSceneNode(mName + "BombBodyNode");
	SceneNode *entityNode = bodyNode->createChildSceneNode(mName + "BombEntityNode");
	entityNode->attachObject(entity);
	entityNode->scale(0.2, 0.2, 0.2);
	entityNode->setPosition(0, -size.x, 0);
	SphereCollisionShape *boxShape = new SphereCollisionShape(size.x);
	mBody = new OgreBulletDynamics::RigidBody(mName + "SphereBomb", mWorld);

	mBody->setShape(
		bodyNode,
		boxShape,
		0.6f,
		0.6f,
		2.85f,
		mPosition
	);

	mBody->disableDeactivation();
	mBody->getBulletRigidBody()->setAngularFactor(1.0f);

	mGraphicsSetUp = true;

}

void Bomb::detonate(){mTTL = 0;}

void Bomb::frameRenderingQueued(const Ogre::FrameEvent &evt){
	mTTL -= evt.timeSinceLastFrame;
}

std::string Bomb::getName(){return mName;}

Ogre::Vector3 Bomb::getPosition(){
	if(mGraphicsSetUp)
		return mBody->getSceneNode()->getPosition();
	return mPosition;
}

int Bomb::getRange(){return mRange;}
