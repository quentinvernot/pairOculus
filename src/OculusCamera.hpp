#ifndef __OCULUSCAMERA_H
#define __OCULUSCAMERA_H

#include <OgreCamera.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>

class OculusCamera{

	public:
		OculusCamera(Ogre::Camera *leftCam, Ogre::Camera *rightCam);
		~OculusCamera();

		void move(Ogre::Vector3 vec);
		void yaw(Ogre::Radian ang);
		void pitch(Ogre::Radian ang);
		void roll(Ogre::Radian ang);

		void setPosition(Ogre::Vector3 pos);
		void setOrientation(Ogre::Quaternion pos);

		void setCameras(Ogre::Camera *leftCam, Ogre::Camera *rightCam);
		void setLeftCamera(Ogre::Camera *cam);
		void setRightCamera(Ogre::Camera *cam);
		Ogre::Camera *getLeftCamera();
		Ogre::Camera *getRightCamera();

	private:
		Ogre::Camera *mLeftCamera;
		Ogre::Camera *mRightCamera;
		Ogre::Radian mNodeYaw;
		Ogre::Radian mNodePitch;
		Ogre::Radian mNodeRoll;
		Ogre::Vector3 mNodePosition;
		Ogre::Vector3 mLeftCameraOffset;
		Ogre::Vector3 mRightCameraOffset;

};

#endif // __OCULUSCAMERA_H
