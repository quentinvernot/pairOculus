#ifndef __SIMPLECAMERA_H
#define __SIMPLECAMERA_H

#include <OgreCamera.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>

class SimpleCamera{

	public:
		SimpleCamera(Ogre::Camera *cam);
		~SimpleCamera();

		void move(Ogre::Vector3 vec);
		void yaw(Ogre::Radian ang);
		void pitch(Ogre::Radian ang);
		void roll(Ogre::Radian ang);

		void setPosition(Ogre::Vector3 pos);
		Ogre::Quaternion getOrientation();
		void setOrientation(Ogre::Quaternion ori);
		void lookAt(Ogre::Vector3 vec);

		void setCamera(Ogre::Camera *cam);
		Ogre::Camera *getCamera();

	private:
		Ogre::Camera *mCamera;

};

#endif // __SIMPLECAMERA_H
