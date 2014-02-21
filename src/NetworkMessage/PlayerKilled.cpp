#include "PlayerKilled.hpp"

namespace NetworkMessage{

	PlayerKilled::PlayerKilled():
		NetworkMessage(PLAYERKILLED)
	{
	}

	PlayerKilled::~PlayerKilled(){
	}

};
