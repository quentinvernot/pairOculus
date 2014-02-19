#include "Player.hpp"

Player::Player(std::string name):
	mName(name),
	mTopSpeed(300),
	mTopAccel(1),
	mFastMove(false),
	mNodeYaw(0),
	mNodePitch(0),
	mNodeRoll(0),
	mNodePositionX(0),
	mNodePositionY(0),
	mNodePositionZ(50),
	mGoingForward(false),
	mGoingBack(false),
	mGoingLeft(false),
	mGoingRight(false),
	mGoingUp(false),
	mGoingDown(false)
{
}

std::string Player::getName(){return mName;}
