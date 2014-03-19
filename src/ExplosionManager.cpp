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

#include "ExplosionManager.hpp"

ExplosionManager::ExplosionManager(
	OgreBulletDynamics::DynamicsWorld *world
):
	mWorld(world),
	mExplosionsPerDetonation(10),
	mExplosionCreated(0)
{
}

ExplosionManager::~ExplosionManager(){
	newExplosions.clear();
	activeExplosions.clear();
}

void ExplosionManager::add(std::string owner, Ogre::Vector3 position){
	std::ostringstream convert;

	Ogre::Vector3 velocity(30, 0, 0);

	for(unsigned int i = 0; i < mExplosionsPerDetonation; i++){
		convert << owner << mExplosionCreated;
		newExplosions.push_back(new Explosion(convert.str(), position, velocity, mWorld));
		velocity = Ogre::Quaternion(Ogre::Degree((double)(360*i)/(double)mExplosionsPerDetonation), Ogre::Vector3::UNIT_Y) * velocity;
		mExplosionCreated++;
		convert.str("");
		convert.clear();
	}

}

void ExplosionManager::frameRenderingQueued(const Ogre::FrameEvent &evt){

	while(newExplosions.size() > 0){
		newExplosions.front()->generateGraphics();
		activeExplosions.push_back(newExplosions.front());
		newExplosions.pop_front();
	}

	for(unsigned int i = 0; i < activeExplosions.size(); i++)
		activeExplosions[i]->frameRenderingQueued(evt);

	while(activeExplosions.size() > 0 && activeExplosions.front()->getRange() <= 0){
			delete activeExplosions.front();
			activeExplosions.pop_front();
	}

}

unsigned int ExplosionManager::size(){return activeExplosions.size();}

Explosion *ExplosionManager::operator[](unsigned int i){
	if(i > activeExplosions.size())
		return 0;
	return activeExplosions[i];
}
