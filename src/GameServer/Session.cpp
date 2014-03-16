#include "Session.hpp"

namespace GameServer{

	Session::Session(
		int id,
		boost::asio::io_service& io_service,
		boost::function<
			void (
				NetworkMessage::NetworkMessage *message,
				Session *sourceSession
			)
		> receive,
		boost::function<void (Session *sourceSession)> close
	):
		NetworkIO(io_service),
		mId(id),
		mReceive(receive),
		mClose(close),
		mPlayer(0),
		mIsReady(false)
	{
	}

	Session::~Session(){
	}

	void Session::close(){
		mSocket.close();
		mClose(this);
	}

	int Session::getId(){return mId;}

	Player *Session::getPlayer(){return mPlayer;}
	void Session::setPlayer(Player *player){
		mPlayer = player;
	}

	bool Session::getIsReady(){return mIsReady;}
	void Session::setIsReady(bool isReady){mIsReady = isReady;}
	
	void Session::handleReceive(NetworkMessage::NetworkMessage *message){
		mReceive(message, this);
	}

};
