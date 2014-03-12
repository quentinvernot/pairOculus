#include "BlockFactory.hpp"

BlockFactory::BlockFactory(Ogre::SceneManager* sceneMgr) :
	mSceneMgr(sceneMgr)
{
}

BlockFactory::~BlockFactory() {
}

Ogre::ManualObject* BlockFactory::createBlock(
	Map::PrintType cellType,
	unsigned int i,
	unsigned int j,
	double scale
) {

	stringstream genName;
	genName << "manualBlock_" << i << "_" << j;

	switch (cellType) {
		case Map::EMPTY:
			return NULL;
			break;
		case Map::BREAKABLE: {
			Pyramid *myPyramid = new Pyramid(
				mSceneMgr->createManualObject(genName.str()),
				Block::COMPLETE,
				-(scale/2),
				-(scale/6),
				-(scale/2),
				scale,
				scale/2,
				scale
			);
			return myPyramid->GetManualBlock();
			break;
		}
		case Map::UNBREAKABLE: {
			Cube *myCube = new Cube(
				mSceneMgr->createManualObject(genName.str()),
				Block::COMPLETE,
				-(scale/2),
				-(scale/6),
				-(scale/2),
				scale,
				scale/3,
				scale
			);
			return myCube->GetManualBlock();
			break;
		}
		default:
			break;
	}

	//TODO Exception?
	Ogre::LogManager::getSingletonPtr()->logMessage("WARNING No representation for this kind of Block");
	std::cerr << cellType << std::endl;
	return NULL;
}
