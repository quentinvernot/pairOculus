#include "Map.hpp"

Map::Map(unsigned int height, unsigned int width, time_t seed):
	mSeed(seed) {
	setWidth(height);
	setHeight(width);
	mScale = 2;
	generateMap();
}

Map::~Map() {
	for(unsigned int i = 0; i < mHeight; i++)
		delete mMap[i];

	delete mMap;
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

	// To see the map (for debuging it)
	printMap();

	return mMap;
}

bool Map::isBreakable(int i, int j) {
	switch (mMap[i][j]) {
		case BREAKABLE:
			return true;
			break;
		case EMPTY:
		case UNBREAKABLE:
			return false;
			break;
		default:
			;	// TODO generate exception
	}

	std::cerr << "WARNING Found an unknow kind of block in isBreakable" << std::endl;
	return false;	// You must never come here
}
/*
bool Map::Break(int i, int j)
{
	switch (mMap[i][j]) {
		case BREAKABLE:
			mMap[i][j] = EMPTY;
			break;
		case EMPTY:
		case UNBREAKABLE:
			break;
		default:
			;	// TODO generate exception
	}

	std::cout << "WARNING Found an unknow kind of block in isBreakable" << std::endl;
	return false;	// You must never come here
}
*/

time_t Map::getSeed(){return mSeed;}

void Map::setStartingPosition(int pos, Player *player) {

	switch (pos) {
		case 0:
			player->setNodePositionX(1.5f * (mScale + 0.1f));
			player->setNodePositionY(1);
			player->setNodePositionZ(1.5f * (mScale + 0.1f));
			break;
		case 1:
			player->setNodePositionX((mHeight-1.5f) * (mScale + 0.1f));
			player->setNodePositionY(0);
			player->setNodePositionZ((mWidth-1.5f) * (mScale + 0.1f));
			break;
		case 2:
			player->setNodePositionX((mHeight-1.5f) * (mScale + 0.1f));
			player->setNodePositionY(0);
			player->setNodePositionZ(1.5f * (mScale + 0.1f));
			break;
		case 3:
			player->setNodePositionX(1.5f * (mScale + 0.1f));
			player->setNodePositionY(0);
			player->setNodePositionZ((mWidth-1.5f) * (mScale + 0.1f));
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
