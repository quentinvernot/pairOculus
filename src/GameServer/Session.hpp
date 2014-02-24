#ifndef __GAMESERVERSESSION_H
#define __GAMESERVERSESSION_H

#include <iostream>
#include <list>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>

#include "../NetworkMessage/NetworkMessageFactory.hpp"
#include "../NetworkIO.hpp"
#include "../Player.hpp"

using boost::asio::ip::tcp;

namespace GameServer{

	class Session : public NetworkIO{

		public:
			//Methods
			Session(
				boost::asio::io_service& io_service,
				boost::function<
					void (
						NetworkMessage::NetworkMessage *message,
						Session *sourceSession
					)
				> receive
			);
			~Session();

			Player *getPlayer();
			void setPlayer(Player *player);

		private:
			//Methods
			void handleReceive(NetworkMessage::NetworkMessage *message);

			//Attributes
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
			> mReceive;
			Player *mPlayer;

	};

};

#endif //__GAMESERVERSESSION_H
