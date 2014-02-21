#ifndef __NETWORKMESSAGEJOINACCEPT_H
#define __NETWORKMESSAGEJOINACCEPT_H

#include <string>
#include <sstream>
#include <deque>
#include "NetworkMessage.hpp"
#include "../Player.hpp"
#include "../PlayerList.hpp"

namespace NetworkMessage{

	class JoinAccept : public NetworkMessage{

		public:
			//methods
			JoinAccept(
				PlayerList *playerList
				//map
			);
			~JoinAccept();

			PlayerList *getPlayerList();

		private:
			//methods
			//arguments
			PlayerList mPlayerList;

	};

};

#endif //__NETWORKMESSAGEJOINACCEPT_H
