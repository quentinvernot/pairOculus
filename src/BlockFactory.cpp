/*
This source file is part of pairOculus, a student project aiming at creating a
simple 3D multiplayer game for the Oculus Rift.

Repository can be found here : https://github.com/Target6/pairOculus

Copyright (c) 2013 Zykino

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
