#include "OgrePlayerList.hpp"

OgrePlayerList::OgrePlayerList(){
}

OgrePlayerList::~OgrePlayerList(){
	clear();
}

void OgrePlayerList::addPlayer(OgrePlayer *player){
	mPlayerList.push_back(player);
}

void OgrePlayerList::removePlayer(OgrePlayer *player){

	for(unsigned int i = 0; i < mPlayerList.size(); i++)
		if(mPlayerList[i] == player)
			mPlayerList.erase(mPlayerList.begin() + i);

}

void OgrePlayerList::clear(){
	mPlayerList.clear();
}

OgrePlayer *OgrePlayerList::get(unsigned int i){
	return mPlayerList[i];
}

OgrePlayer *OgrePlayerList::operator[](unsigned int i){
	return get(i);
}

OgrePlayer *OgrePlayerList::getPlayerByName(std::string nickname){

	for(unsigned int i = 0; i < mPlayerList.size(); i++)
		if(mPlayerList[i]->getNickname() == nickname)
			return mPlayerList[i];

	return 0;

}

unsigned int OgrePlayerList::size(){
	return mPlayerList.size();
}
