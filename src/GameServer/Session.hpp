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
				int id,
				boost::asio::io_service& io_service,
				boost::function<
					void (
						NetworkMessage::NetworkMessage *message,
						Session *sourceSession
					)
				> receive,
				boost::function<void (Session *sourceSession)> close
			);
			~Session();
			
			void close();

			int getId();
			Player *getPlayer();
			void setPlayer(Player *player);
			bool getIsReady();
			void setIsReady(bool isReady);

		private:
			//Methods
			void handleReceive(NetworkMessage::NetworkMessage *message);

			//Attributes
			int mId;
			boost::function<
				void (
					NetworkMessage::NetworkMessage *message,
					Session *sourceSession
				)
			> mReceive;
			boost::function<void (Session *sourceSession)> mClose;
			Player *mPlayer;
			bool mIsReady;

	};

};

#endif //__GAMESERVERSESSION_H
