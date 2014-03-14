#ifndef __GAMESERVERINSTANCE_H
#define __GAMESERVERINSTANCE_H

#include "Session.hpp"
#include "SessionList.hpp"
#include "../PlayerList.hpp"
#include "../Map.hpp"

#include <iostream>
#include <deque>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace GameServer{

	class Instance{

		public:
			//Methods
			Instance(unsigned short port);
			~Instance();

			void start();
			void stop();
			void handleAccept(
				Session *gss,
				const boost::system::error_code& error
			);
			void onReceive(
				NetworkMessage::NetworkMessage *message,
				Session *sourceSession
			);
			void onClose(Session *sourceSession);

		private:
			//Methods
			void onJoin(
				NetworkMessage::Join *message,
				Session *sourceSession
			);
			void onLeave(
				NetworkMessage::Leave *message,
				Session *sourceSession
			);
			void onJoinAccept(
				NetworkMessage::JoinAccept *message,
				Session *sourceSession
			);
			void onJoinRefuse(
				NetworkMessage::JoinRefuse *message,
				Session *sourceSession
			);
			void onPlayerJoined(
				NetworkMessage::PlayerJoined *message,
				Session *sourceSession
			);
			void onPlayerLeft(
				NetworkMessage::PlayerLeft *message,
				Session *sourceSession
			);
			void onGameStart(
				NetworkMessage::GameStart *message,
				Session *sourceSession
			);
			void onGameEnd(
				NetworkMessage::GameEnd *message,
				Session *sourceSession
			);
			void onPlayerInput(
				NetworkMessage::PlayerInput *message,
				Session *sourceSession
			);
			void onPlayerKilled(
				NetworkMessage::PlayerKilled *message,
				Session *sourceSession
			);
			
			void sendJoinAccept(Session *sourceSession);
			void sendJoinRefuse(Session *sourceSession);
			void sendPlayerJoined(Player *player);
			void sendPlayerLeft(std::string nickname);
			void sendGameStart();
			void sendGameEnd();
			void sendPlayerInput(
				std::string nickname,
				NetworkMessage::PlayerInput *message
			);
			void sendPlayerKilled(
				std::string nickname,
				NetworkMessage::PlayerKilled *message
			);

			//Attributes
			boost::asio::io_service mIo_service;
			tcp::acceptor mAcceptor;
			Session *mSession;
			SessionList *mSessionList;
			NetworkMessage::NetworkMessageFactory *mNMFactory;

			PlayerList *mPlayerList;
			Map *mMap;
			int mOpenedSessions;
			bool mGameStarted;

	};

};

#endif //__GAMESERVERINSTANCE_H
