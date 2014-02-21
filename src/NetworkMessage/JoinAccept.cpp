#include "JoinAccept.hpp"

namespace NetworkMessage{

	JoinAccept::JoinAccept(
		PlayerList *playerList
		//map
	):
		NetworkMessage(JOINACCEPT),
		mPlayerList(*playerList)
	{

		std::ostringstream convert;

		for(unsigned int i = 0; i < playerList->size(); i++){
			convert << mPlayerList[i]->getNickname() << "\n";
			convert << mPlayerList[i]->getNodePositionX() << "\n";
			convert << mPlayerList[i]->getNodePositionY() << "\n";
			convert << mPlayerList[i]->getNodePositionZ() << "\n";
		}

		mBody = convert.str();

	}

	JoinAccept::~JoinAccept(){
	}
	
	PlayerList *JoinAccept::getPlayerList(){return &mPlayerList;}

};
