#include "Leave.hpp"

namespace NetworkMessage{

	Leave::Leave():
		NetworkMessage(LEAVE)
	{
		mBody = "";
	}

	Leave::~Leave(){
	}

};
