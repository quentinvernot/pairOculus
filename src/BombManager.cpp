#include "BombManager.hpp"

BombManager::BombManager(
	OgreBulletDynamics::DynamicsWorld *world,
	LocalMap *map
):
	mWorld(world),
	mMap(map),
	mBombPlaced(0)
{
}

BombManager::~BombManager(){
	newBombs.clear();
	activeBombs.clear();
}

void BombManager::add(
	std::string owner,
	Ogre::Vector3 position
){
	std::ostringstream convert;
	convert << owner << mBombPlaced;
	newBombs.push_back(new Bomb(convert.str(), position, mWorld));
	mBombPlaced++;
}

void BombManager::frameRenderingQueued(){

	while(newBombs.size() > 0){
		newBombs.front()->generateGraphics();
		activeBombs.push_back(newBombs.front());
		newBombs.pop_front();
	}

	clock_t now = clock();

	while(activeBombs.size() > 0 && activeBombs.front()->hasExploded(now)){
		delete activeBombs.front();
		activeBombs.pop_front();
	}

}
