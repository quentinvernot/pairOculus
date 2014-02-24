#ifndef __GAMECLIENTLISTENER_H
#define __GAMECLIENTLISTENER_H

#include "../NetworkIO.hpp"
#include "../NetworkMessage/NetworkMessageFactory.hpp"

#include <iostream>
#include <list>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace GameClient{

	class Listener : public NetworkIO{

		public:
			//Methods
			Listener(
				boost::asio::io_service &io_service,
				tcp::resolver::iterator iterator,
				boost::function<
					void (NetworkMessage::NetworkMessage *message)
				> receive
			);
			~Listener();
			
			void start();

		private:
			//Methods
			void handleReceive(NetworkMessage::NetworkMessage *message);

			//Attributes
			tcp::resolver::iterator mIterator;
			boost::function<
				void (NetworkMessage::NetworkMessage *message)
			> mReceive;

	};

};

#endif //__GAMECLIENTLISTENER_H
