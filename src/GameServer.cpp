#include "GameServer.hpp"

GameServer::GameServer(){
	mInstance = new GameServerInstance(1337, mIo_service);
}

GameServer::~GameServer(){
}

void GameServer::start(){
    mIo_service.run();
}
