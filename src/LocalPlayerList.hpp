#ifndef __LOCALPLAYERLIST_H
#define __LOCALPLAYERLIST_H

#include "PlayerList.hpp"
#include "LocalPlayer.hpp"
#include <deque>

class LocalPlayerList{

	public:
		//Methods
		LocalPlayerList();
		~LocalPlayerList();

		void addPlayer(LocalPlayer *player);
		void removePlayer(LocalPlayer *player);
		void clear();
		LocalPlayer *get(unsigned int i);
		LocalPlayer *operator[](unsigned int i);
		LocalPlayer *getPlayerByName(std::string nickname);
		unsigned int size();

	private:
		//Attributes
		std::deque<LocalPlayer*> mPlayerList;

};

#endif //__LOCALPLAYERLIST_H
