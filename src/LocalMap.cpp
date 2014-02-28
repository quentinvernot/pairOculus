#include "LocalMap.hpp"

LocalMap::LocalMap(Map* mmap, Ogre::SceneManager* sceneMgr, unsigned int scale) :
	mmap (mmap) {
	FloorPanel* fp = new FloorPanel(sceneMgr->createManualObject("floor"), scale*mmap->getHeight(), scale*mmap->getWidth());
	BlockFactory* bf = new BlockFactory(sceneMgr);

	Ogre::ManualObject *object;

//	fp->generateFloor();
	object = fp->GetManualFloor();
	sceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(object);

	for (unsigned int i = 0; i < mmap->getHeight(); i++) {
		for (unsigned int j = 0; j < mmap->getWidth(); j++) {
			object = bf->createBlock(mmap->getCellType(i, j), i, j, scale);
			if (object != NULL)
				sceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(object);
		}
	}
	//ctor
}

LocalMap::~LocalMap() {
	//dtor
}

void LocalMap::viewMap() {
}
