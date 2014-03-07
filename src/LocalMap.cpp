#include "LocalMap.hpp"

LocalMap::LocalMap(unsigned int height, unsigned int width, time_t seed) :
	Map(height, width, seed) {
	//ctor
}

LocalMap::~LocalMap() {
	//dtor
}

void LocalMap::generate(Ogre::SceneManager* sceneMgr) {
	FloorPanel* fp = new FloorPanel(sceneMgr->createManualObject("floor"), mScale*mHeight, mScale*mWidth);
	BlockFactory* bf = new BlockFactory(sceneMgr);

	sceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(fp->GetManualFloor());
	Ogre::ManualObject *object;

	for (unsigned int i = 0; i < mHeight; i++) {
		for (unsigned int j = 0; j < mWidth; j++) {
			object = bf->createBlock(mMap[i][j], i, j, mScale);
			if (object != NULL)
				sceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(object);
		}
	}
}

void LocalMap::viewMap() {
}
