#ifndef __GAMECLIENT_H
#define __GAMECLIENT_H

#include "Listener.hpp"
#include "../NetworkMessage/NetworkMessage.hpp"
#include "../NetworkMessage/NetworkMessageFactory.hpp"

#include <iostream>
#include <string>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

using boost::asio::ip::tcp;

namespace GameClient{

	class GameClient{

		public:
			//Methods
			GameClient(
				std::string address,
				std::string port
			);
			~GameClient();
			
			void start();
			void stop();
			void sendMessage(NetworkMessage::NetworkMessage *message);
			void handleReceive(NetworkMessage::NetworkMessage *message);

		private:
			//Methods
			void onJoin(NetworkMessage::Join *message);
			void onLeave(NetworkMessage::Leave *message);
			void onJoinAccept(NetworkMessage::JoinAccept *message);
			void onJoinRefuse(NetworkMessage::JoinRefuse *message);
			void onPlayerJoined(NetworkMessage::PlayerJoined *message);
			void onPlayerLeft(NetworkMessage::PlayerLeft *message);
			void onGameStart(NetworkMessage::GameStart *message);
			void onGameEnd(NetworkMessage::GameEnd *message);
			void onPlayerInput(NetworkMessage::PlayerInput *message);
			void onPlayerKilled(NetworkMessage::PlayerKilled *message);

			//Attributes
			boost::asio::io_service mIo_service;
			Listener *mListener;
			boost::thread *mThread;

	};

};
#endif //__GAMECLIENT_H
