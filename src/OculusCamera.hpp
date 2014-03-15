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
		Ogre::Quaternion getOrientation();
		void setOrientation(Ogre::Quaternion pos);
		void lookAt(Ogre::Vector3 vec);

		void increaseIPD();
		void decreaseIPD();

		void setCameras(Ogre::Camera *leftCam, Ogre::Camera *rightCam);
		void setLeftCamera(Ogre::Camera *cam);
		void setRightCamera(Ogre::Camera *cam);
		Ogre::Camera *getLeftCamera();
		Ogre::Camera *getRightCamera();

	private:
		//Methods
		void removeOffset();
		void applyOffset();

		//Attributes
		Ogre::Real mIPD; //Interpupillary Distance
		Ogre::Camera *mLeftCamera;
		Ogre::Camera *mRightCamera;
		Ogre::Vector3 mNodePosition;
		Ogre::Vector3 mBaseOffset;
		Ogre::Vector3 mCameraOffset;

};

#endif // __OCULUSCAMERA_H
