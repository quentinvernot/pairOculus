#include "GameSession.hpp"

GameSession::GameSession(boost::asio::io_service& io_service):
	mSocket(io_service)
{
}

GameSession::~GameSession(){
}

tcp::socket &GameSession::getSocket(){return mSocket;}

void GameSession::start(){}
