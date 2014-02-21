#include "Instance.hpp"

namespace GameServer{

	Instance::Instance(
		unsigned short port,
		boost::asio::io_service& io_service
	) :
		mIo_service(io_service),
		mAcceptor(mIo_service, tcp::endpoint(tcp::v4(), port)),
		mSession(0),
		mSessionList(new SessionList),
		mPlayerList(new PlayerList()),
		mNMFactory(new NetworkMessage::NetworkMessageFactory())
	{
		start();
	}

	Instance::~Instance(){
	}

	void Instance::start(){

		mSession = new Session(
			mIo_service,
			boost::bind(
				&Instance::handleReceive,
				this,
				_1,
				_2
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

	}

	void Instance::handleAccept(
		Session *Session,
		const boost::system::error_code& error
	){

		if (!error){
			mSessionList->addSession(Session);
			Session->start();
		}

		start();

	}

	void Instance::handleReceive(
		NetworkMessage::NetworkMessage *message,
		Session *sourceSession
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

	void Instance::onLeave(
		NetworkMessage::Leave *message,
		Session *sourceSession
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

	void Instance::onJoinAccept(
		NetworkMessage::JoinAccept *message,
		Session *sourceSession
	){
		using namespace NetworkMessage;

		std::cout << "Received JOINACCEPT" << std::endl;
		std::cout << message->getMessage() << std::endl;

	}

	void Instance::onJoinRefuse(
		NetworkMessage::JoinRefuse *message,
		Session *sourceSession
	){
		using namespace NetworkMessage;

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

	void Instance::onGameEnd(
		NetworkMessage::GameEnd *message,
		Session *sourceSession
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

	void Instance::onPlayerInput(
		NetworkMessage::PlayerInput *message,
		Session *sourceSession
	){
		using namespace NetworkMessage;

		std::cout << "Received PLAYERINPUT" << std::endl;
		std::cout << message->getMessage() << std::endl;

	}

	void Instance::onPlayerKilled(
		NetworkMessage::PlayerKilled *message,
		Session *sourceSession
	){
		using namespace NetworkMessage;

		std::cout << "Received PLAYERKILLED" << std::endl;
		std::cout << message->getMessage() << std::endl;

	}

};
