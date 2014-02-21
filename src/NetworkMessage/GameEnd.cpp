#include "GameEnd.hpp"

namespace NetworkMessage{

	GameEnd::GameEnd():
		NetworkMessage(GAMEEND)
	{
	}

	GameEnd::~GameEnd(){
	}

};
