#include "Connector.hpp"

namespace GameClient{

	Connector::Connector(
		boost::asio::io_service &io_service,
		tcp::resolver::iterator iterator,
		boost::function<void ()> close,
		boost::function<
			void (NetworkMessage::NetworkMessage *message)
		> receive
	):
		NetworkIO(io_service),
		mIterator(iterator),
		mClose(close),
		mReceive(receive)
	{
	}

	Connector::~Connector(){
	}

	void Connector::start(){
		boost::asio::async_connect(
			mSocket,
			mIterator,
			boost::bind(
				&Connector::handleReadBody,
				this,
				boost::asio::placeholders::error
			)
		);
	}

	void Connector::close(){
		mClose();
	}

	void Connector::handleReceive(NetworkMessage::NetworkMessage *message){
		mReceive(message);
	}

};
