/*
This source file is part of pairOculus, a student project aiming at creating a
simple 3D multiplayer game for the Oculus Rift.

Repository can be found here : https://github.com/Target6/pairOculus 

Copyright (c) 2013 Target6

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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
