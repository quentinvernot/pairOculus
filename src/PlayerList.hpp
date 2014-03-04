#ifndef __PLAYERLIST_H
#define __PLAYERLIST_H

#include "Player.hpp"
#include <deque>

class PlayerList{

	public:
		//Methods
		PlayerList();
		~PlayerList();

		virtual void addPlayer(Player *player);
		void addPlayer(std::string nickname);
		void removePlayer(std::string nickname);
		virtual void removePlayer(Player *player);
		void clear();
		virtual Player *get(unsigned int i);
		virtual Player *operator[](unsigned int i);
		virtual Player *getPlayerByName(std::string nickname);
		unsigned int size();

	private:
		//Attributes
		std::deque<Player*> mPlayerList;

};

#endif //__PLAYERLIST_H