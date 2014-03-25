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

#ifndef __GAMESERVERSESSIONLIST_HPP
#define __GAMESERVERSESSIONLIST_HPP

#include <iostream>
#include <deque>

#include "Session.hpp"

namespace GameServer{

	/// A list of Sessions.
	class SessionList{

		public:
			//Methods
			/// Constructor.
			SessionList();
			/// Destructor.
			~SessionList();

			/// Adds a Session.
			void addSession(Session *session);
			/// Removes a Session.
			void removeSession(Session *session);
			/// Clears the list.
			void clear();
			/// Returns the Session at the specified index.
			Session *get(unsigned int i);
			Session *operator[](unsigned int i);
			/// Returns the number of Sessions.
			unsigned int size();


		private:
			//Attributes
			/// The list itself.
			std::deque<Session*> mSessionList;

	};

};

#endif //__GAMESERVERSESSIONLIST_HPP
