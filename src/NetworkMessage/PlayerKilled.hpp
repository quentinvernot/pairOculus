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

#ifndef __NETWORKMESSAGEPLAYERKILLED_HPP
#define __NETWORKMESSAGEPLAYERKILLED_HPP

#include <string>
#include <sstream>
#include "NetworkMessage.hpp"

namespace NetworkMessage{

	/// Message sent when a player dies.
	class PlayerKilled : public NetworkMessage{

		public:
			//Methods
			/// Constructor.
			PlayerKilled(std::string nickname);
			/// Destructor.
			~PlayerKilled();

			/// Gets the player's nickname.
			std::string getNickname();

		private:
			//Attributes
			/// The player's nickname.
			std::string mNickname;

	};

};

#endif //__NETWORKMESSAGEPLAYERKILLED_HPP
