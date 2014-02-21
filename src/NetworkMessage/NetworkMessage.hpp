#ifndef __NETWORKMESSAGE_H
#define __NETWORKMESSAGE_H

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

namespace NetworkMessage{

	enum MessageType {
		JOIN,
		LEAVE,
		JOINACCEPT,
		JOINREFUSE,
		PLAYERJOINED,
		PLAYERLEFT,
		GAMESTART,
		GAMEEND,
		PLAYERINPUT,
		PLAYERKILLED
	};
	
	enum {
		HEADERLENGTH = 8,
		MAXBODYLENGTH = 1024
	};

	class NetworkMessage{

		public:
			//methods
			NetworkMessage(MessageType type);
			~NetworkMessage();

			MessageType getType();
			std::string getHeader();
			std::string getBody();
			std::string getMessage();

		protected:
			//arguments
			MessageType mType;
			std::string mHeader;
			std::string mBody;

		private:
			//methods
			void makeHeader();
			void formatBody();

	};

};

#endif //__NETWORKMESSAGE_H
