#include "PlayerList.hpp"

PlayerList::PlayerList():
	mPlayerList()
{
}

PlayerList::~PlayerList(){
	clear();
}

void PlayerList::addPlayer(Player *player){
	mPlayerList.push_back(player);
}

void PlayerList::addPlayer(std::string nickname){
	mPlayerList.push_back(new Player(nickname));
}

void PlayerList::removePlayer(std::string nickname){

	for(unsigned int i = 0; i < mPlayerList.size(); i++)
		if(mPlayerList[i]->getNickname() == nickname)
			mPlayerList.erase(mPlayerList.begin() + i);

}

void PlayerList::removePlayer(Player *player){

	for(unsigned int i = 0; i < mPlayerList.size(); i++)
		if(mPlayerList[i] == player)
			mPlayerList.erase(mPlayerList.begin() + i);

}

void PlayerList::clear(){
	mPlayerList.clear();
}

Player *PlayerList::get(unsigned int i){
	return mPlayerList[i];
}

Player *PlayerList::operator[](unsigned int i){
	return get(i);
}

Player *PlayerList::getPlayerByName(std::string nickname){

	for(unsigned int i = 0; i < mPlayerList.size(); i++)
		if(mPlayerList[i]->getNickname() == nickname)
			return mPlayerList[i];

	return 0;

}

unsigned int PlayerList::size(){
	return mPlayerList.size();
}
