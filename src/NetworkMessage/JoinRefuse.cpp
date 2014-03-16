#include "JoinRefuse.hpp"

namespace NetworkMessage{

	JoinRefuse::JoinRefuse(std::string reason):
		NetworkMessage(JOINREFUSE),
		mReason(reason)
	{
		mBody = mReason + "\n";
	}

	JoinRefuse::~JoinRefuse(){
	}

	std::string JoinRefuse::getReason(){return mReason;}

};
