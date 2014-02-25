#include "NetworkIO.hpp"

NetworkIO::NetworkIO(boost::asio::io_service& io_service):
	mSocket(io_service),
	mHeaderBuffer(0),
	mBodyBuffer(0),
	mMessageBuffer(""),
	mNMFactory(new NetworkMessage::NetworkMessageFactory()),
	mMessageList(),
	mWriting(false)
{
	mHeaderBuffer = new char[NetworkMessage::HEADERLENGTH+1];
	mBodyBuffer = new char[NetworkMessage::MAXBODYLENGTH+1];
	
	std::fill_n(mHeaderBuffer, (int)NetworkMessage::HEADERLENGTH+1, 0);
	std::fill_n(mBodyBuffer, (int)NetworkMessage::MAXBODYLENGTH+1, 0);
}

NetworkIO::~NetworkIO(){
}

tcp::socket &NetworkIO::getSocket(){return mSocket;}

void NetworkIO::start(){
	handleReadBody(boost::system::error_code());
}

void NetworkIO::close(){
}

void NetworkIO::sendMessage(NetworkMessage::NetworkMessage *message){

	mMessageList.push_back(*message);

	if(mMessageList.size() < 2)
		handleWrite(boost::system::error_code());

}

void NetworkIO::handleReadHeader(const boost::system::error_code& error){

	std::cout << "#" << mHeaderBuffer << "#" << std::endl;
	mMessageBuffer = mHeaderBuffer;
	std::fill_n(mBodyBuffer, (int)NetworkMessage::MAXBODYLENGTH+1, 0);

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
	else{
		close();
	}

}

void NetworkIO::handleReadBody(const boost::system::error_code& error){

	if(!error){

		if(mMessageBuffer != ""){
			mMessageBuffer += mBodyBuffer;
			handleReceive(mNMFactory->buildMessage(mMessageBuffer));
			mMessageBuffer = "";
			std::fill_n(mHeaderBuffer, (int)NetworkMessage::HEADERLENGTH+1, 0);
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
	else{
		close();
	}

}

void NetworkIO::handleWrite(const boost::system::error_code& error){

	using namespace NetworkMessage;

	if(mMessageList.size() == 0){
		mWriting = false;
		return;
	}

	NetworkMessage::NetworkMessage nm = mMessageList.front();
	mMessageList.pop_front();
	mWriting = true;

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
	else{
		close();
	}
}
