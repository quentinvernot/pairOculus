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

#include "Map.hpp"

Map::Map(unsigned int height, unsigned int width, time_t seed):
	mSeed(seed) {
	setWidth(height);
	setHeight(width);
	mScale = 2;
	generateMap();
}

Map::~Map() {
	delete[] mMap;
}

Map::PrintType** Map::generateMap() {

	int result;

	std::cout << "Seed: " << mSeed << std::endl;

	// Init random
	typedef boost::mt19937 RNGType;
	RNGType rng(mSeed);
	boost::uniform_int<> block_type(0,99);	// d100
	boost::variate_generator< RNGType, boost::uniform_int<> >dice(rng, block_type);

	mMap = new PrintType* [mHeight];
	for (unsigned int i = 0; i < mHeight; i++)
	{
		mMap[i] = new PrintType [mWidth];
		for (unsigned int j = 0; j < mWidth; j++)
		{
			// Border of the map
			if (i == 0 || j == 0 || i == mHeight-1 || j == mWidth-1)
				mMap [i][j] = UNBREAKABLE;

			// Middle of the map
			else if (i%2 == 0 && j%2 == 0)
				mMap[i][j] = UNBREAKABLE;

			// Random block or free space
			else {
				result = dice();
				if (result < 30)
					mMap[i][j] = EMPTY;
				else
					mMap[i][j] = BREAKABLE;
			}
		}
	}

	// Free the corners
	mMap[1][1] = EMPTY;
	mMap[1][2] = EMPTY;
	mMap[2][1] = EMPTY;

	mMap[1][mWidth-2] = EMPTY;
	mMap[1][mWidth-3] = EMPTY;
	mMap[2][mWidth-2] = EMPTY;

	mMap[mHeight-2][1] = EMPTY;
	mMap[mHeight-2][2] = EMPTY;
	mMap[mHeight-3][1] = EMPTY;

	mMap[mHeight-2][mWidth-2] = EMPTY;
	mMap[mHeight-2][mWidth-3] = EMPTY;
	mMap[mHeight-3][mWidth-2] = EMPTY;

	// To see the map in terminal (for debug)
	printMap();

	return mMap;
}

bool Map::isBreakable(unsigned int i, unsigned int j) {

	if(i < 0 || i > mHeight || j < 0 || j > mWidth)
		return false;

	switch (mMap[i][j]) {
		case BREAKABLE:
			return true;
		case EMPTY:
		case UNBREAKABLE:
		default:
			return false;
	}

	std::cerr << "WARNING Found an unknow kind of block in isBreakable" << std::endl;
	return false;	// You shouldn't be there
}

bool Map::isUnbreakable(unsigned int i, unsigned int j) {

	if(i < 0 || i > mHeight || j < 0 || j > mWidth)
		return false;

	switch (mMap[i][j]) {
		case UNBREAKABLE:
			return true;
		case EMPTY:
		case BREAKABLE:
		default:
			return false;
	}

	std::cerr << "WARNING Found an unknow kind of block in isUnbreakable" << std::endl;
	return false;	// You shouldn't be there
}

time_t Map::getSeed(){return mSeed;}

void Map::setStartingPosition(int pos, Player *player) {

	switch (pos) {
		case 0:
			player->setStartingPosition(1.5f * mScale, 1, 1.5f * mScale);
			break;
		case 1:
			player->setStartingPosition((mHeight-1.5f) * mScale, 1, (mWidth-1.5f) * mScale);
			break;
		case 2:
			player->setStartingPosition((mHeight-1.5f) * mScale, 1, 1.5f * mScale);
			break;
		case 3:
			player->setStartingPosition(1.5f * mScale, 1, (mWidth-1.5f) * mScale);
			break;
		default:
			std::cerr << "ERROR Position \"" << pos << "\" is invalid." << std::endl;
	}

}

void Map::printMap() {
	for (unsigned int i = 0; i < mHeight; i++) {
		for (unsigned int j = 0; j < mWidth; j++) {
			std::cout << mMap [i][j];
		}
		std::cout << std::endl;
	}
}
