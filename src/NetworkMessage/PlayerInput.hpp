#ifndef __NETWORKMESSAGEPLAYERINPUT_H
#define __NETWORKMESSAGEPLAYERINPUT_H

#include <string>
#include <sstream>
#include "NetworkMessage.hpp"

namespace NetworkMessage{

	class PlayerInput : public NetworkMessage{

		public:
			//methods
			PlayerInput();
			~PlayerInput();

		private:
			//methods
			//arguments

	};

};

#endif //__NETWORKMESSAGEPLAYERINPUT_H
