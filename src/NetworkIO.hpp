#ifndef __NETWORKCOMMONNETWORKIO_H
#define __NETWORKCOMMONNETWORKIO_H

#include <list>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>

#include "NetworkMessage/NetworkMessageFactory.hpp"

using boost::asio::ip::tcp;

class NetworkIO{

	public:
		//Methods
		NetworkIO(boost::asio::io_service& io_service);
		virtual ~NetworkIO();

		tcp::socket &getSocket();
		virtual void start();
		void sendMessage(NetworkMessage::NetworkMessage *message);

	protected:
		//Methods
		void handleReadHeader(const boost::system::error_code& error);
		void handleReadBody(const boost::system::error_code& error);
		void handleWrite(const boost::system::error_code& error);
		virtual void handleReceive(
			NetworkMessage::NetworkMessage *message
		) = 0;

		//Attributes
		tcp::socket mSocket;
		char *mHeaderBuffer;
		char *mBodyBuffer;
		std::string mMessageBuffer;
		NetworkMessage::NetworkMessageFactory *mNMFactory;
		std::list<NetworkMessage::NetworkMessage> mMessageList;

};

#endif //__NETWORKCOMMONNETWORKIO_H
