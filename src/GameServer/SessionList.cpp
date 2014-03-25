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

#include "SessionList.hpp"

namespace GameServer{

	SessionList::SessionList(){
	}

	SessionList::~SessionList(){
	}

	void SessionList::addSession(Session *session){
		mSessionList.push_back(session);
	}

	void SessionList::removeSession(Session *session){

		for(unsigned int i = 0; i < mSessionList.size(); i++)
			if(mSessionList[i] == session)
				mSessionList.erase(mSessionList.begin() + i);

	}
	
	void SessionList::clear(){
		mSessionList.clear();
	}

	Session *SessionList::get(unsigned int i){
		return mSessionList[i];
	}

	Session *SessionList::operator[](unsigned int i){
		return get(i);
	}

	unsigned int SessionList::size(){
		return mSessionList.size();
	}

};
