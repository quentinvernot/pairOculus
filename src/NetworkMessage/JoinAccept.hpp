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
				unsigned int mapHeight,
				unsigned int mapWidth,
				time_t seed
			);
			~JoinAccept();

			PlayerList *getPlayerList();
			unsigned int getMapHeight();
			unsigned int getMapWidth();
			time_t getSeed();

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
