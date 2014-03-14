#ifndef __NETWORKMESSAGEPLAYERKILLED_H
#define __NETWORKMESSAGEPLAYERKILLED_H

#include <string>
#include <sstream>
#include "NetworkMessage.hpp"

namespace NetworkMessage{

	class PlayerKilled : public NetworkMessage{

		public:
			//methods
			PlayerKilled(std::string nickname);
			~PlayerKilled();

			std::string getNickname();

		private:
			//methods
			//arguments
			std::string mNickname;

	};

};

#endif //__NETWORKMESSAGEPLAYERKILLED_H
