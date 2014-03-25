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

#ifndef __GAMESERVERSESSION_HPP
#define __GAMESERVERSESSION_HPP

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

	/// A server session, linked to a client.
	class Session : public NetworkIO{

		public:
			//Methods
			/// Constructor.
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
			/// Destructor.
			~Session();

			/// Closes the connection.
			void close();

			/// Returns the id.
			int getId();
			/// Returns the Player.
			Player *getPlayer();
			/// Set the Player.
			void setPlayer(Player *player);
			/// Returns whether or not the client announced that he was ready.
			bool getIsReady();
			/// Sets the ready flag.
			void setIsReady(bool isReady);

		private:
			//Methods
			/// Handles the receiving of messages.
			void handleReceive(NetworkMessage::NetworkMessage *message);

			//Attributes
			/// The session's id.
			int mId;
			/// Callback function called when a message is received.
			boost::function<
				void (
					NetworkMessage::NetworkMessage *message,
					Session *sourceSession
				)
			> mReceive;
			/// Callback function called when the connection is closed/lost.
			boost::function<void (Session *sourceSession)> mClose;
			/// The session's Player.
			Player *mPlayer;
			/// Flag indicating whether or not the client announced he was ready.
			bool mIsReady;

	};

};

#endif //__GAMESERVERSESSION_HPP
