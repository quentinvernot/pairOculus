#include "Listener.hpp"

namespace GameClient{

	Listener::Listener(
		std::string address,
		std::string port
	):
		mConnector(0),
		mThread(0),
		mCallbackJoin(0),
		mCallbackLeave(0),
		mCallbackJoinAccept(0),
		mCallbackJoinRefuse(0),
		mCallbackPlayerJoined(0),
		mCallbackPlayerLeft(0),
		mCallbackGameStart(0),
		mCallbackGameEnd(0),
		mCallbackPlayerInput(0),
		mCallbackPlayerKilled(0)
	{
		tcp::resolver resolver(mIo_service);
		tcp::resolver::query query(address, port);
		tcp::resolver::iterator iterator = resolver.resolve(query);
		mConnector = new Connector(
			mIo_service,
			iterator,
			boost::bind(&Listener::handleReceive, this, _1)
		);
		
	}

	Listener::~Listener(){
	}

	void Listener::start(){
		mConnector->start();
		mThread = new boost::thread(boost::bind(&boost::asio::io_service::run, &mIo_service));
	}

	void Listener::stop(){
		delete mConnector;
		mThread->join();
	}

	void Listener::sendMessage(NetworkMessage::NetworkMessage *message){
		mConnector->sendMessage(message);
	}

	void Listener::handleReceive(NetworkMessage::NetworkMessage *message){

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

	void Listener::setCallbackJoin(
		boost::function<
			void (NetworkMessage::NetworkMessage *message)
		> callbackJoin
	){
		mCallbackJoin = callbackJoin;
	}

	void Listener::setCallbackLeave(
		boost::function<
			void (NetworkMessage::NetworkMessage *message)
		> callbackLeave
	){
		mCallbackLeave = callbackLeave;
	}

	void Listener::setCallbackJoinAccept(
		boost::function<
			void (NetworkMessage::NetworkMessage *message)
		> callbackJoinAccept
	){
		mCallbackJoinAccept = callbackJoinAccept;
	}

	void Listener::setCallbackJoinRefuse(
		boost::function<
			void (NetworkMessage::NetworkMessage *message)
		> callbackJoinRefuse
	){
		mCallbackJoinRefuse = callbackJoinRefuse;
	}

	void Listener::setCallbackPlayerJoined(
		boost::function<
			void (NetworkMessage::NetworkMessage *message)
		> callbackPlayerJoined
	){
		mCallbackPlayerJoined = callbackPlayerJoined;
	}

	void Listener::setCallbackPlayerLeft(
		boost::function<
			void (NetworkMessage::NetworkMessage *message)
		> callbackPlayerLeft
	){
		mCallbackPlayerLeft = callbackPlayerLeft;
	}

	void Listener::setCallbackGameStart(
		boost::function<
			void (NetworkMessage::NetworkMessage *message)
		> callbackGameStart
	){
		mCallbackGameStart = callbackGameStart;
	}

	void Listener::setCallbackGameEnd(
		boost::function<
			void (NetworkMessage::NetworkMessage *message)
		> callbackGameEnd
	){
		mCallbackGameEnd = callbackGameEnd;
	}

	void Listener::setCallbackPlayerInput(
		boost::function<
			void (NetworkMessage::NetworkMessage *message)
		> callbackPlayerInput
	){
		mCallbackPlayerInput = callbackPlayerInput;
	}

	void Listener::setCallbackPlayerKilled(
		boost::function<
			void (NetworkMessage::NetworkMessage *message)
		> callbackPlayerKilled
	){
		mCallbackPlayerKilled = callbackPlayerKilled;
	}

	void Listener::onJoin(NetworkMessage::Join *message){

		using namespace NetworkMessage;

		std::cout << "Received JOIN" << std::endl;
		std::cout << message->getMessage() << std::endl;

		if(mCallbackJoin != 0)
			mCallbackJoin(message);

	}

	void Listener::onLeave(NetworkMessage::Leave *message){

		using namespace NetworkMessage;

		std::cout << "Received LEAVE" << std::endl;
		std::cout << message->getMessage() << std::endl;

		if(mCallbackLeave != 0)
			mCallbackLeave(message);

	}

	void Listener::onJoinAccept(NetworkMessage::JoinAccept *message){

		using namespace NetworkMessage;

		std::cout << "Received JOINACCEPT" << std::endl;
		std::cout << message->getMessage() << std::endl;

		if(mCallbackJoinAccept != 0)
			mCallbackJoinAccept(message);

	}

	void Listener::onJoinRefuse(NetworkMessage::JoinRefuse *message){

		using namespace NetworkMessage;

		std::cout << "Received JOINREFUSE" << std::endl;
		std::cout << message->getMessage() << std::endl;

		if(mCallbackJoinRefuse != 0)
			mCallbackJoinRefuse(message);

	}

	void Listener::onPlayerJoined(NetworkMessage::PlayerJoined *message){

		using namespace NetworkMessage;

		std::cout << "Received PLAYERJOINED" << std::endl;
		std::cout << message->getMessage() << std::endl;

		if(mCallbackPlayerJoined != 0)
			mCallbackPlayerJoined(message);

	}

	void Listener::onPlayerLeft(NetworkMessage::PlayerLeft *message){

		using namespace NetworkMessage;

		std::cout << "Received PLAYERLEFT" << std::endl;
		std::cout << message->getMessage() << std::endl;

		if(mCallbackPlayerLeft != 0)
			mCallbackPlayerLeft(message);

	}

	void Listener::onGameStart(NetworkMessage::GameStart *message){

		using namespace NetworkMessage;

		std::cout << "Received GAMESTART" << std::endl;
		std::cout << message->getMessage() << std::endl;

		if(mCallbackGameStart != 0)
			mCallbackGameStart(message);

	}

	void Listener::onGameEnd(NetworkMessage::GameEnd *message){

		using namespace NetworkMessage;

		std::cout << "Received GAMEEND" << std::endl;
		std::cout << message->getMessage() << std::endl;

		if(mCallbackGameEnd != 0)
			mCallbackGameEnd(message);

	}

	void Listener::onPlayerInput(NetworkMessage::PlayerInput *message){

		using namespace NetworkMessage;

		std::cout << "Received PLAYERINPUT" << std::endl;
		std::cout << message->getMessage() << std::endl;

		if(mCallbackPlayerInput != 0)
			mCallbackPlayerInput(message);

	}

	void Listener::onPlayerKilled(NetworkMessage::PlayerKilled *message){

		using namespace NetworkMessage;

		std::cout << "Received PLAYERKILLED" << std::endl;
		std::cout << message->getMessage() << std::endl;

		if(mCallbackPlayerKilled != 0)
			mCallbackPlayerKilled(message);

	}

};
