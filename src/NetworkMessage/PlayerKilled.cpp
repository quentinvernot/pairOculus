#include "PlayerKilled.hpp"

namespace NetworkMessage{

	PlayerKilled::PlayerKilled(std::string nickname):
		NetworkMessage(PLAYERKILLED),
		mNickname(nickname)
	{
		mBody = mNickname + "\n";
	}

	PlayerKilled::~PlayerKilled(){
	}

	std::string PlayerKilled::getNickname(){return mNickname;}

};
