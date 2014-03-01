#include "PlayerLeft.hpp"

namespace NetworkMessage{

	PlayerLeft::PlayerLeft(std::string nickname):
		NetworkMessage(PLAYERLEFT)
	{
		mBody = nickname + "\n";
	}

	PlayerLeft::~PlayerLeft(){
	}
	
	std::string PlayerLeft::getNickname(){return mNickname;}

};
