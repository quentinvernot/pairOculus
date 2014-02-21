#include <iostream>
#include "src/GameClient/GameClient.hpp"
#include "src/PlayerList.hpp"

using namespace std;
using namespace NetworkMessage;

int main(){

	NetworkMessageFactory *test = new NetworkMessageFactory();

	NetworkMessage::NetworkMessage *aa = test->buildMessage(JOIN, "Target6");
	std::cout << aa->getMessage() << std::endl;

	GameClient::GameClient *gc = new GameClient::GameClient("127.0.0.1", "1337");
	gc->start();
	gc->sendMessage(aa);

	int a;
	std::cin >> a;

    return 0;

}
