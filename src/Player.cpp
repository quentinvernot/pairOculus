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

std::string Player::getNickname(){return mName;}

double Player::getNodeYaw(){return mNodeYaw;}
double Player::getNodePitch(){return mNodePitch;}
double Player::getNodeRoll(){return mNodeRoll;}

long Player::getNodePositionX(){return mNodePositionX;}
long Player::getNodePositionY(){return mNodePositionY;}
long Player::getNodePositionZ(){return mNodePositionZ;}
void Player::setNodePositionX(long nodePositionX){
	mNodePositionX = nodePositionX;
}
void Player::setNodePositionY(long nodePositionY){
	mNodePositionY = nodePositionY;
}
void Player::setNodePositionZ(long nodePositionZ){
	mNodePositionZ = nodePositionZ;
}

bool Player::getGoingForward(){return mGoingForward;}
bool Player::getGoingBack(){return mGoingBack;}
bool Player::getGoingLeft(){return mGoingLeft;}
bool Player::getGoingRight(){return mGoingRight;}
bool Player::getGoingUp(){return mGoingUp;}
bool Player::getGoingDown(){return mGoingDown;}
