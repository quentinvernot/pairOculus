#ifndef __GAMECLIENTLISTENER_H
#define __GAMECLIENTLISTENER_H

#include "Connector.hpp"
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

			bool isClosed();

			void setCallbackClose(boost::function<void (void)> callbackClose);
			void setCallbackJoin(
				boost::function<
					void (NetworkMessage::Join *message)
				> callbackJoin
			);
			void setCallbackLeave(
				boost::function<
					void (NetworkMessage::Leave *message)
				> callbackLeave
			);
			void setCallbackJoinAccept(
				boost::function<
					void (NetworkMessage::JoinAccept *message)
				> callbackJoinAccept
			);
			void setCallbackJoinRefuse(
				boost::function<
					void (NetworkMessage::JoinRefuse *message)
				> callbackJoinRefuse
			);
			void setCallbackPlayerJoined(
				boost::function<
					void (NetworkMessage::PlayerJoined *message)
				> callbackPlayerJoined
			);
			void setCallbackPlayerLeft(
				boost::function<
					void (NetworkMessage::PlayerLeft *message)
				> callbackPlayerLeft
			);
			void setCallbackGameStart(
				boost::function<
					void (NetworkMessage::GameStart *message)
				> callbackGameStart
			);
			void setCallbackGameEnd(
				boost::function<
					void (NetworkMessage::GameEnd *message)
				> callbackGameEnd
			);
			void setCallbackPlayerInput(
				boost::function<
					void (NetworkMessage::PlayerInput *message)
				> callbackPlayerInput
			);
			void setCallbackPlayerKilled(
				boost::function<
					void (NetworkMessage::PlayerKilled *message)
				> callbackPlayerKilled
			);
			
			void onClose();

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

			boost::function<void (void)> mCallbackClose;
			boost::function<
				void (NetworkMessage::Join *message)
			> mCallbackJoin;
			boost::function<
				void (NetworkMessage::Leave *message)
			> mCallbackLeave;
			boost::function<
				void (NetworkMessage::JoinAccept *message)
			> mCallbackJoinAccept;
			boost::function<
				void (NetworkMessage::JoinRefuse *message)
			> mCallbackJoinRefuse;
			boost::function<
				void (NetworkMessage::PlayerJoined *message)
			> mCallbackPlayerJoined;
			boost::function<
				void (NetworkMessage::PlayerLeft *message)
			> mCallbackPlayerLeft;
			boost::function<
				void (NetworkMessage::GameStart *message)
			> mCallbackGameStart;
			boost::function<
				void (NetworkMessage::GameEnd *message)
			> mCallbackGameEnd;
			boost::function<
				void (NetworkMessage::PlayerInput *message)
			> mCallbackPlayerInput;
			boost::function<
				void (NetworkMessage::PlayerKilled *message)
			> mCallbackPlayerKilled;

	};

};
#endif //__GAMECLIENTLISTENER_H
