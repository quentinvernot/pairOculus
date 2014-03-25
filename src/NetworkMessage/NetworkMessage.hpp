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

#ifndef __NETWORKMESSAGE_HPP
#define __NETWORKMESSAGE_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

namespace NetworkMessage{

	/// Every message types.
	enum MessageType {
		JOIN,			//! Client joins the server.
		LEAVE,			//! Client leaves the server.
		JOINACCEPT,		//! Server accepts the new client.
		JOINREFUSE,		//! Server refuses the new client.
		PLAYERJOINED,	//! Server advertises a new client.
		PLAYERLEFT,		//! Server advertises a lost client.
		GAMESTART,		//! Client wants to start / Server decides to start.
		GAMEEND,		//! Server decides to end.
		PLAYERINPUT,	//! A player sent relevant input.
		PLAYERKILLED	//! A player was killed.
	};

	/// Miscellaneous constants.
	enum {
		HEADERLENGTH = 8,		//! Size of the header
		MAXBODYLENGTH = 1024	//! Maximum size of the body.
	};

	/// A generic network message.
	class NetworkMessage{

		public:
			//Methods
			/// Constructor.
			NetworkMessage(MessageType type);
			/// Destructor.
			~NetworkMessage();

			/// Returns the type of message.
			MessageType getType();
			/// Returns the message's header.
			std::string getHeader();
			/// Returns the message's body.
			std::string getBody();
			/// Returns the full message.
			std::string getMessage();

		protected:
			//Attributes
			/// Type of message.
			MessageType mType;
			/** Message's header.
			 *  \remarks
			 *  	The header's format is as follow :
			 *  	<Message type>\n<Body length>\n
			 * 		<Message type> is 2 characters long.
			 * 		<Body length> is 4 characters long.
			 */
			std::string mHeader;
			/// Message's body.
			std::string mBody;

		private:
			//Methods
			/// Builds the header.
			void makeHeader();
			/// Ensures that the body is not longer than its max size.
			void formatBody();

	};

};

#endif //__NETWORKMESSAGE_HPP
