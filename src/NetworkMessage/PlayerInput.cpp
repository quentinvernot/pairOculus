#include "PlayerInput.hpp"

namespace NetworkMessage{

	PlayerInput::PlayerInput(Player *player):
		NetworkMessage(PLAYERINPUT),
		mNickname(player->getNickname()),
		mNodeYaw(player->getNodeYaw()),
		mNodePitch(player->getNodePitch()),
		mNodeRoll(player->getNodeRoll()),
		mNodePositionX(player->getNodePositionX()),
		mNodePositionY(player->getNodePositionY()),
		mNodePositionZ(player->getNodePositionZ()),
		mGoingForward(player->getGoingForward()),
		mGoingBack(player->getGoingBack()),
		mGoingLeft(player->getGoingLeft()),
		mGoingRight(player->getGoingRight()),
		mGoingUp(player->getGoingUp()),
		mGoingDown(player->getGoingDown()),
		mPuttingBomb(player->getPuttingBomb())
	{
		buildSelf();
	}

	PlayerInput::PlayerInput(
		std::string nickname,
		double nodeYaw,
		double nodePitch,
		double nodeRoll,
		double nodePositionX,
		double nodePositionY,
		double nodePositionZ,
		bool goingForward,
		bool goingBack,
		bool goingLeft,
		bool goingRight,
		bool goingUp,
		bool goingDown,
		bool puttingBomb
	):
		NetworkMessage(PLAYERINPUT),
		mNickname(nickname),
		mNodeYaw(nodeYaw),
		mNodePitch(nodePitch),
		mNodeRoll(nodeRoll),
		mNodePositionX(nodePositionX),
		mNodePositionY(nodePositionY),
		mNodePositionZ(nodePositionZ),
		mGoingForward(goingForward),
		mGoingBack(goingBack),
		mGoingLeft(goingLeft),
		mGoingRight(goingRight),
		mGoingUp(goingUp),
		mGoingDown(goingDown),
		mPuttingBomb(puttingBomb)
	{
		buildSelf();
	}

	PlayerInput::~PlayerInput(){
	}

	std::string PlayerInput::getNickname(){return mNickname;}

	double PlayerInput::getNodeYaw(){return mNodeYaw;}
	double PlayerInput::getNodePitch(){return mNodePitch;}
	double PlayerInput::getNodeRoll(){return mNodeRoll;}

	double PlayerInput::getNodePositionX(){return mNodePositionX;}
	double PlayerInput::getNodePositionY(){return mNodePositionY;}
	double PlayerInput::getNodePositionZ(){return mNodePositionZ;}

	bool PlayerInput::getGoingForward(){return mGoingForward;}
	bool PlayerInput::getGoingBack(){return mGoingBack;}
	bool PlayerInput::getGoingLeft(){return mGoingLeft;}
	bool PlayerInput::getGoingRight(){return mGoingRight;}
	bool PlayerInput::getGoingUp(){return mGoingUp;}
	bool PlayerInput::getGoingDown(){return mGoingDown;}

	bool PlayerInput::getPuttingBomb(){return mPuttingBomb;}

	void PlayerInput::buildSelf(){

		std::ostringstream convert;

		convert << mNickname << "\n";

		convert << mNodeYaw << "\n";
		convert << mNodePitch << "\n";
		convert << mNodeRoll << "\n";

		convert << mNodePositionX << "\n";
		convert << mNodePositionY << "\n";
		convert << mNodePositionZ << "\n";

		convert << mGoingForward << "\n";
		convert << mGoingBack << "\n";
		convert << mGoingLeft << "\n";
		convert << mGoingRight << "\n";
		convert << mGoingUp << "\n";
		convert << mGoingDown << "\n";

		convert << mPuttingBomb << "\n";

		mBody = convert.str();

	}

};
