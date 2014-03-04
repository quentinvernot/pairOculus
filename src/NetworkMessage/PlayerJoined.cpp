#include "PlayerJoined.hpp"

namespace NetworkMessage{

	PlayerJoined::PlayerJoined(
		Player *player
	):
		NetworkMessage(PLAYERJOINED),
		mNickname(player->getNickname()),
		mX(player->getNodePositionX()),
		mY(player->getNodePositionY()),
		mZ(player->getNodePositionZ())
	{
		buildSelf();
	}

	PlayerJoined::PlayerJoined(
		std::string nickname,
		long x,
		long y,
		long z
	):
		NetworkMessage(PLAYERJOINED),
		mNickname(nickname),
		mX(x),
		mY(y),
		mZ(z)
	{
		buildSelf();
	}

	PlayerJoined::~PlayerJoined(){
	}

	std::string PlayerJoined::getNickname(){return mNickname;}
	long PlayerJoined::getPositionX(){return mX;}
	long PlayerJoined::getPositionY(){return mY;}
	long PlayerJoined::getPositionZ(){return mZ;}

	void PlayerJoined::buildSelf(){
		std::ostringstream convert;
		convert << mNickname << "\n";
		convert << mX << "\n";
		convert << mY << "\n";
		convert << mZ << "\n";
		mBody = convert.str();
	}

};