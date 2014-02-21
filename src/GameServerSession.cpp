#include "GameServerSession.hpp"

GameServerSession::GameServerSession(
	boost::asio::io_service& io_service,
	boost::function<
		void (
			NetworkMessage::NetworkMessage *message,
			GameServerSession *sourceSession
		)
	> handleReceive
):
	mSocket(io_service),
	mHeaderBuffer(0),
	mBodyBuffer(0),
	mMessageBuffer(""),
	mNMFactory(new NetworkMessage::NetworkMessageFactory()),
	mMessageList(),
	mHandleReceive(handleReceive),
	mPlayer(0)
{
	mHeaderBuffer = new char[NetworkMessage::HEADERLENGTH+1];
	mBodyBuffer = new char[NetworkMessage::MAXBODYLENGTH+1];
}

GameServerSession::~GameServerSession(){
}

tcp::socket &GameServerSession::getSocket(){return mSocket;}

void GameServerSession::start(){
	handleReadBody(boost::system::error_code());
}

void GameServerSession::sendMessage(NetworkMessage::NetworkMessage *message){
	mMessageList.push_back(*message);
	handleWrite(boost::system::error_code());
}

Player *GameServerSession::getPlayer(){return mPlayer;}
void GameServerSession::setPlayer(Player *player){
	mPlayer = player;
}

void GameServerSession::handleReadHeader(const boost::system::error_code& error){

	mMessageBuffer = mHeaderBuffer;

	if(!error){
		boost::asio::async_read(
			mSocket,
			boost::asio::buffer(
				mBodyBuffer,
				mNMFactory->getLengthFromHeader(mHeaderBuffer)
			),
			boost::bind(
				&GameServerSession::handleReadBody,
				this,
				boost::asio::placeholders::error
			)
		);
	}

}

void GameServerSession::handleReadBody(const boost::system::error_code& error){

	if(!error){
		
		if(mMessageBuffer != ""){

			mMessageBuffer += mBodyBuffer;
			mHandleReceive(mNMFactory->buildMessage(mMessageBuffer), this);
			mMessageBuffer = "";

		}

		boost::asio::async_read(
			mSocket,
			boost::asio::buffer(
				mHeaderBuffer,
				NetworkMessage::HEADERLENGTH
			),
			boost::bind(
				&GameServerSession::handleReadHeader,
				this,
				boost::asio::placeholders::error
			)
		);
	}

}

void GameServerSession::handleWrite(const boost::system::error_code& error){

	if(mMessageList.size() == 0)
		return;

	NetworkMessage::NetworkMessage nm = mMessageList.front();
	mMessageList.pop_front();

	if(!error && mMessageList.empty()){
		boost::asio::async_write(
			mSocket,
			boost::asio::buffer(
				nm.getMessage().c_str(),
				nm.getMessage().length()
			),
			boost::bind(
				&GameServerSession::handleWrite,
				this,
				boost::asio::placeholders::error
			)
		);
	}
}
