#ifndef __PLAYERLIST_H
#define __PLAYERLIST_H

#include "Player.hpp"
#include <deque>

class PlayerList{

	public:
		//Methods
		PlayerList();
		~PlayerList();

		void addPlayer(Player *player);
		void addPlayer(std::string nickname);
		void removePlayer(std::string nickname);
		Player *get(unsigned int i);
		Player *operator[](unsigned int i);
		Player *getPlayerByName(std::string nickname);
		unsigned int size();

	private:
		//Methods

		//Attributes
		std::deque<Player*> mPlayerList;

};

#endif //__PLAYERLIST_H
