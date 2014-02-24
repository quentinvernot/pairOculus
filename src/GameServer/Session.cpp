#include "Session.hpp"

namespace GameServer{

	Session::Session(
		boost::asio::io_service& io_service,
		boost::function<
			void (
				NetworkMessage::NetworkMessage *message,
				Session *sourceSession
			)
		> receive
	):
		NetworkIO(io_service),
		mReceive(receive),
		mPlayer(0)
	{
	}

	Session::~Session(){
	}

	Player *Session::getPlayer(){return mPlayer;}
	void Session::setPlayer(Player *player){
		mPlayer = player;
	}
	
	void Session::handleReceive(NetworkMessage::NetworkMessage *message){
		mReceive(message, this);
	}

};
