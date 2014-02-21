#ifndef __NETWORKMESSAGEPLAYERKILLED_H
#define __NETWORKMESSAGEPLAYERKILLED_H

#include <string>
#include <sstream>
#include "NetworkMessage.hpp"

namespace NetworkMessage{

	class PlayerKilled : public NetworkMessage{

		public:
			//methods
			PlayerKilled();
			~PlayerKilled();

		private:
			//methods
			//arguments

	};

};

#endif //__NETWORKMESSAGEPLAYERKILLED_H
