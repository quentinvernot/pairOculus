#include "NetworkMessage.hpp"

namespace NetworkMessage{

	NetworkMessage::NetworkMessage(MessageType type):
		mType(type),
		mHeader(""),
		mBody("")
	{
	}

	NetworkMessage::~NetworkMessage(){
	}

	MessageType NetworkMessage::getType(){return mType;}
	std::string NetworkMessage::getHeader(){return mHeader;}
	std::string NetworkMessage::getBody(){
		formatBody();
		return mBody;
	}
	std::string NetworkMessage::getMessage(){
		makeHeader();
		formatBody();
		return mHeader+mBody;
	}

	void NetworkMessage::makeHeader(){

		std::ostringstream convert("");
		convert << std::setfill('0') << std::setw(2) << mType << "\n";
		convert << std::setfill('0') << std::setw(4) << mBody.length() << "\n";
		mHeader = convert.str();

	}

	void NetworkMessage::formatBody(){
		if(mBody.length() > MAXBODYLENGTH)
			mBody.substr(0, MAXBODYLENGTH);
	}

};
