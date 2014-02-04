#ifndef __GAMESERVERINSTANCE_H
#define __GAMESERVERINSTANCE_H

#include "GameSession.hpp"

#include <iostream>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class GameServerInstance{

	public:
		//Methods
		GameServerInstance(
			unsigned short port,
			boost::asio::io_service& io_service
		);
		~GameServerInstance();

		void start();
		void handleAccept(
			GameSession *gameSession,
			const boost::system::error_code& error
		);

	private:
		//Methods

		//Attributes
		boost::asio::io_service& mIo_service;
		tcp::acceptor mAcceptor;
		GameSession *mGameSession;

};

#endif //__GAMESERVERINSTANCE_H
