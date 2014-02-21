#include "JoinRefuse.hpp"

namespace NetworkMessage{

	JoinRefuse::JoinRefuse(std::string reason):
		NetworkMessage(JOINREFUSE)
	{
		mBody = reason + "\n";
	}

	JoinRefuse::~JoinRefuse(){
	}

};
