#include "Instance.hpp"

namespace GameServer{

	Instance::Instance(unsigned short port):
		mIo_service(),
		mAcceptor(mIo_service, tcp::endpoint(tcp::v4(), port)),
		mSession(0),
		mSessionList(new SessionList),
		mNMFactory(new NetworkMessage::NetworkMessageFactory()),
		mPlayerList(new PlayerList()),
		mMap(new Map(15, 15)),
		mOpenedSessions(0),
		mGameRunning(false),
		mGameEnded(false)
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
		std::cout << "From : " << sourceSession->getPlayer()->getNickname() << std::endl;
		std::cout << message->getNickname() << std::endl;

		std::string nickname = message->getNickname();

		if(mGameRunning){
			sendJoinRefuse(sourceSession, "A game is already ongoing.");
			mSessionList->removeSession(sourceSession);
		}
		else if(
			mPlayerList->getPlayerByName(nickname) == 0 &&
			sourceSession->getPlayer() == 0
		){

			mPlayerList->addPlayer(nickname);
			Player *np = mPlayerList->getPlayerByName(nickname);
			mMap->setStartingPosition(mPlayerList->getPlayerIndex(nickname), np);
			sourceSession->setPlayer(np);
			sendJoinAccept(sourceSession);
			sendPlayerJoined(np);

		}
		else{
			sendJoinRefuse(sourceSession, "Nickname already in use.");
			mSessionList->removeSession(sourceSession);
		}

	}

	void Instance::onLeave(
		NetworkMessage::Leave *message,
		Session *sourceSession
	){

		std::cout << "Received LEAVE" << std::endl;
		std::cout << "From : " << sourceSession->getPlayer()->getNickname() << std::endl;

		sendPlayerLeft(sourceSession->getPlayer()->getNickname());
		mPlayerList->removePlayer(sourceSession->getPlayer()->getNickname());
		mSessionList->removeSession(sourceSession);

		if(mPlayerList->size() == 0){
			std::cout << "Everyone left, resetting the server for the next game." << std::endl;
			mGameRunning = false;
			mGameEnded = false;
		}

	}

	void Instance::onJoinAccept(
		NetworkMessage::JoinAccept *message,
		Session *sourceSession
	){

		std::cout << "Received JOINACCEPT" << std::endl;
		std::cout << "From : " << sourceSession->getPlayer()->getNickname() << std::endl;

	}

	void Instance::onJoinRefuse(
		NetworkMessage::JoinRefuse *message,
		Session *sourceSession
	){

		std::cout << "Received JOINREFUSE" << std::endl;
		std::cout << "From : " << sourceSession->getPlayer()->getNickname() << std::endl;

	}

	void Instance::onPlayerJoined(
		NetworkMessage::PlayerJoined *message,
		Session *sourceSession
	){
		using namespace NetworkMessage;

		std::cout << "Received PLAYERJOINED" << std::endl;
		std::cout << "From : " << sourceSession->getPlayer()->getNickname() << std::endl;

	}

	void Instance::onPlayerLeft(
		NetworkMessage::PlayerLeft *message,
		Session *sourceSession
	){
		using namespace NetworkMessage;

		std::cout << "Received PLAYERLEFT" << std::endl;
		std::cout << "From : " << sourceSession->getPlayer()->getNickname() << std::endl;

	}

	void Instance::onGameStart(
		NetworkMessage::GameStart *message,
		Session *sourceSession
	){

		std::cout << "Received GAMESTART" << std::endl;
		std::cout << "From : " << sourceSession->getPlayer()->getNickname() << std::endl;

		sourceSession->setIsReady(true);

		unsigned int readyCount = 0;
		for(unsigned int i = 0; i < mSessionList->size(); i++)
			if((*mSessionList)[i]->getIsReady())
				readyCount++;

		if(readyCount == mPlayerList->size()){
			std::cout << "Everyone is ready to start" << std::endl;
			mGameRunning = true;
			sendGameStart();
		}

	}

	void Instance::onGameEnd(
		NetworkMessage::GameEnd *message,
		Session *sourceSession
	){

		std::cout << "Received GAMEEND" << std::endl;
		std::cout << "From : " << sourceSession->getPlayer()->getNickname() << std::endl;

	}

	void Instance::onPlayerInput(
		NetworkMessage::PlayerInput *message,
		Session *sourceSession
	){

		std::cout << "Received PLAYERINPUT" << std::endl;
		std::cout << "From : " << sourceSession->getPlayer()->getNickname() << std::endl;
		std::cout << message->getNickname() << std::endl;

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
		std::cout << "From : " << sourceSession->getPlayer()->getNickname() << std::endl;
		std::cout << message->getNickname() << std::endl;

		if(mGameRunning && !mGameEnded && sourceSession->getPlayer() != 0){
			std::string nickname = sourceSession->getPlayer()->getNickname();
			mPlayerList->getPlayerByName(nickname)->die();
			sendPlayerKilled(nickname, message);
			
			unsigned int deadCount = 0;
			for(unsigned int i = 0; i < mPlayerList->size(); i++)
				if((*mPlayerList)[i]->isDead())
					deadCount ++;

			if(deadCount == mPlayerList->size() - 1){
				std::cout << "Only one player is alive" << std::endl;
				sendGameEnd();
				mGameEnded = true;
			}

		}
		else
			std::cout << "Game is not started" << std::endl;

	}

	void Instance::sendJoinAccept(Session *sourceSession){

		using namespace NetworkMessage;
		std::cout << "Sending JOINACCEPT to source" << std::endl;
		std::cout << (*mPlayerList)[0]->getNickname() << std::endl;
		sourceSession->sendMessage(
			mNMFactory->buildMessage(
				JOINACCEPT,
				mPlayerList,
				mMap->getHeight(),
				mMap->getWidth(),
				mMap->getSeed()
			)
		);

	}

	void Instance::sendJoinRefuse(
		Session *sourceSession,
		std::string reason
	){

		using namespace NetworkMessage;
		std::cout << "Sending JOINREFUSE to source" << std::endl;
		std::cout << reason << std::endl;
		sourceSession->sendMessage(
			mNMFactory->buildMessage(JOINREFUSE, reason)
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
	
	void Instance::sendPlayerKilled(
		std::string nickname,
		NetworkMessage::PlayerKilled *message
	){

		using namespace NetworkMessage;
		std::cout << "Sending PLAYERKILLED to everyone else" << std::endl;
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
