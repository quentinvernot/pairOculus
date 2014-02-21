#ifndef __NETWORKMESSAGEFACTORY_H
#define __NETWORKMESSAGEFACTORY_H

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

	class NetworkMessageFactory{

		public:
			//methods
			NetworkMessageFactory();
			~NetworkMessageFactory();

			NetworkMessage *buildMessage(
				std::string data
			);
			NetworkMessage *buildMessage(
				MessageType type
			);
			NetworkMessage *buildMessage(
				MessageType type,
				std::string data
			);
			NetworkMessage *buildMessage(
				MessageType type,
				std::string data,
				long x,
				long y,
				long z
			);
			NetworkMessage *buildMessage(
				MessageType type,
				Player *player
			);
			NetworkMessage *buildMessage(
				MessageType type,
				PlayerList *playerList
			);
			int getLengthFromHeader(std::string header);

		private:
			//methods
			//arguments

	};

};

#endif //__NETWORKMESSAGEFACTORY_H
