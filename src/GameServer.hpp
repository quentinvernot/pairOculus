#ifndef __GAMESERVER_H
#define __GAMESERVER_H

#include "GameServerInstance.hpp"

#include <iostream>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class GameServer{

	public:
		//Methods
		GameServer();
		~GameServer();
		
		void start();
		void stop();

	private:
		//Methods

		//Attributes
		boost::asio::io_service mIo_service;
		GameServerInstance *mInstance;

};

#endif //__GAMESERVER_H
