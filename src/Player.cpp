#include "Player.hpp"

Player::Player(std::string nickname):
	mNickname(nickname),
	mTopSpeed(300),
	mTopAccel(1),
	mFastMove(false),
	mYaw(0),
	mPitch(0),
	mRoll(0),
	mX(0),
	mY(0),
	mZ(0),
	mGoingForward(false),
	mGoingBack(false),
	mGoingLeft(false),
	mGoingRight(false),
	mGoingUp(false),
	mGoingDown(false),
	mPuttingBomb(false),
	mHasWon(false),
	mIsDead(false)
{
}

Player::~Player(){
}

std::string Player::getNickname(){return mNickname;}

double Player::getYaw(){return mYaw;}
double Player::getPitch(){return mPitch;}
double Player::getRoll(){return mRoll;}

double Player::getX(){return mX;}
double Player::getY(){return mY;}
double Player::getZ(){return mZ;}
void Player::setX(double x){mX = x;}
void Player::setY(double y){mY = y;}
void Player::setZ(double z){mZ = z;}

void Player::setStartingPosition(double x, double y, double z){
	mX = x;
	mStartingX = x;
	mY = y;
	mStartingY = y;
	mZ = z;
	mStartingZ = z;
}

bool Player::getGoingForward(){return mGoingForward;}
bool Player::getGoingBack(){return mGoingBack;}
bool Player::getGoingLeft(){return mGoingLeft;}
bool Player::getGoingRight(){return mGoingRight;}
bool Player::getGoingUp(){return mGoingUp;}
bool Player::getGoingDown(){return mGoingDown;}

bool Player::getPuttingBomb(){return mPuttingBomb;}

void Player::win(){mHasWon = true;}
bool Player::hasWon(){return mIsDead;}
void Player::die(){mIsDead = true;}
bool Player::isDead(){return mIsDead;}
