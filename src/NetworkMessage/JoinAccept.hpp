#ifndef __NETWORKMESSAGEJOINACCEPT_H
#define __NETWORKMESSAGEJOINACCEPT_H

#include <string>
#include <sstream>
#include <deque>
#include "NetworkMessage.hpp"
#include "../Player.hpp"
#include "../PlayerList.hpp"
#include "../Map.hpp"

namespace NetworkMessage{

	class JoinAccept : public NetworkMessage{

		public:
			//methods
			JoinAccept(
				PlayerList *playerList,
				unsigned int mMapHeight,
				unsigned int mMapWidth,
				time_t mSeed
			);
			~JoinAccept();

			PlayerList *getPlayerList();

		private:
			//methods
			//arguments
			PlayerList mPlayerList;
			unsigned int mMapHeight;
			unsigned int mMapWidth;
			time_t mSeed;

	};

};

#endif //__NETWORKMESSAGEJOINACCEPT_H
