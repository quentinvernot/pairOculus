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

#ifndef __NETWORKMESSAGEPLAYERJOINED_HPP
#define __NETWORKMESSAGEPLAYERJOINED_HPP

#include <string>
#include <sstream>
#include "../Player.hpp"
#include "NetworkMessage.hpp"

namespace NetworkMessage{

	/** Message sent by the server when a player joins.
	 *  Contains the new player's nickname and coordinates.
	 */
	class PlayerJoined : public NetworkMessage{

		public:
			//Methods
			/// Constructor. Builds the message from a Player.
			PlayerJoined(Player *player);
			/// Constructor. Builds the message from the Players informations.
			PlayerJoined(
				std::string nickname,
				double x,
				double y,
				double z
			);
			/// Destructor.
			~PlayerJoined();

			/// Gets the player's nickname.
			std::string getNickname();
			/// Gets the body's position on the X axis.
			virtual double getX();
			/// Gets the body's position on the Y axis.
			virtual double getY();
			/// Gets the body's position on the Z axis.
			virtual double getZ();

		private:
			//Methods
			/// Builds the message's body.
			void buildSelf();

			//Attributes
			/// The player's nickname.
			std::string mNickname;
			/// The player's body's position on the X axis.
			double mX;
			/// The player's body's position on the Y axis.
			double mY;
			/// The player's body's position on the Z axis.
			double mZ;

	};

};

#endif //__NETWORKMESSAGEPLAYERJOINED_HPP
