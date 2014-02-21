#include "GameClient.hpp"

namespace GameClient{

	GameClient::GameClient(
		std::string address,
		std::string port
	){
		tcp::resolver resolver(mIo_service);
		tcp::resolver::query query(address, port);
		tcp::resolver::iterator iterator = resolver.resolve(query);
		mListener = new Listener(
			mIo_service,
			iterator,
			boost::bind(&GameClient::handleReceive, this, _1)
		);
		
	}

	GameClient::~GameClient(){
	}

	void GameClient::start(){
		mListener->start();
		mThread = new boost::thread(boost::bind(&boost::asio::io_service::run, &mIo_service));
		//mIo_service.run();
	}

	void GameClient::stop(){
		delete mListener;
		mThread->join();
	}

	void GameClient::sendMessage(NetworkMessage::NetworkMessage *message){
		mListener->sendMessage(message);
	}

	void GameClient::handleReceive(NetworkMessage::NetworkMessage *message){

		using namespace NetworkMessage;

		switch(message->getType()){
			case JOIN:
				onJoin((Join*)message);
				break;
			case LEAVE:
				onLeave((Leave*)message);
				break;
			case JOINACCEPT:
				onJoinAccept((JoinAccept*)message);
				break;
			case JOINREFUSE:
				onJoinRefuse((JoinRefuse*)message);
				break;
			case PLAYERJOINED:
				onPlayerJoined((PlayerJoined*)message);
				break;
			case PLAYERLEFT:
				onPlayerLeft((PlayerLeft*)message);
				break;
			case GAMESTART:
				onGameStart((GameStart*)message);
				break;
			case GAMEEND:
				onGameEnd((GameEnd*)message);
				break;
			case PLAYERINPUT:
				onPlayerInput((PlayerInput*)message);
				break;
			case PLAYERKILLED:
				onPlayerKilled((PlayerKilled*)message);
				break;
			default:
				break;
		}

	}

	void GameClient::onJoin(NetworkMessage::Join *message){

		using namespace NetworkMessage;

		std::cout << "Received JOIN" << std::endl;
		std::cout << message->getMessage() << std::endl;

	}

	void GameClient::onLeave(NetworkMessage::Leave *message){

		using namespace NetworkMessage;

		std::cout << "Received LEAVE" << std::endl;
		std::cout << message->getMessage() << std::endl;

	}

	void GameClient::onJoinAccept(NetworkMessage::JoinAccept *message){

		using namespace NetworkMessage;

		std::cout << "Received JOINACCEPT" << std::endl;
		std::cout << message->getMessage() << std::endl;

	}

	void GameClient::onJoinRefuse(NetworkMessage::JoinRefuse *message){

		using namespace NetworkMessage;

		std::cout << "Received JOINREFUSE" << std::endl;
		std::cout << message->getMessage() << std::endl;

	}

	void GameClient::onPlayerJoined(NetworkMessage::PlayerJoined *message){

		using namespace NetworkMessage;

		std::cout << "Received PLAYERJOINED" << std::endl;
		std::cout << message->getMessage() << std::endl;

	}

	void GameClient::onPlayerLeft(NetworkMessage::PlayerLeft *message){

		using namespace NetworkMessage;

		std::cout << "Received PLAYERLEFT" << std::endl;
		std::cout << message->getMessage() << std::endl;

	}

	void GameClient::onGameStart(NetworkMessage::GameStart *message){

		using namespace NetworkMessage;

		std::cout << "Received GAMESTART" << std::endl;
		std::cout << message->getMessage() << std::endl;

	}

	void GameClient::onGameEnd(NetworkMessage::GameEnd *message){

		using namespace NetworkMessage;

		std::cout << "Received GAMEEND" << std::endl;
		std::cout << message->getMessage() << std::endl;

	}

	void GameClient::onPlayerInput(NetworkMessage::PlayerInput *message){

		using namespace NetworkMessage;

		std::cout << "Received PLAYERINPUT" << std::endl;
		std::cout << message->getMessage() << std::endl;

	}

	void GameClient::onPlayerKilled(NetworkMessage::PlayerKilled *message){

		using namespace NetworkMessage;

		std::cout << "Received PLAYERKILLED" << std::endl;
		std::cout << message->getMessage() << std::endl;

	}

};
