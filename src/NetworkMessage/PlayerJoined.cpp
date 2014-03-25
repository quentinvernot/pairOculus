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
