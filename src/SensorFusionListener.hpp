#ifndef __SENSORFUSIONLISTENER_H
#define __SENSORFUSIONLISTENER_H

#include <OgreVector3.h>
#include <OVR.h>

class SensorFusionListener{

	public:
		//Methods
		virtual ~SensorFusionListener(){};
		virtual bool headMoved(const Ogre::Vector3 &evt)=0;

};

#endif //__SENSORFUSIONLISTENER_H
