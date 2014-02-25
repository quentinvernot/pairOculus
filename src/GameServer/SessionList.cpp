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
