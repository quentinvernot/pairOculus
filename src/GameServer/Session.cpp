#include "Session.hpp"

namespace GameServer{

	Session::Session(
		boost::asio::io_service& io_service,
		boost::function<
			void (
				NetworkMessage::NetworkMessage *message,
				Session *sourceSession
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

	Session::~Session(){
	}

	tcp::socket &Session::getSocket(){return mSocket;}

	void Session::start(){
		handleReadBody(boost::system::error_code());
	}

	void Session::sendMessage(NetworkMessage::NetworkMessage *message){
		mMessageList.push_back(*message);
		handleWrite(boost::system::error_code());
	}

	Player *Session::getPlayer(){return mPlayer;}
	void Session::setPlayer(Player *player){
		mPlayer = player;
	}

	void Session::handleReadHeader(const boost::system::error_code& error){

		mMessageBuffer = mHeaderBuffer;

		if(!error){
			boost::asio::async_read(
				mSocket,
				boost::asio::buffer(
					mBodyBuffer,
					mNMFactory->getLengthFromHeader(mHeaderBuffer)
				),
				boost::bind(
					&Session::handleReadBody,
					this,
					boost::asio::placeholders::error
				)
			);
		}

	}

	void Session::handleReadBody(const boost::system::error_code& error){

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
					&Session::handleReadHeader,
					this,
					boost::asio::placeholders::error
				)
			);
		}

	}

	void Session::handleWrite(const boost::system::error_code& error){

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
					&Session::handleWrite,
					this,
					boost::asio::placeholders::error
				)
			);
		}
	}

};
