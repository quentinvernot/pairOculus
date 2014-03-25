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

#ifndef __GAMESERVERINSTANCE_HPP
#define __GAMESERVERINSTANCE_HPP

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

	/// A server instance.
	class Instance{

		public:
			//Methods
			/// Constructor.
			Instance(unsigned short port);
			/// Destructor.
			~Instance();

			/// Starts listening for clients.
			void start();
			/// Stops listening for clients and stop the connections.
			void stop();
			/// Handles the establishement of a session.
			void handleAccept(
				Session *gss,
				const boost::system::error_code& error
			);
			/// Action taken when a message is received.
			void onReceive(
				NetworkMessage::NetworkMessage *message,
				Session *sourceSession
			);
			/// Action taken when a session closes/loses its connection.
			void onClose(Session *sourceSession);

		private:
			//Methods
			/** Action taken when a JOIN message is received.
			 *  Checks if the new client can join and accepts or refuses it.
			 *  Also advertises the new client to everyone if it was accepted.
			 */
			void onJoin(
				NetworkMessage::Join *message,
				Session *sourceSession
			);
			/** Action taken when a LEAVE message is received.
			 *  Removes the player from the list and advertises the event to all
			 *  other sessions.
			 */
			void onLeave(
				NetworkMessage::Leave *message,
				Session *sourceSession
			);
			/** Action taken when a JOINACCEPT message is received.
			 *  \remarks
			 * 		This should not happen to the server, no action is taken.
			 */
			void onJoinAccept(
				NetworkMessage::JoinAccept *message,
				Session *sourceSession
			);
			/** Action taken when a JOINREFUSE message is received.
			 *  \remarks
			 * 		This should not happen to the server, no action is taken.
			 */
			void onJoinRefuse(
				NetworkMessage::JoinRefuse *message,
				Session *sourceSession
			);
			/** Action taken when a PLAYERJOINED message is received.
			 *  \remarks
			 * 		This should not happen to the server, no action is taken.
			 */
			void onPlayerJoined(
				NetworkMessage::PlayerJoined *message,
				Session *sourceSession
			);
			/** Action taken when a PLAYERLEFT message is received.
			 *  \remarks
			 * 		This should not happen to the server, no action is taken.
			 */
			void onPlayerLeft(
				NetworkMessage::PlayerLeft *message,
				Session *sourceSession
			);
			/** Action taken when a GAMESTART message is received.
			 *  Sets the ready flag of the correcponding session to true.
			 *  If all sessions are ready, sends a GAMESTART to everyone.
			 */
			void onGameStart(
				NetworkMessage::GameStart *message,
				Session *sourceSession
			);
			/// Action taken when a GAMEEND message is received.
			void onGameEnd(
				NetworkMessage::GameEnd *message,
				Session *sourceSession
			);
			/** Action taken when a PLAYERINPUT message is received.
			 *  Sends the inputs to everyone else.
			 */
			void onPlayerInput(
				NetworkMessage::PlayerInput *message,
				Session *sourceSession
			);
			/** Action taken when a PLAYERKILLED message is received.
			 *  Sends the event to everyone else.
			 */
			void onPlayerKilled(
				NetworkMessage::PlayerKilled *message,
				Session *sourceSession
			);

			/// Sends a JOINACCEPT to the new client.
			void sendJoinAccept(Session *sourceSession);
			/// Sends a JOINREFUSE to the new client.
			void sendJoinRefuse(
				Session *sourceSession,
				std::string reason
			);
			/// Sends a PLAYERJOINED to every non-new clients.
			void sendPlayerJoined(Player *player);
			/// Sends a PLAYERLEFT to everyone.
			void sendPlayerLeft(std::string nickname);
			/// Sends a GAMESTART to everyone.
			void sendGameStart();
			/// Sends a GAMEEND to everyone.
			void sendGameEnd();
			/// Sends a PAYERINPUT to everyone but the source.
			void sendPlayerInput(
				std::string nickname,
				NetworkMessage::PlayerInput *message
			);
			/// Sends a PLAYERKILLED to everyone but the source.
			void sendPlayerKilled(
				std::string nickname,
				NetworkMessage::PlayerKilled *message
			);

			//Attributes
			/// Boost io_service.
			boost::asio::io_service mIo_service;
			/// Boost acceptor.
			tcp::acceptor mAcceptor;
			/// A temporary Session used in multiple methods.
			Session *mSession;
			/// List of Sessions
			SessionList *mSessionList;
			/// The message factory.
			NetworkMessage::NetworkMessageFactory *mNMFactory;

			/// The list of Players.
			PlayerList *mPlayerList;
			/// The Map.
			Map *mMap;
			/// Number of opened Sessions.
			int mOpenedSessions;
			/// Flag indicating whether or not the game is running.
			bool mGameRunning;
			/// Flag indicating whether or not the game has ended.
			bool mGameEnded;

	};

};

#endif //__GAMESERVERINSTANCE_HPP
