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

#ifndef __OGREPLAYERLIST_HPP
#define __OGREPLAYERLIST_HPP

#include "OgrePlayer.hpp"
#include <deque>

/** A list of OgrePlayers.
 *  This is a wrapper for a std::deque, allowing the acces by name or index, and
 *  ensuring that removed elements are deleted.
 */
class OgrePlayerList{

	public:
		//Methods
		/// Default constructor.
		OgrePlayerList();
		/// Destructor.
		~OgrePlayerList();

		/// Adds the given Player to the list.
		void addPlayer(OgrePlayer *player);
		/// Removes a Player from the list.
		void removePlayer(OgrePlayer *player);
		/// Removes all the Players from the list.
		void clear();
		/// Returns the Player at the specified index.
		OgrePlayer *get(unsigned int i);
		OgrePlayer *operator[](unsigned int i);
		/** Returns the Player corresponding to the nickname.
		 *  \remarks
		 * 		Returns NULL if no player is found.
		 */
		OgrePlayer *getPlayerByName(std::string nickname);
		/// Returns the size of the list.
		unsigned int size();

	private:
		//Attributes
		/// The list.
		std::deque<OgrePlayer*> mPlayerList;

};

#endif //__OGREPLAYERLIST_HPP
