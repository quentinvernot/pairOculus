#ifndef __GAMESERVERSESSION_H
#define __GAMESERVERSESSION_H

#include <iostream>
#include <list>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>

#include "../NetworkMessage/NetworkMessageFactory.hpp"
#include "../Player.hpp"

using boost::asio::ip::tcp;

namespace GameServer{

	class Session{

		public:
			//Methods
			Session(
				boost::asio::io_service& io_service,
				boost::function<
					void (
						NetworkMessage::NetworkMessage *message,
						Session *sourceSession
					)
				> handleReceive
			);
			~Session();

			tcp::socket &getSocket();
			void start();
			void sendMessage(NetworkMessage::NetworkMessage *message);

			Player *getPlayer();
			void setPlayer(Player *player);

		private:
			//Methods
			void handleReadHeader(const boost::system::error_code& error);
			void handleReadBody(const boost::system::error_code& error);
			void handleWrite(const boost::system::error_code& error);

			//Attributes
			tcp::socket mSocket;
			char *mHeaderBuffer;
			char *mBodyBuffer;
			std::string mMessageBuffer;
			NetworkMessage::NetworkMessageFactory *mNMFactory;
			std::list<NetworkMessage::NetworkMessage> mMessageList;
			boost::function<
				void (
					NetworkMessage::NetworkMessage *message,
					Session *sourceSession
				)
			> mHandleReceive;

			Player *mPlayer;

	};

};

#endif //__GAMESERVERSESSION_H
