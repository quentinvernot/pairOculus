#ifndef __NETWORKMESSAGEPLAYERJOINED_H
#define __NETWORKMESSAGEPLAYERJOINED_H

#include <string>
#include <sstream>
#include "../Player.hpp"
#include "NetworkMessage.hpp"

namespace NetworkMessage{

	class PlayerJoined : public NetworkMessage{

		public:
			//methods
			PlayerJoined(Player *player);
			PlayerJoined(
				std::string nickname,
				long x,
				long y,
				long z
			);
			~PlayerJoined();
			
			std::string getNickname();
			long getPositionX();
			long getPositionY();
			long getPositionZ();

		private:
			//methods
			void buildSelf();
			//arguments
			std::string mNickname;
			long mX;
			long mY;
			long mZ;

	};

};

#endif //__NETWORKMESSAGEPLAYERJOINED_H
