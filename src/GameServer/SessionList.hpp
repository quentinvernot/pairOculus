#ifndef __GAMESERVERSESSIONLIST_H
#define __GAMESERVERSESSIONLIST_H

#include <iostream>
#include <deque>

#include "Session.hpp"

namespace GameServer{

	class SessionList{

		public:
			//Methods
			SessionList();
			~SessionList();

			void addSession(Session *session);
			void removeSession(Session *session);
			Session *get(unsigned int i);
			Session *operator[](unsigned int i);
			Session *getSessionByName(std::string nickname);
			unsigned int size();


		private:
			//Methods
			std::deque<Session*> mSessionList;

			//Attributes

	};

};

#endif //__SESSIONLIST_H
