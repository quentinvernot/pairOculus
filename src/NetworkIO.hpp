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

#ifndef __NETWORKIO_HPP
#define __NETWORKIO_HPP

#include <cstring>
#include <list>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>

#include "NetworkMessage/NetworkMessageFactory.hpp"

using boost::asio::ip::tcp;

/** A network sender and receiver class.
 *  Use it by extending it and implementing its methods.
 */
class NetworkIO{

	public:
		//Methods
		/// Constructor.
		NetworkIO(boost::asio::io_service& io_service);
		/// Destructor.
		virtual ~NetworkIO();

		/// Returns the socket.
		tcp::socket &getSocket();
		/// Returns whether or not the connection is closed/lost.
		bool isClosed();

		/// Starts the connection.
		virtual void start();
		/// Closes the connection.
		virtual void close();
		/// Adds the given message to the queue.
		void sendMessage(NetworkMessage::NetworkMessage *message);

	protected:
		//Methods
		/// Handles the reading of the first part of a message.
		void handleReadHeader(const boost::system::error_code& error);
		/// Handles the reading of the last part of a message.
		void handleReadBody(const boost::system::error_code& error);
		/// Sends a message.
		void handleWrite(const boost::system::error_code& error);
		/// Should handle the receiving of messages.
		virtual void handleReceive(NetworkMessage::NetworkMessage *message) = 0;

		//Attributes
		/// The socket.
		tcp::socket mSocket;
		/// Buffer for received headers.
		char *mHeaderBuffer;
		/// Buffer for received bodies.
		char *mBodyBuffer;
		/// Buffer for the complete received message.
		std::string mMessageBuffer;
		/// Message factory.
		NetworkMessage::NetworkMessageFactory *mNMFactory;
		/// List of messages that need to be delivered.
		std::list<NetworkMessage::NetworkMessage *> mMessageList;
		/// Flag indicating whether or not the connection is closed.
		bool mIsClosed;

};

#endif //__NETWORKIO_HPP
