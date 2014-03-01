#ifndef __NETWORKMESSAGEPLAYERLEFT_H
#define __NETWORKMESSAGEPLAYERLEFT_H

#include <string>
#include <sstream>
#include "NetworkMessage.hpp"

namespace NetworkMessage{

	class PlayerLeft : public NetworkMessage{

		public:
			//methods
			PlayerLeft(std::string nickname);
			~PlayerLeft();
			std::string getNickname();

		private:
			//methods
			//arguments
			std::string mNickname;

	};

};

#endif //__NETWORKMESSAGEPLAYERLEFT_H
