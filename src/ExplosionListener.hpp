#ifndef __EXPLOSIONLISTENER_H
#define __EXPLOSIONLISTENER_H

#include <string>
#include <OgreVector3.h>

class ExplosionListener{

	public:
		//Methods
		virtual ~ExplosionListener(){};
		virtual bool bombExploded(Ogre::Vector3 position, int range)=0;

};

#endif //__EXPLOSIONLISTENER_H
