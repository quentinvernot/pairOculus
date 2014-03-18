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

#include "RemotePlayer.hpp"

RemotePlayer::RemotePlayer(
	std::string name,
	OgreBulletDynamics::DynamicsWorld *world,
	BombManager *bombManager
):
	OgrePlayer(name, world, bombManager)
{
}

RemotePlayer::~RemotePlayer(){
}

void RemotePlayer::generateGraphics(){

	if(mGraphicsSetUp)
		return;

	using namespace Ogre;

	mEntity = mWorld->getSceneManager()->createEntity("bomberman.mesh");
	mEntity->setCastShadows(true);
	Vector3 size = computeHitboxSize();

	SceneNode *bodyNode = mWorld->getSceneManager()->getRootSceneNode()->createChildSceneNode();

	SceneNode *entityNode = bodyNode->createChildSceneNode();
	entityNode->attachObject(mEntity);
	entityNode->scale(0.1, 0.1, 0.1);
	entityNode->setPosition(0, -0.3, 0);

	generateHitbox(size, bodyNode);

	mPlayerAnimationState = new PlayerAnimation(mWorld->getSceneManager(), mEntity);

	mGraphicsSetUp = true;

}

bool RemotePlayer::frameRenderingQueued(const Ogre::FrameEvent &evt){

	computeAcceleration();
	computeVelocity(evt);
	computeNodePosition(evt);

	handleBombCreation(evt);

	if(mGraphicsSetUp){

		if (mVelocity.x != 0 && mVelocity.z != 0)
			mPlayerAnimationState->doRunAnimation();
		else
			mPlayerAnimationState->doIdleAnimation();

		mPlayerAnimationState->getPlayerAnimationState()->addTime(evt.timeSinceLastFrame);

	}

	resetCorrection();

	return true;

}

void RemotePlayer::win(){

	if(mIsDead)
		return;

	mHasWon = true;

	mGoingForward = false;
	mGoingBack = false;
	mGoingLeft = false;
	mGoingRight = false;
	mPuttingBomb = false;
	mGoingUp = false;
	mGoingDown = false;
	mFastMove = false;

	mX = mStartingX;
	mY = mStartingY + 10;
	mZ = mStartingZ;

	mWasTeleported = true;

}

void RemotePlayer::die(){

	if(mHasWon)
		return;

	mIsDead = true;

	mGoingForward = false;
	mGoingBack = false;
	mGoingLeft = false;
	mGoingRight = false;
	mPuttingBomb = false;
	mGoingUp = false;
	mGoingDown = false;
	mFastMove = false;

	mX = mStartingX;
	mY = mStartingY + 10;
	mZ = mStartingZ;

	mWasTeleported = true;

}
