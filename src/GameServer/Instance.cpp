#include "Instance.hpp"

namespace GameServer{

	Instance::Instance(unsigned short port):
		mIo_service(),
		mAcceptor(mIo_service, tcp::endpoint(tcp::v4(), port)),
		mSession(0),
		mSessionList(new SessionList),
		mPlayerList(new PlayerList()),
		mNMFactory(new NetworkMessage::NetworkMessageFactory()),
		mOpenedSessions(0),
		mGameStarted(false)
	{
	}

	Instance::~Instance(){
	}

	void Instance::start(){

		mSession = new Session(
			mOpenedSessions,
			mIo_service,
			boost::bind(
				&Instance::onReceive,
				this,
				_1,
				_2
			),
			boost::bind(
				&Instance::onClose,
				this,
				_1
			)
		);

		mAcceptor.async_accept(
			mSession->getSocket(),
			boost::bind(
				&Instance::handleAccept,
				this,
				mSession,
				boost::asio::placeholders::error
			)
		);
		
		mIo_service.run();

	}

	void Instance::stop(){
		mSessionList->clear();
	}

	void Instance::handleAccept(
		Session *session,
		const boost::system::error_code& error
	){

		if (!error){
			std::cout << "Adding session " << mOpenedSessions << std::endl;
			mOpenedSessions++;
			mSessionList->addSession(session);
			session->start();
		}

		start();

	}

	void Instance::onReceive(
		NetworkMessage::NetworkMessage *message,
		Session *sourceSession
	){

		std::cout << "In session " << sourceSession->getId() << std::endl;

		using namespace NetworkMessage;

		switch(message->getType()){
			case JOIN:
				onJoin((Join*)message, sourceSession);
				break;
			case LEAVE:
				onLeave((Leave*)message, sourceSession);
				break;
			case JOINACCEPT:
				onJoinAccept((JoinAccept*)message, sourceSession);
				break;
			case JOINREFUSE:
				onJoinRefuse((JoinRefuse*)message, sourceSession);
				break;
			case PLAYERJOINED:
				onPlayerJoined((PlayerJoined*)message, sourceSession);
				break;
			case PLAYERLEFT:
				onPlayerLeft((PlayerLeft*)message, sourceSession);
				break;
			case GAMESTART:
				onGameStart((GameStart*)message, sourceSession);
				break;
			case GAMEEND:
				onGameEnd((GameEnd*)message, sourceSession);
				break;
			case PLAYERINPUT:
				onPlayerInput((PlayerInput*)message, sourceSession);
				break;
			case PLAYERKILLED:
				onPlayerKilled((PlayerKilled*)message, sourceSession);
				break;
			default:
				break;
		}

	}

	void Instance::onClose(Session *sourceSession){

		int id = sourceSession->getId();
		std::cout << "Deleting session " << id << std::endl;

		if(sourceSession->getPlayer() != 0)
			sendPlayerLeft(sourceSession->getPlayer()->getNickname());
		
		mSessionList->removeSession(sourceSession);

	}

	void Instance::onJoin(
		NetworkMessage::Join *message,
		Session *sourceSession
	){

		using namespace NetworkMessage;

		std::cout << "Received JOIN" << std::endl;
		std::cout << message->getMessage() << std::endl;

		std::string nickname = message->getNickname();
		if(
			mPlayerList->getPlayerByName(nickname) == 0 &&
			sourceSession->getPlayer() == 0
		){
			mPlayerList->addPlayer(nickname);
			Player *np = mPlayerList->getPlayerByName(nickname);
			sourceSession->setPlayer(np);
			sendJoinAccept(sourceSession);
			sendPlayerJoined(np);

		}
		else{
			sendJoinRefuse(sourceSession);
			mSessionList->removeSession(sourceSession);
		}

	}

	void Instance::onLeave(
		NetworkMessage::Leave *message,
		Session *sourceSession
	){

		std::cout << "Received LEAVE" << std::endl;
		std::cout << message->getMessage() << std::endl;

		sendPlayerLeft(sourceSession->getPlayer()->getNickname());

	}

	void Instance::onJoinAccept(
		NetworkMessage::JoinAccept *message,
		Session *sourceSession
	){

		std::cout << "Received JOINACCEPT" << std::endl;
		std::cout << message->getMessage() << std::endl;

	}

	void Instance::onJoinRefuse(
		NetworkMessage::JoinRefuse *message,
		Session *sourceSession
	){

		std::cout << "Received JOINREFUSE" << std::endl;
		std::cout << message->getMessage() << std::endl;

	}

	void Instance::onPlayerJoined(
		NetworkMessage::PlayerJoined *message,
		Session *sourceSession
	){
		using namespace NetworkMessage;

		std::cout << "Received PLAYERJOINED" << std::endl;
		std::cout << message->getMessage() << std::endl;

	}

	void Instance::onPlayerLeft(
		NetworkMessage::PlayerLeft *message,
		Session *sourceSession
	){
		using namespace NetworkMessage;

		std::cout << "Received PLAYERLEFT" << std::endl;
		std::cout << message->getMessage() << std::endl;

	}

	void Instance::onGameStart(
		NetworkMessage::GameStart *message,
		Session *sourceSession
	){

		std::cout << "Received GAMESTART" << std::endl;
		std::cout << message->getMessage() << std::endl;

		sourceSession->setIsReady(true);
		
		unsigned int readyCount = 0;
		for(unsigned int i = 0; i < mSessionList->size(); i++)
			if((*mSessionList)[i]->getIsReady())
				readyCount++;
		
		if(readyCount == mPlayerList->size()){
			std::cout << "Everyone is ready to start" << std::endl;
			sendGameStart();
		}

	}

	void Instance::onGameEnd(
		NetworkMessage::GameEnd *message,
		Session *sourceSession
	){

		std::cout << "Received GAMEEND" << std::endl;
		std::cout << message->getMessage() << std::endl;

		sendGameEnd();

	}

	void Instance::onPlayerInput(
		NetworkMessage::PlayerInput *message,
		Session *sourceSession
	){

		std::cout << "Received PLAYERINPUT" << std::endl;
		std::cout << message->getMessage() << std::endl;

		if(sourceSession->getPlayer() != 0){
			std::string nickname = sourceSession->getPlayer()->getNickname();
			sendPlayerInput(nickname, message);
		}

	}

	void Instance::onPlayerKilled(
		NetworkMessage::PlayerKilled *message,
		Session *sourceSession
	){
		using namespace NetworkMessage;

		std::cout << "Received PLAYERKILLED" << std::endl;
		std::cout << message->getMessage() << std::endl;

	}

	void Instance::sendJoinAccept(Session *sourceSession){

		using namespace NetworkMessage;
		std::cout << "Sending JOINACCEPT to source" << std::endl;
		sourceSession->sendMessage(
			mNMFactory->buildMessage(JOINACCEPT, mPlayerList)
		);

	}

	void Instance::sendJoinRefuse(Session *sourceSession){

		using namespace NetworkMessage;
		std::cout << "Sending JOINREFUSE to source" << std::endl;
		sourceSession->sendMessage(
			mNMFactory->buildMessage(JOINREFUSE, "Nickname already in use.")
		);

	}

	void Instance::sendPlayerJoined(Player *player){

		using namespace NetworkMessage;
		std::cout << "Sending PLAYERJOINED to everyone else" << std::endl;
		std::string nickname = player->getNickname();
		
		for(unsigned int i = 0; i < mSessionList->size(); i++){

			if(
				(*mSessionList)[i]->getPlayer() != 0 &&
				(*mSessionList)[i]->getPlayer()->getNickname() != nickname
			){
				(*mSessionList)[i]->sendMessage(
					mNMFactory->buildMessage(PLAYERJOINED, player)
				);
			}

		}

	}

	void Instance::sendPlayerLeft(std::string nickname){

		using namespace NetworkMessage;

		if(mPlayerList->getPlayerByName(nickname) != 0){

			std::cout << "Sending PLAYERLEFT to everyone else" << std::endl;
			for(unsigned int i = 0; i < mSessionList->size(); i++){

				if(
					(*mSessionList)[i]->getPlayer() != 0 &&
					(*mSessionList)[i]->getPlayer()->getNickname() != nickname
				){
					(*mSessionList)[i]->sendMessage(
						mNMFactory->buildMessage(PLAYERLEFT, nickname)
					);
				}

			}

			mPlayerList->removePlayer(nickname);

		}

	}

	void Instance::sendGameStart(){

		using namespace NetworkMessage;
		std::cout << "Sending GAMESTART to everyone" << std::endl;

		for(unsigned int i = 0; i < mSessionList->size(); i++){

			if((*mSessionList)[i]->getPlayer() != 0){
				(*mSessionList)[i]->sendMessage(
					mNMFactory->buildMessage(GAMESTART)
				);
			}

		}

	}

	void Instance::sendGameEnd(){

		using namespace NetworkMessage;
		std::cout << "Sending GAMEEND to everyone" << std::endl;
		
		for(unsigned int i = 0; i < mSessionList->size(); i++){

			if((*mSessionList)[i]->getPlayer() != 0){
				(*mSessionList)[i]->sendMessage(
					mNMFactory->buildMessage(GAMEEND)
				);
			}

		}

	}

	void Instance::sendPlayerInput(
		std::string nickname,
		NetworkMessage::PlayerInput *message
	){

		using namespace NetworkMessage;
		std::cout << "Sending PLAYERINPUT to everyone else" << std::endl;
		for(unsigned int i = 0; i < mSessionList->size(); i++){

			if(
				(*mSessionList)[i]->getPlayer() != 0 &&
				(*mSessionList)[i]->getPlayer()->getNickname() != nickname
			){
				(*mSessionList)[i]->sendMessage(message);
			}

		}

	}
	
};
