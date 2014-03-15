#include "PlayerLeft.hpp"

namespace NetworkMessage{

	PlayerLeft::PlayerLeft(std::string nickname):
		NetworkMessage(PLAYERLEFT),
		mNickname(nickname)
	{
		mBody = nickname + "\n";
	}

	PlayerLeft::~PlayerLeft(){
	}
	
	std::string PlayerLeft::getNickname(){return mNickname;}

};
