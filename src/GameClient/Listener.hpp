#ifndef __GAMECLIENTLISTENER_H
#define __GAMECLIENTLISTENER_H

#include "../NetworkMessage/NetworkMessage.hpp"
#include "../NetworkMessage/NetworkMessageFactory.hpp"

#include <iostream>
#include <list>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace GameClient{

	class Listener{

		public:
			//Methods
			Listener(
				boost::asio::io_service &io_service,
				tcp::resolver::iterator iterator,
				boost::function<
					void (NetworkMessage::NetworkMessage *message)
				> handleReceive
			);
			~Listener();

			void start();
			void sendMessage(NetworkMessage::NetworkMessage *message);

		private:
			//Methods
			void handleConnect(const boost::system::error_code& error);
			void handleReadHeader(const boost::system::error_code& error);
			void handleReadBody(const boost::system::error_code& error);
			void handleWrite(const boost::system::error_code& error);

			//Attributes
			tcp::resolver::iterator mIterator;
			tcp::socket mSocket;
			char *mHeaderBuffer;
			char *mBodyBuffer;
			std::string mMessageBuffer;
			NetworkMessage::NetworkMessageFactory *mNMFactory;
			std::list<NetworkMessage::NetworkMessage> mMessageList;
			boost::function<
				void (NetworkMessage::NetworkMessage *message)
			> mHandleReceive;

	};

};

#endif //__GAMECLIENTLISTENER_H
