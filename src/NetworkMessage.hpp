#ifndef __NETWORKMESSAGE_H
#define __NETWORKMESSAGE_H

#include <string>
#include <sstream>

enum MessageType {
	PLAYERJOIN = 0,
	PLAYERLEFT = 1,
	PLAYERMOVE = 2,
	INITMAP = 3
};

class NetworkMessage{

	public:
		//methods
		NetworkMessage();
		~NetworkMessage();

		std::string getHeader();
		std::string getBody();
		virtual void appendData(std::string data);
		std::string getData();

	private:
		//methods
		void makeHeader();

		//arguments
		MessageType mType;
		std::string mHeader;
		std::string mBody;
};

#endif //__NETWORKMESSAGE_H
