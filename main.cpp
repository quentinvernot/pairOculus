#include <iostream>
#include "src/Game.hpp"

int main(int argc, char *argv[]){

	if(argc <= 1 || argc == 3){
		std::cout << "USAGE: main <nickname> [<server address> <server port>]" << std::endl;
		return 1;
	}

	try{
		Game *game;
		if(argc == 2)
			game = new Game(argv[1]);
		else
			game = new Game(argv[1], argv[2], argv[3]);
		game->go();
		delete game;
	}
	catch(Ogre::Exception& e){
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		std::cerr << "An exception has occured: " <<
		e.getFullDescription().c_str() << std::endl;
#endif
	}

	return 0;

}
