/*
This source file is part of pairOculus, a student project aiming at creating a
simple 3D multiplayer game for the Oculus Rift.

Repository can be found here : https://github.com/Target6/pairOculus 

Copyright (c) 2013 Target6

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef __GAMECLIENTLISTENER_HPP
#define __GAMECLIENTLISTENER_HPP

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

	/// Class handling the client operations and callbacks.
	class Listener{

		public:
			//Methods
			/// Constructor.
			Listener(
				std::string address,
				std::string port
			);
			/// Destructor.
			~Listener();

			/// Starts the connection.
			void start();
			/// Stops the connection.
			void stop();
			/// Sends the given message.
			void sendMessage(NetworkMessage::NetworkMessage *message);
			/// Handles the receiving of messages.
			void handleReceive(NetworkMessage::NetworkMessage *message);

			/// Returnd whether or not the connection is closed.
			bool isClosed();

			/// Sets the callback function called when the connection is closed.
			void setCallbackClose(boost::function<void (void)> callbackClose);
			/// Sets the callback function called when JOIN is received.
			void setCallbackJoin(
				boost::function<
					void (NetworkMessage::Join *message)
				> callbackJoin
			);
			/// Sets the callback function called when LEAVE is received.
			void setCallbackLeave(
				boost::function<
					void (NetworkMessage::Leave *message)
				> callbackLeave
			);
			/// Sets the callback function called when JOINACCEPT is received.
			void setCallbackJoinAccept(
				boost::function<
					void (NetworkMessage::JoinAccept *message)
				> callbackJoinAccept
			);
			/// Sets the callback function called when JOINREFUSE is received.
			void setCallbackJoinRefuse(
				boost::function<
					void (NetworkMessage::JoinRefuse *message)
				> callbackJoinRefuse
			);
			/// Sets the callback function called when PLAYERJOINED is received.
			void setCallbackPlayerJoined(
				boost::function<
					void (NetworkMessage::PlayerJoined *message)
				> callbackPlayerJoined
			);
			/// Sets the callback function called when PLAYERLEFT is received.
			void setCallbackPlayerLeft(
				boost::function<
					void (NetworkMessage::PlayerLeft *message)
				> callbackPlayerLeft
			);
			/// Sets the callback function called when GAMESTART is received.
			void setCallbackGameStart(
				boost::function<
					void (NetworkMessage::GameStart *message)
				> callbackGameStart
			);
			/// Sets the callback function called when GAMEEND is received.
			void setCallbackGameEnd(
				boost::function<
					void (NetworkMessage::GameEnd *message)
				> callbackGameEnd
			);
			/// Sets the callback function called when PLAYERINPUT is received.
			void setCallbackPlayerInput(
				boost::function<
					void (NetworkMessage::PlayerInput *message)
				> callbackPlayerInput
			);
			/// Sets the callback function called when PLAYERKILLED is received.
			void setCallbackPlayerKilled(
				boost::function<
					void (NetworkMessage::PlayerKilled *message)
				> callbackPlayerKilled
			);
			
			/// Action when the connection is closed/lost.
			void onClose();

		private:
			//Methods
			/// Action when a JOIN is received.
			void onJoin(NetworkMessage::Join *message);
			/// Action when a LEAVE is received.
			void onLeave(NetworkMessage::Leave *message);
			/// Action when a JOINACCEPT is received.
			void onJoinAccept(NetworkMessage::JoinAccept *message);
			/// Action when a JOINREFUSE is received.
			void onJoinRefuse(NetworkMessage::JoinRefuse *message);
			/// Action when a PLAYERJOINED is received.
			void onPlayerJoined(NetworkMessage::PlayerJoined *message);
			/// Action when a PLAYERLEFT is received.
			void onPlayerLeft(NetworkMessage::PlayerLeft *message);
			/// Action when a GAMESTART is received.
			void onGameStart(NetworkMessage::GameStart *message);
			/// Action when a GAMEEND is received.
			void onGameEnd(NetworkMessage::GameEnd *message);
			/// Action when a PLAYERINPUT is received.
			void onPlayerInput(NetworkMessage::PlayerInput *message);
			/// Action when a PLAYERKILLED is received.
			void onPlayerKilled(NetworkMessage::PlayerKilled *message);

			//Attributes
			/// Boost io_service.
			boost::asio::io_service mIo_service;
			/// The Connector.
			Connector *mConnector;
			/// Connector thread.
			boost::thread *mThread;

			/// Callback function called when the connection is closed.
			boost::function<void (void)> mCallbackClose;
			/// Callback function called when JOIN is received.
			boost::function<
				void (NetworkMessage::Join *message)
			> mCallbackJoin;
			/// Callback function called when LEAVE is received.
			boost::function<
				void (NetworkMessage::Leave *message)
			> mCallbackLeave;
			/// Callback function called when JOINACCEPT is received.
			boost::function<
				void (NetworkMessage::JoinAccept *message)
			> mCallbackJoinAccept;
			/// Callback function called when JOINREFUSE is received.
			boost::function<
				void (NetworkMessage::JoinRefuse *message)
			> mCallbackJoinRefuse;
			/// Callback function called when PLAYERJOINED is received.
			boost::function<
				void (NetworkMessage::PlayerJoined *message)
			> mCallbackPlayerJoined;
			/// Callback function called when PLAYERLEFT is received.
			boost::function<
				void (NetworkMessage::PlayerLeft *message)
			> mCallbackPlayerLeft;
			/// Callback function called when GAMESTART is received.
			boost::function<
				void (NetworkMessage::GameStart *message)
			> mCallbackGameStart;
			/// Callback function called when GAMEEND is received.
			boost::function<
				void (NetworkMessage::GameEnd *message)
			> mCallbackGameEnd;
			/// Callback function called when PLAYERINPUT is received.
			boost::function<
				void (NetworkMessage::PlayerInput *message)
			> mCallbackPlayerInput;
			/// Callback function called when PLAYERKILLED is received.
			boost::function<
				void (NetworkMessage::PlayerKilled *message)
			> mCallbackPlayerKilled;

	};

};
#endif //__GAMECLIENTLISTENER_HPP
