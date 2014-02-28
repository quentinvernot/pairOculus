#include "LocalPlayerList.hpp"

LocalPlayerList::LocalPlayerList(){
}

LocalPlayerList::~LocalPlayerList(){
	clear();
}

void LocalPlayerList::addPlayer(LocalPlayer *player){
	mPlayerList.push_back(player);
}

void LocalPlayerList::removePlayer(LocalPlayer *player){

	for(unsigned int i = 0; i < mPlayerList.size(); i++)
		if(mPlayerList[i] == player)
			mPlayerList.erase(mPlayerList.begin() + i);

}

void LocalPlayerList::clear(){
	mPlayerList.clear();
}

LocalPlayer *LocalPlayerList::get(unsigned int i){
	return mPlayerList[i];
}

LocalPlayer *LocalPlayerList::operator[](unsigned int i){
	return get(i);
}

LocalPlayer *LocalPlayerList::getPlayerByName(std::string nickname){

	for(unsigned int i = 0; i < mPlayerList.size(); i++)
		if(mPlayerList[i]->getNickname() == nickname)
			return mPlayerList[i];

	return 0;

}

unsigned int LocalPlayerList::size(){
	return mPlayerList.size();
}
