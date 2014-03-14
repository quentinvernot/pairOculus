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
