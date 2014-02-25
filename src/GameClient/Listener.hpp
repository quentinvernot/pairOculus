#ifndef __GAMECLIENTLISTENER_H
#define __GAMECLIENTLISTENER_H

#include "Connector.hpp"
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

	class Listener{

		public:
			//Methods
			Listener(
				std::string address,
				std::string port
			);
			~Listener();
			
			void start();
			void stop();
			void sendMessage(NetworkMessage::NetworkMessage *message);
			void handleReceive(NetworkMessage::NetworkMessage *message);

			void setCallbackJoin(
				boost::function<
					void (NetworkMessage::NetworkMessage *message)
				> callbackJoin
			);
			void setCallbackLeave(
				boost::function<
					void (NetworkMessage::NetworkMessage *message)
				> callbackLeave
			);
			void setCallbackJoinAccept(
				boost::function<
					void (NetworkMessage::NetworkMessage *message)
				> callbackJoinAccept
			);
			void setCallbackJoinRefuse(
				boost::function<
					void (NetworkMessage::NetworkMessage *message)
				> callbackJoinRefuse
			);
			void setCallbackPlayerJoined(
				boost::function<
					void (NetworkMessage::NetworkMessage *message)
				> callbackPlayerJoined
			);
			void setCallbackPlayerLeft(
				boost::function<
					void (NetworkMessage::NetworkMessage *message)
				> callbackPlayerLeft
			);
			void setCallbackGameStart(
				boost::function<
					void (NetworkMessage::NetworkMessage *message)
				> callbackGameStart
			);
			void setCallbackGameEnd(
				boost::function<
					void (NetworkMessage::NetworkMessage *message)
				> callbackGameEnd
			);
			void setCallbackPlayerInput(
				boost::function<
					void (NetworkMessage::NetworkMessage *message)
				> callbackPlayerInput
			);
			void setCallbackPlayerKilled(
				boost::function<
					void (NetworkMessage::NetworkMessage *message)
				> callbackPlayerKilled
			);

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
			Connector *mConnector;
			boost::thread *mThread;

			boost::function<
				void (NetworkMessage::NetworkMessage *message)
			> mCallbackJoin;
			boost::function<
				void (NetworkMessage::NetworkMessage *message)
			> mCallbackLeave;
			boost::function<
				void (NetworkMessage::NetworkMessage *message)
			> mCallbackJoinAccept;
			boost::function<
				void (NetworkMessage::NetworkMessage *message)
			> mCallbackJoinRefuse;
			boost::function<
				void (NetworkMessage::NetworkMessage *message)
			> mCallbackPlayerJoined;
			boost::function<
				void (NetworkMessage::NetworkMessage *message)
			> mCallbackPlayerLeft;
			boost::function<
				void (NetworkMessage::NetworkMessage *message)
			> mCallbackGameStart;
			boost::function<
				void (NetworkMessage::NetworkMessage *message)
			> mCallbackGameEnd;
			boost::function<
				void (NetworkMessage::NetworkMessage *message)
			> mCallbackPlayerInput;
			boost::function<
				void (NetworkMessage::NetworkMessage *message)
			> mCallbackPlayerKilled;

	};

};
#endif //__GAMECLIENTLISTENER_H
