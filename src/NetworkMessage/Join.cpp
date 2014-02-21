#include "Join.hpp"

namespace NetworkMessage{

	Join::Join(std::string nickname):
		NetworkMessage(JOIN),
		mNickname(nickname)
	{
		mBody = mNickname + "\n";
	}

	Join::~Join(){
	}
	
	std::string Join::getNickname(){return mNickname;}

};
