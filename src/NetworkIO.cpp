#include "NetworkIO.hpp"

NetworkIO::NetworkIO(boost::asio::io_service& io_service):
	mSocket(io_service),
	mHeaderBuffer(0),
	mBodyBuffer(0),
	mMessageBuffer(""),
	mNMFactory(new NetworkMessage::NetworkMessageFactory()),
	mMessageList()
{
	mHeaderBuffer = new char[NetworkMessage::HEADERLENGTH+1];
	mBodyBuffer = new char[NetworkMessage::MAXBODYLENGTH+1];
}

NetworkIO::~NetworkIO(){
}

tcp::socket &NetworkIO::getSocket(){return mSocket;}

void NetworkIO::start(){
	handleReadBody(boost::system::error_code());
}

void NetworkIO::sendMessage(NetworkMessage::NetworkMessage *message){

	mMessageList.push_back(*message);

	if(mMessageList.size() < 2)
		handleWrite(boost::system::error_code());

}

void NetworkIO::handleReadHeader(const boost::system::error_code& error){

	mMessageBuffer = mHeaderBuffer;

	if(!error){
		boost::asio::async_read(
			mSocket,
			boost::asio::buffer(
				mBodyBuffer,
				mNMFactory->getLengthFromHeader(mHeaderBuffer)
			),
			boost::bind(
				&NetworkIO::handleReadBody,
				this,
				boost::asio::placeholders::error
			)
		);
	}

}

void NetworkIO::handleReadBody(const boost::system::error_code& error){

	if(!error){
		
		if(mMessageBuffer != ""){

			mMessageBuffer += mBodyBuffer;
			handleReceive(mNMFactory->buildMessage(mMessageBuffer));
			mMessageBuffer = "";

		}

		boost::asio::async_read(
			mSocket,
			boost::asio::buffer(
				mHeaderBuffer,
				NetworkMessage::HEADERLENGTH
			),
			boost::bind(
				&NetworkIO::handleReadHeader,
				this,
				boost::asio::placeholders::error
			)
		);
	}

}

void NetworkIO::handleWrite(const boost::system::error_code& error){

	if(mMessageList.size() == 0)
		return;

	NetworkMessage::NetworkMessage nm = mMessageList.front();
	mMessageList.pop_front();

	if(!error){
		boost::asio::async_write(
			mSocket,
			boost::asio::buffer(
				nm.getMessage().c_str(),
				nm.getMessage().length()
			),
			boost::bind(
				&NetworkIO::handleWrite,
				this,
				boost::asio::placeholders::error
			)
		);
	}
}
