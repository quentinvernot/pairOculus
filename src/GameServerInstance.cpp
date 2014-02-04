#include "GameServerInstance.hpp"

GameServerInstance::GameServerInstance(
	unsigned short port,
	boost::asio::io_service& io_service
) :
	mIo_service(io_service),
	mAcceptor(mIo_service, tcp::endpoint(tcp::v4(), port)),
	mGameSession(0)
{
	start();
}

GameServerInstance::~GameServerInstance(){
}

void GameServerInstance::start(){
	
	mGameSession = new GameSession(mIo_service);
	mAcceptor.async_accept(
		mGameSession->getSocket(),
		boost::bind(
			&GameServerInstance::handleAccept,
			this,
			mGameSession,
			boost::asio::placeholders::error
		)
	);
}

void GameServerInstance::handleAccept(
	GameSession *gameSession,
	const boost::system::error_code& error
){

	if (!error)
		gameSession->start();

	start();

}
