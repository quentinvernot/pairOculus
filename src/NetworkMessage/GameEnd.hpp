#ifndef __NETWORKMESSAGEGAMEEND_H
#define __NETWORKMESSAGEGAMEEND_H

#include <string>
#include <sstream>
#include "NetworkMessage.hpp"

namespace NetworkMessage{

	class GameEnd : public NetworkMessage{

		public:
			//methods
			GameEnd();
			~GameEnd();

		private:
			//methods
			//arguments

	};

};

#endif //__NETWORKMESSAGEGAMEEND_H
