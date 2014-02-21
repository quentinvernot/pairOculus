#include <iostream>
#include <boost/asio.hpp>
#include "src/GameServer/GameServer.hpp"

using namespace std;

int main(){

    GameServer::GameServer *gs = new GameServer::GameServer();
    gs->start();
 
    return 0;

}
