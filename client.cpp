#include <iostream>
#include "src/GameClient/Listener.hpp"
#include "src/PlayerList.hpp"

using namespace std;
using namespace NetworkMessage;
using namespace GameClient;

int main(int argc, char **argv){

	if(argc < 2)
		return 1;

	NetworkMessageFactory *test = new NetworkMessageFactory();
	NetworkMessage::NetworkMessage *aa = test->buildMessage(JOIN, argv[1]);

	Listener *gc = new Listener("127.0.0.1", "1337");
	gc->start();
	gc->sendMessage(aa);
	sleep(1);
	gc->stop();

    return 0;

}
