#ifndef __NETWORKMESSAGELEAVE_H
#define __NETWORKMESSAGELEAVE_H

#include <string>
#include <sstream>
#include "NetworkMessage.hpp"

namespace NetworkMessage{

	class Leave : public NetworkMessage{

		public:
			//methods
			Leave();
			~Leave();

		private:
			//methods
			//arguments

	};

};

#endif //__NETWORKMESSAGELEAVE_H
