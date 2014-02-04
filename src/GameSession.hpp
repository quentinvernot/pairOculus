#ifndef __GAMESESSION_H
#define __GAMESESSION_H

#include <iostream>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class GameSession{

	public:
		//Methods
		GameSession(boost::asio::io_service& io_service);
		~GameSession();

		tcp::socket &getSocket();
		void start();

	private:
		//Methods

		//Attributes
		tcp::socket mSocket;

};

#endif //__GAMESESSION_H
