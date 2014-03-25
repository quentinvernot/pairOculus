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

#include "PlayerInput.hpp"

namespace NetworkMessage{

	PlayerInput::PlayerInput(Player *player):
		NetworkMessage(PLAYERINPUT),
		mNickname(player->getNickname()),
		mYaw(player->getYaw()),
		mPitch(player->getPitch()),
		mRoll(player->getRoll()),
		mX(player->getX()),
		mY(player->getY()),
		mZ(player->getZ()),
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
		double nodeX,
		double nodeY,
		double nodeZ,
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
		mYaw(nodeYaw),
		mPitch(nodePitch),
		mRoll(nodeRoll),
		mX(nodeX),
		mY(nodeY),
		mZ(nodeZ),
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

	double PlayerInput::getYaw(){return mYaw;}
	double PlayerInput::getPitch(){return mPitch;}
	double PlayerInput::getRoll(){return mRoll;}

	double PlayerInput::getX(){return mX;}
	double PlayerInput::getY(){return mY;}
	double PlayerInput::getZ(){return mZ;}

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

		convert << mYaw << "\n";
		convert << mPitch << "\n";
		convert << mRoll << "\n";

		convert << mX << "\n";
		convert << mY << "\n";
		convert << mZ << "\n";

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
