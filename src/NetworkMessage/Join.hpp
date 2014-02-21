#ifndef __NETWORKMESSAGEJOIN_H
#define __NETWORKMESSAGEJOIN_H

#include <string>
#include <sstream>
#include "NetworkMessage.hpp"

namespace NetworkMessage{

	class Join : public NetworkMessage{

		public:
			//methods
			Join(std::string nickname);
			~Join();

			std::string getNickname();

		private:
			//methods
			//arguments
			std::string mNickname;

	};

};

#endif //__NETWORKMESSAGEJOIN_H
