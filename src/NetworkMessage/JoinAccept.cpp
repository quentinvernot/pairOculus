#include "JoinAccept.hpp"

namespace NetworkMessage{

	JoinAccept::JoinAccept(
		PlayerList *playerList,
		unsigned int mapHeight,
		unsigned int mapWidth,
		time_t seed
	):
		NetworkMessage(JOINACCEPT),
		mPlayerList(*playerList),
		mMapHeight(mapHeight),
		mMapWidth(mapWidth),
		mSeed(seed)
	{

		std::ostringstream convert;

		for(unsigned int i = 0; i < playerList->size(); i++){
			convert << mPlayerList[i]->getNickname() << "\n";
			convert << mPlayerList[i]->getX() << "\n";
			convert << mPlayerList[i]->getY() << "\n";
			convert << mPlayerList[i]->getZ() << "\n";
		}

		convert << mMapHeight << "\n";
		convert << mMapWidth << "\n";
		convert << mSeed << "\n";

		mBody = convert.str();

	}

	JoinAccept::~JoinAccept(){
	}
	
	PlayerList *JoinAccept::getPlayerList(){return &mPlayerList;}
	unsigned int JoinAccept::getMapHeight(){return mMapHeight;}
	unsigned int JoinAccept::getMapWidth(){return mMapWidth;}
	time_t JoinAccept::getSeed(){return mSeed;}

};
