#ifndef __GAMECLIENTCONNECTOR_H
#define __GAMECLIENTCONNECTOR_H

#include "../NetworkIO.hpp"
#include "../NetworkMessage/NetworkMessageFactory.hpp"

#include <iostream>
#include <list>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace GameClient{

	class Connector : public NetworkIO{

		public:
			//Methods
			Connector(
				boost::asio::io_service &io_service,
				tcp::resolver::iterator iterator,
				boost::function<void ()> close,
				boost::function<
					void (NetworkMessage::NetworkMessage *message)
				> receive
			);
			~Connector();
			
			void start();
			void close();

		private:
			//Methods
			void handleReceive(NetworkMessage::NetworkMessage *message);

			//Attributes
			tcp::resolver::iterator mIterator;
			boost::function<void ()> mClose;
			boost::function<
				void (NetworkMessage::NetworkMessage *message)
			> mReceive;

	};

};

#endif //__GAMECLIENTCONNECTOR_H
