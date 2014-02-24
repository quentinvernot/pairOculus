#include <iostream>
#include <boost/asio.hpp>
#include "src/GameServer/Instance.hpp"

using namespace std;

int main(){

    GameServer::Instance *gsi = new GameServer::Instance(1337);
    gsi->start();
 
    return 0;

}
