#include "Listener.hpp"

namespace GameClient{

	Listener::Listener(
		boost::asio::io_service &io_service,
		tcp::resolver::iterator iterator,
		boost::function<
			void (NetworkMessage::NetworkMessage *message)
		> receive
	):
		NetworkIO(io_service),
		mIterator(iterator),
		mReceive(receive)
	{
	}

	Listener::~Listener(){
		mSocket.close();
	}

	void Listener::start(){
		boost::asio::async_connect(
			mSocket,
			mIterator,
			boost::bind(
				&Listener::handleReadBody,
				this,
				boost::asio::placeholders::error
			)
		);
	}

	void Listener::handleReceive(NetworkMessage::NetworkMessage *message){
		mReceive(message);
	}

};
