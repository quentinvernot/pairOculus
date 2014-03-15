#include "PlayerJoined.hpp"

namespace NetworkMessage{

	PlayerJoined::PlayerJoined(
		Player *player
	):
		NetworkMessage(PLAYERJOINED),
		mNickname(player->getNickname()),
		mX(player->getX()),
		mY(player->getY()),
		mZ(player->getZ())
	{
		buildSelf();
	}

	PlayerJoined::PlayerJoined(
		std::string nickname,
		double x,
		double y,
		double z
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
	double PlayerJoined::getX(){return mX;}
	double PlayerJoined::getY(){return mY;}
	double PlayerJoined::getZ(){return mZ;}

	void PlayerJoined::buildSelf(){
		std::ostringstream convert;
		convert << mNickname << "\n";
		convert << mX << "\n";
		convert << mY << "\n";
		convert << mZ << "\n";
		mBody = convert.str();
	}

};
