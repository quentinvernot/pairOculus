#include "GameServerSessionList.hpp"

GameServerSessionList::GameServerSessionList(){
}

GameServerSessionList::~GameServerSessionList(){
}

void GameServerSessionList::addSession(GameServerSession *session){
	mSessionList.push_back(session);
}

void GameServerSessionList::removeSession(GameServerSession *session){

	for(unsigned int i = 0; i < mSessionList.size(); i++)
		if(mSessionList[i] == session)
			mSessionList.erase(mSessionList.begin() + i);

}

GameServerSession *GameServerSessionList::get(unsigned int i){
	return mSessionList[i];
}

GameServerSession *GameServerSessionList::operator[](unsigned int i){
	return get(i);
}

unsigned int GameServerSessionList::size(){
	return mSessionList.size();
}
