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


#ifndef __GAMECLIENTCONNECTOR_HPP
#define __GAMECLIENTCONNECTOR_HPP

#include "../NetworkIO.hpp"
#include "../NetworkMessage/NetworkMessageFactory.hpp"

#include <iostream>
#include <list>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace GameClient{

	/// Connects to the server and handles the communication.
	class Connector : public NetworkIO{

		public:
			//Methods
			/// Constructor.
			Connector(
				boost::asio::io_service &io_service,
				tcp::resolver::iterator iterator,
				boost::function<void ()> close,
				boost::function<
					void (NetworkMessage::NetworkMessage *message)
				> receive
			);
			/// Destructor.
			~Connector();
			
			/// Start the connection.
			void start();
			/// Closes the connection.
			void close();

		private:
			//Methods
			/// Handles the receiving of messages.
			void handleReceive(NetworkMessage::NetworkMessage *message);

			//Attributes
			/// Iterator containing the connection information.
			tcp::resolver::iterator mIterator;
			/// Callback function called when the connection is closed/lost.
			boost::function<void ()> mClose;
			/// Callback function called when a message is received.
			boost::function<
				void (NetworkMessage::NetworkMessage *message)
			> mReceive;

	};

};

#endif //__GAMECLIENTCONNECTOR_HPP
