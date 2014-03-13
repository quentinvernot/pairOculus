#ifndef __LOCALPLAYERLIST_H
#define __LOCALPLAYERLIST_H

#include "PlayerList.hpp"
#include "OgrePlayer.hpp"
#include <deque>

class OgrePlayerList{

	public:
		//Methods
		OgrePlayerList();
		~OgrePlayerList();

		void addPlayer(OgrePlayer *player);
		void removePlayer(OgrePlayer *player);
		void clear();
		OgrePlayer *get(unsigned int i);
		OgrePlayer *operator[](unsigned int i);
		OgrePlayer *getPlayerByName(std::string nickname);
		unsigned int size();

	private:
		//Attributes
		std::deque<OgrePlayer*> mPlayerList;

};

#endif //__LOCALPLAYERLIST_H
