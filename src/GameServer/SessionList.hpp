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
			void clear();
			Session *get(unsigned int i);
			Session *operator[](unsigned int i);
			unsigned int size();


		private:
			//Attributes
			std::deque<Session*> mSessionList;

	};

};

#endif //__GAMESERVERSESSIONLIST_H
