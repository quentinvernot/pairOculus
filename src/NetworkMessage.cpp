#include "NetworkMessage.hpp"

std::string NetworkMessage::getHeader(){return mHeader;}
std::string NetworkMessage::getBody(){return mBody;}
std::string NetworkMessage::getData(){return mHeader+mBody;}

void NetworkMessage::makeHeader(){
	mHeader = mType + "\n";
	mHeader += mBody.length() + "\n";
}
