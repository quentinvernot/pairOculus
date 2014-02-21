#include "Listener.hpp"

namespace GameClient{

	Listener::Listener(
		boost::asio::io_service &io_service,
		tcp::resolver::iterator iterator,
		boost::function<
			void (NetworkMessage::NetworkMessage *message)
		> handleReceive
	):
		mIterator(iterator),
		mSocket(io_service),
		mHeaderBuffer(0),
		mBodyBuffer(0),
		mMessageBuffer(""),
		mNMFactory(new NetworkMessage::NetworkMessageFactory()),
		mMessageList(),
		mHandleReceive(handleReceive)
	{
		mHeaderBuffer = new char[NetworkMessage::HEADERLENGTH+1];
		mBodyBuffer = new char[NetworkMessage::MAXBODYLENGTH+1];
	}

	Listener::~Listener(){
		mSocket.close();
	}

	void Listener::start(){
		boost::asio::async_connect(
			mSocket,
			mIterator,
			boost::bind(
				&Listener::handleConnect,
				this,
				boost::asio::placeholders::error
			)
		);

	}

	void Listener::sendMessage(NetworkMessage::NetworkMessage *message){
		mMessageList.push_back(*message);
		handleWrite(boost::system::error_code());
	}

	void Listener::handleConnect(const boost::system::error_code& error){

		if(!error){
			boost::asio::async_read(
				mSocket,
				boost::asio::buffer(
					mHeaderBuffer,
					NetworkMessage::HEADERLENGTH
				),
				boost::bind(
					&Listener::handleReadHeader,
					this,
					boost::asio::placeholders::error
				)
			);
		}

	}
	
	void Listener::handleReadHeader(const boost::system::error_code& error){

		mMessageBuffer = mHeaderBuffer;

		if(!error){
			boost::asio::async_read(
				mSocket,
				boost::asio::buffer(
					mBodyBuffer,
					mNMFactory->getLengthFromHeader(mHeaderBuffer)
				),
				boost::bind(
					&Listener::handleReadBody,
					this,
					boost::asio::placeholders::error
				)
			);
		}

	}

	void Listener::handleReadBody(const boost::system::error_code& error){

		if(!error){
			
			if(mMessageBuffer != ""){

				mMessageBuffer += mBodyBuffer;
				mHandleReceive(mNMFactory->buildMessage(mMessageBuffer));
				mMessageBuffer = "";

			}

			boost::asio::async_read(
				mSocket,
				boost::asio::buffer(
					mHeaderBuffer,
					NetworkMessage::HEADERLENGTH
				),
				boost::bind(
					&Listener::handleReadHeader,
					this,
					boost::asio::placeholders::error
				)
			);
		}

	}

	void Listener::handleWrite(const boost::system::error_code& error){

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
					&Listener::handleWrite,
					this,
					boost::asio::placeholders::error
				)
			);
		}
	}

};
