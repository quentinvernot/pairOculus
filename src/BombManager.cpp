#include "BombManager.hpp"

BombManager::BombManager(OgreBulletDynamics::DynamicsWorld *world):
	mWorld(world),
	mExplosionManager(new ExplosionManager(mWorld)),
	mBombPlaced(0),
	mExplosionListener(0)
{
}

BombManager::~BombManager(){
	mNewBombs.clear();
	mActiveBombs.clear();
}

void BombManager::add(
	std::string owner,
	Ogre::Vector3 position
){
	std::ostringstream convert;
	convert << owner << mBombPlaced;
	mNewBombs.push_back(new Bomb(convert.str(), position, mWorld));
	mBombPlaced++;
}

void BombManager::detonate(unsigned int i){

	if(mExplosionListener){

		if(i > mActiveBombs.size())
			return;

		mExplosionListener->bombExploded(
			mActiveBombs[i]->getPosition(),
			mActiveBombs[i]->getRange()
		);
		
	}

	mExplosionManager->add(
		mActiveBombs[i]->getName(),
		mActiveBombs[i]->getPosition()
	);

	delete mActiveBombs[i];
	mActiveBombs.erase(mActiveBombs.begin() + i);

}

void BombManager::frameRenderingQueued(const Ogre::FrameEvent &evt){

	while(mNewBombs.size() > 0){
		mNewBombs.front()->generateGraphics();
		mActiveBombs.push_back(mNewBombs.front());
		mNewBombs.pop_front();
	}

	for(unsigned int i = 0; i < mActiveBombs.size(); i++)
		mActiveBombs[i]->frameRenderingQueued(evt);

	while(mActiveBombs.size() > 0 && mActiveBombs.front()->hasExploded())
		detonate(0);

	mExplosionManager->frameRenderingQueued(evt);

}

unsigned int BombManager::size(){return mActiveBombs.size();}

Bomb *BombManager::operator[](unsigned int i){
	if(i > mActiveBombs.size())
		return 0;
	return mActiveBombs[i];
}

void BombManager::setExplosionListener(ExplosionListener *el){
	mExplosionListener = el;
}
