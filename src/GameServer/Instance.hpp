#ifndef __GAMESERVERINSTANCE_H
#define __GAMESERVERINSTANCE_H

#include "Session.hpp"
#include "SessionList.hpp"
#include "../PlayerList.hpp"

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
			Instance(
				unsigned short port,
				boost::asio::io_service& io_service
			);
			~Instance();

			void start();
			void handleAccept(
				Session *gss,
				const boost::system::error_code& error
			);
			void handleReceive(
				NetworkMessage::NetworkMessage *message,
				Session *sourceSession
			);

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

			//Attributes
			boost::asio::io_service& mIo_service;
			tcp::acceptor mAcceptor;
			Session *mSession;
			SessionList *mSessionList;
			PlayerList *mPlayerList;
			NetworkMessage::NetworkMessageFactory *mNMFactory;

	};

};

#endif //__GAMESERVERINSTANCE_H
