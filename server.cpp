#include <iostream>
#include <boost/asio.hpp>
#include "src/GameServer.hpp"

using namespace std;

int main(){

    GameServer *gs = new GameServer();
    gs->start();

    return 0;

}
