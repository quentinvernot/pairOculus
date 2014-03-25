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

#ifndef __NETWORKMESSAGEJOINACCEPT_HPP
#define __NETWORKMESSAGEJOINACCEPT_HPP

#include <string>
#include <sstream>
#include <deque>
#include "NetworkMessage.hpp"
#include "../PlayerList.hpp"
#include "../Map.hpp"

namespace NetworkMessage{

	/** Message sent by the server to a new player.
	 *  Contains the information necessary to build the Map and the current 
	 *  PlayerList.
	 */
	class JoinAccept : public NetworkMessage{

		public:
			//Methods
			/// Constructor.
			JoinAccept(
				PlayerList *playerList,
				unsigned int mapHeight,
				unsigned int mapWidth,
				time_t seed
			);
			/// Destructor.
			~JoinAccept();

			/// Returns the PlayerList.
			PlayerList *getPlayerList();
			/// Returns the Map's height.
			unsigned int getMapHeight();
			/// Returns the Map's width.
			unsigned int getMapWidth();
			/// Returns the random seed used to generate the Map.
			time_t getSeed();

		private:
			//Attributes
			/// The PlayerList.
			PlayerList mPlayerList;
			/// The Map Height.
			unsigned int mMapHeight;
			/// The Map Width.
			unsigned int mMapWidth;
			/// The random seed used to generate the Map.
			time_t mSeed;

	};

};

#endif //__NETWORKMESSAGEJOINACCEPT_HPP
