#include "GameServer.hpp"

namespace GameServer{

	GameServer::GameServer(){
		mInstance = new Instance(1337, mIo_service);
	}

	GameServer::~GameServer(){
	}

	void GameServer::start(){
		mIo_service.run();
	}

};
