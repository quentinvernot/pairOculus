#include "Player.hpp"

Player::Player(std::string nickname):
	mNickname(nickname),
	mTopSpeed(300),
	mTopAccel(1),
	mFastMove(false),
	mNodeYaw(0),
	mNodePitch(0),
	mNodeRoll(0),
	mNodePositionX(0),
	mNodePositionY(0),
	mNodePositionZ(0),
	mGoingForward(false),
	mGoingBack(false),
	mGoingLeft(false),
	mGoingRight(false),
	mGoingUp(false),
	mGoingDown(false)
{
}

Player::~Player(){
}

std::string Player::getNickname(){return mNickname;}

double Player::getNodeYaw(){return mNodeYaw;}
double Player::getNodePitch(){return mNodePitch;}
double Player::getNodeRoll(){return mNodeRoll;}

double Player::getNodePositionX(){return mNodePositionX;}
double Player::getNodePositionY(){return mNodePositionY;}
double Player::getNodePositionZ(){return mNodePositionZ;}
void Player::setNodePositionX(double nodePositionX){
	mNodePositionX = nodePositionX;
}
void Player::setNodePositionY(double nodePositionY){
	mNodePositionY = nodePositionY;
}
void Player::setNodePositionZ(double nodePositionZ){
	mNodePositionZ = nodePositionZ;
}

bool Player::getGoingForward(){return mGoingForward;}
bool Player::getGoingBack(){return mGoingBack;}
bool Player::getGoingLeft(){return mGoingLeft;}
bool Player::getGoingRight(){return mGoingRight;}
bool Player::getGoingUp(){return mGoingUp;}
bool Player::getGoingDown(){return mGoingDown;}
