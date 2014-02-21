#ifndef __GAMESERVERSESSIONLIST_H
#define __GAMESERVERSESSIONLIST_H

#include <iostream>
#include <deque>

#include "GameServerSession.hpp"

class GameServerSessionList{

	public:
		//Methods
		GameServerSessionList();
		~GameServerSessionList();

		void addSession(GameServerSession *session);
		void removeSession(GameServerSession *session);
		GameServerSession *get(unsigned int i);
		GameServerSession *operator[](unsigned int i);
		GameServerSession *getSessionByName(std::string nickname);
		unsigned int size();


	private:
		//Methods
		std::deque<GameServerSession*> mSessionList;

		//Attributes

};

#endif //__GAMESERVERSESSIONLIST_H
