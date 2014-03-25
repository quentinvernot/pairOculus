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

#ifndef __NETWORKMESSAGEFACTORY_HPP
#define __NETWORKMESSAGEFACTORY_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

#include "../Player.hpp"
#include "../PlayerList.hpp"
#include "NetworkMessage.hpp"
#include "Join.hpp"
#include "Leave.hpp"
#include "JoinAccept.hpp"
#include "JoinRefuse.hpp"
#include "PlayerJoined.hpp"
#include "PlayerLeft.hpp"
#include "GameStart.hpp"
#include "GameEnd.hpp"
#include "PlayerInput.hpp"
#include "PlayerKilled.hpp"

namespace NetworkMessage{

	/** A factory class to build all messages from their requirements.
	 *  \remarks 
	 *  	If a message is demanded with a content that does not match its
	 *  	type (e.g. buildMessage(PLAYERINPUT, std::string)), the factory
	 *  	will always return a NULL pointer.
	 */
	class NetworkMessageFactory{

		public:
			//Methods
			/// Constructor.
			NetworkMessageFactory();
			/// Destructor.
			~NetworkMessageFactory();

			/** Builds a message from a string.
			 *  \remarks
			 * 		Meant to be used to rebuild an incomming message that was
			 *  	received from the network.
			 */
			NetworkMessage *buildMessage(
				std::string data
			);
			/// Builds all the messages containing no data.
			NetworkMessage *buildMessage(
				MessageType type
			);
			/// Builds the messages containing only a string.
			NetworkMessage *buildMessage(
				MessageType type,
				std::string data
			);
			/// Builds the messages containing a string and 3D coordinates.
			NetworkMessage *buildMessage(
				MessageType type,
				std::string data,
				double x,
				double y,
				double z
			);
			/// Builds the messages containing a Player.
			NetworkMessage *buildMessage(
				MessageType type,
				Player *player
			);
			/// Builds JoinAccept messages.
			NetworkMessage *buildMessage(
				MessageType type,
				PlayerList *playerList,
				unsigned int mapHeight,
				unsigned int mapWidth,
				time_t seed
			);
			/// Build PlayerInput messages.
			NetworkMessage *buildMessage(
				MessageType type,
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
			);

			/// Returns the lenght of a message's body from its header.
			int getLengthFromHeader(std::string header);

	};

};

#endif //__NETWORKMESSAGEFACTORY_HPP
