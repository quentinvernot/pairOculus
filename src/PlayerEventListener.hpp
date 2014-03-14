#ifndef __PLAYEREVENTLISTENER_H
#define __PLAYEREVENTLISTENER_H

#include "LocalPlayer.hpp"
#include <OgreVector3.h>

class PlayerEventListener{

	public:
		//Methods
		virtual ~PlayerEventListener(){};
		virtual bool playerInput()=0;
		virtual bool playerDied()=0;

};

#endif //__PLAYEREVENTLISTENER_H
