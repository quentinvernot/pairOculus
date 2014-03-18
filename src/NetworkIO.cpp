#include "NetworkIO.hpp"

NetworkIO::NetworkIO(boost::asio::io_service& io_service):
	mSocket(io_service),
	mHeaderBuffer(0),
	mBodyBuffer(0),
	mMessageBuffer(""),
	mNMFactory(new NetworkMessage::NetworkMessageFactory()),
	mMessageList(),
	mIsClosed(false)
{
	mHeaderBuffer = new char[NetworkMessage::HEADERLENGTH+1];
	mBodyBuffer = new char[NetworkMessage::MAXBODYLENGTH+1];
	
	std::fill_n(mHeaderBuffer, (int)NetworkMessage::HEADERLENGTH+1, 0);
	std::fill_n(mBodyBuffer, (int)NetworkMessage::MAXBODYLENGTH+1, 0);
}

NetworkIO::~NetworkIO(){
}

tcp::socket &NetworkIO::getSocket(){return mSocket;}
bool NetworkIO::isClosed(){return mIsClosed;}

void NetworkIO::start(){
	handleReadBody(boost::system::error_code());
}

void NetworkIO::close(){

	try{
		mSocket.shutdown(mSocket.shutdown_both);
		mSocket.close();
	}
	catch(std::exception& e){
		std::cout << e.what() << std::endl;
	}

	mIsClosed = true;

}

void NetworkIO::sendMessage(NetworkMessage::NetworkMessage *message){

	if(mIsClosed)
		return;
	
	mMessageList.push_back(message);

	if(mMessageList.size() == 1)
		handleWrite(boost::system::error_code());

}

void NetworkIO::handleReadHeader(const boost::system::error_code& error){

	if(!mIsClosed && !error){
		
		mMessageBuffer = mHeaderBuffer;
		std::fill_n(mBodyBuffer, (int)NetworkMessage::MAXBODYLENGTH+1, 0);

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

	if(!mIsClosed && !error){

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

	if(!mIsClosed && !error){

		if(mMessageList.size() == 0)
			return;

		char *str = new char[NetworkMessage::HEADERLENGTH + NetworkMessage::MAXBODYLENGTH + 1];
		strcpy(str, mMessageList.front()->getMessage().c_str());
		int length = mMessageList.front()->getMessage().length();
		//delete mMessageList.front();
		mMessageList.pop_front();

		boost::asio::async_write(
			mSocket,
			boost::asio::buffer(str, length),
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
