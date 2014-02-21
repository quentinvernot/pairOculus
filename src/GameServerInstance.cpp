#include "GameServerInstance.hpp"

GameServerInstance::GameServerInstance(
	unsigned short port,
	boost::asio::io_service& io_service
) :
	mIo_service(io_service),
	mAcceptor(mIo_service, tcp::endpoint(tcp::v4(), port)),
	mGameServerSession(0),
	mSessionList(new GameServerSessionList),
	mPlayerList(new PlayerList()),
	mNMFactory(new NetworkMessage::NetworkMessageFactory())
{
	start();
}

GameServerInstance::~GameServerInstance(){
}

void GameServerInstance::start(){

	mGameServerSession = new GameServerSession(
		mIo_service,
		boost::bind(
			&GameServerInstance::handleReceive,
			this,
			_1,
			_2
		)
	);

	mAcceptor.async_accept(
		mGameServerSession->getSocket(),
		boost::bind(
			&GameServerInstance::handleAccept,
			this,
			mGameServerSession,
			boost::asio::placeholders::error
		)
	);

}

void GameServerInstance::handleAccept(
	GameServerSession *gameServerSession,
	const boost::system::error_code& error
){

	if (!error){
		mSessionList->addSession(gameServerSession);
		gameServerSession->start();
	}

	start();

}

void GameServerInstance::handleReceive(
	NetworkMessage::NetworkMessage *message,
	GameServerSession *sourceSession
){

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

void GameServerInstance::onJoin(
	NetworkMessage::Join *message,
	GameServerSession *sourceSession
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
		std::cout << "Sending JOINACCEPT to source" << std::endl;
		sourceSession->sendMessage(
			mNMFactory->buildMessage(JOINACCEPT, mPlayerList)
		);
		std::cout << "Sending PLAYERJOINED to everyone else" << std::endl;
		for(unsigned int i = 0; i < mSessionList->size(); i++){
			
			if(
				(*mSessionList)[i]->getPlayer() != 0 &&
				(*mSessionList)[i]->getPlayer()->getNickname() != nickname
			){
				(*mSessionList)[i]->sendMessage(
					mNMFactory->buildMessage(PLAYERJOINED, np)
				);
			}
			
		}

	}
	else{
		std::cout << "Sending JOINREFUSE to source" << std::endl;
		sourceSession->sendMessage(
			mNMFactory->buildMessage(JOINREFUSE, "Nickname already in use.")
		);
		mSessionList->removeSession(sourceSession);
	}

}

void GameServerInstance::onLeave(
	NetworkMessage::Leave *message,
	GameServerSession *sourceSession
){
	using namespace NetworkMessage;

	std::cout << "Received LEAVE" << std::endl;
	std::cout << message->getMessage() << std::endl;

	std::string nickname = sourceSession->getPlayer()->getNickname();
	std::cout << "a" << std::endl;
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

void GameServerInstance::onJoinAccept(
	NetworkMessage::JoinAccept *message,
	GameServerSession *sourceSession
){
	using namespace NetworkMessage;

	std::cout << "Received JOINACCEPT" << std::endl;
	std::cout << message->getMessage() << std::endl;

}

void GameServerInstance::onJoinRefuse(
	NetworkMessage::JoinRefuse *message,
	GameServerSession *sourceSession
){
	using namespace NetworkMessage;

	std::cout << "Received JOINREFUSE" << std::endl;
	std::cout << message->getMessage() << std::endl;

}

void GameServerInstance::onPlayerJoined(
	NetworkMessage::PlayerJoined *message,
	GameServerSession *sourceSession
){
	using namespace NetworkMessage;

	std::cout << "Received PLAYERJOINED" << std::endl;
	std::cout << message->getMessage() << std::endl;

}

void GameServerInstance::onPlayerLeft(
	NetworkMessage::PlayerLeft *message,
	GameServerSession *sourceSession
){
	using namespace NetworkMessage;

	std::cout << "Received PLAYERLEFT" << std::endl;
	std::cout << message->getMessage() << std::endl;

}

void GameServerInstance::onGameStart(
	NetworkMessage::GameStart *message,
	GameServerSession *sourceSession
){
	using namespace NetworkMessage;

	std::cout << "Received GAMESTART" << std::endl;
	std::cout << message->getMessage() << std::endl;

	std::cout << "Sending GAMESTART to everyone" << std::endl;
	for(unsigned int i = 0; i < mSessionList->size(); i++){

		if((*mSessionList)[i]->getPlayer() != 0){
			(*mSessionList)[i]->sendMessage(
				mNMFactory->buildMessage(GAMESTART)
			);
		}

	}

}

void GameServerInstance::onGameEnd(
	NetworkMessage::GameEnd *message,
	GameServerSession *sourceSession
){
	using namespace NetworkMessage;

	std::cout << "Received GAMEEND" << std::endl;
	std::cout << message->getMessage() << std::endl;

	std::cout << "Sending GAMEEND to everyone" << std::endl;
	for(unsigned int i = 0; i < mSessionList->size(); i++){

		if((*mSessionList)[i]->getPlayer() != 0){
			(*mSessionList)[i]->sendMessage(
				mNMFactory->buildMessage(GAMEEND)
			);
		}

	}

}

void GameServerInstance::onPlayerInput(
	NetworkMessage::PlayerInput *message,
	GameServerSession *sourceSession
){
	using namespace NetworkMessage;

	std::cout << "Received PLAYERINPUT" << std::endl;
	std::cout << message->getMessage() << std::endl;

}

void GameServerInstance::onPlayerKilled(
	NetworkMessage::PlayerKilled *message,
	GameServerSession *sourceSession
){
	using namespace NetworkMessage;

	std::cout << "Received PLAYERKILLED" << std::endl;
	std::cout << message->getMessage() << std::endl;

}
