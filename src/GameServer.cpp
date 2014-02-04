#include "GameServer.hpp"

GameServer::GameServer(){
	instance = new GameServerInstance(1337, io_service);
}

GameServer::~GameServer(){
}

void GameServer::start(){
    io_service.run();
}
