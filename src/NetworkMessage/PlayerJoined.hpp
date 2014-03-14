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
				double x,
				double y,
				double z
			);
			~PlayerJoined();

			std::string getNickname();
			double getPositionX();
			double getPositionY();
			double getPositionZ();

		private:
			//methods
			void buildSelf();
			//arguments
			std::string mNickname;
			double mX;
			double mY;
			double mZ;

	};

};

#endif //__NETWORKMESSAGEPLAYERJOINED_H
