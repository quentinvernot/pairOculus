#ifndef __NETWORKMESSAGEJOINREFUSE_H
#define __NETWORKMESSAGEJOINREFUSE_H

#include <string>
#include <sstream>
#include "NetworkMessage.hpp"

namespace NetworkMessage{

	class JoinRefuse : public NetworkMessage{

		public:
			//methods
			JoinRefuse(std::string reason);
			~JoinRefuse();

		private:
			//methods
			//arguments

	};

};

#endif //__NETWORKMESSAGEJOINREFUSE_H
