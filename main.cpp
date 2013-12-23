#include <iostream>
#include "src/Game.hpp"

int main(int argc, char *argv[]){

	try{
		Game *game = new Game();
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
