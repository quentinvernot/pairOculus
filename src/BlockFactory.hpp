#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H

#include <sstream>

#include <OgreSceneManager.h>
#include <OgreLogManager.h>
#include <OgreManualObject.h>

#include "Map.hpp"
#include "Cube.hpp"
#include "Pyramid.hpp"

class BlockFactory {
	public:
		/** Default constructor */
		BlockFactory(Ogre::SceneManager* sceneMgr);
		/** Default destructor */
		virtual ~BlockFactory();

		Ogre::ManualObject* createBlock(Map::PrintType cellType, unsigned int i, unsigned int j, unsigned int scale);
	private:
		Ogre::SceneManager* mSceneMgr;
};

#endif // BLOCKFACTORY_H