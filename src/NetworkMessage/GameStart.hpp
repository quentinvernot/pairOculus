#ifndef __NETWORKMESSAGEGAMESTART_H
#define __NETWORKMESSAGEGAMESTART_H

#include <string>
#include <sstream>
#include "NetworkMessage.hpp"

namespace NetworkMessage{

	class GameStart : public NetworkMessage{

		public:
			//methods
			GameStart();
			~GameStart();

		private:
			//methods
			//arguments

	};

};

#endif //__NETWORKMESSAGEGAMESTART_H
