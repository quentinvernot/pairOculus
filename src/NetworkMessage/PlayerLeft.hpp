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

		private:
			//methods
			//arguments

	};

};

#endif //__NETWORKMESSAGEPLAYERLEFT_H
