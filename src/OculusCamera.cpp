#include "OculusCamera.hpp"

OculusCamera::OculusCamera(Ogre::Camera *leftCam, Ogre::Camera *rightCam):
	mLeftCamera(0),
	mRightCamera(0),
	mNodePosition(0,0,0),
	mLeftCameraOffset(0, 0, 0),
	mRightCameraOffset(0, 0, 0)
{

	setLeftCamera(leftCam);
	setRightCamera(rightCam);
	setOrientation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_Y));
	mLeftCameraOffset = Ogre::Vector3(0, 1, 0);
	mRightCameraOffset = Ogre::Vector3(0, 1, 0);
	setPosition(mNodePosition);

}

OculusCamera::~OculusCamera() {}

void OculusCamera::move(Ogre::Vector3 vec){

	mLeftCamera->move(vec);
	mRightCamera->move(vec);
	mNodePosition += vec;

}

void OculusCamera::yaw(Ogre::Radian ang){

	mLeftCamera->yaw(ang);
	mRightCamera->yaw(ang);

	mLeftCameraOffset =
		Ogre::Quaternion(
			ang,
			Ogre::Vector3::UNIT_Y
		) * mLeftCameraOffset;
std::cout << "a" << mLeftCameraOffset.x << " " << mLeftCameraOffset.y << " " << mLeftCameraOffset.z << std::endl;
	mRightCameraOffset =
		Ogre::Quaternion(
			ang,
			Ogre::Vector3::UNIT_Y
		) * mRightCameraOffset;
std::cout << "z" << mRightCameraOffset.x << " " << mRightCameraOffset.y << " " << mRightCameraOffset.z << std::endl;
	mLeftCamera->setPosition(mNodePosition);
	mLeftCamera->move(mLeftCameraOffset);

	mRightCamera->setPosition(mNodePosition);
	mRightCamera->move(mRightCameraOffset);

}

void OculusCamera::pitch(Ogre::Radian ang){

	mLeftCamera->pitch(ang);
	mRightCamera->pitch(ang);

	mLeftCameraOffset =
		Ogre::Quaternion(
			ang,
			Ogre::Vector3::UNIT_X
		) * mLeftCameraOffset;

	mRightCameraOffset =
		Ogre::Quaternion(
			ang,
			Ogre::Vector3::UNIT_X
		) * mRightCameraOffset;

	mLeftCamera->setPosition(mNodePosition);
	mLeftCamera->move(mLeftCameraOffset);

	mRightCamera->setPosition(mNodePosition);
	mRightCamera->move(mRightCameraOffset);

}

void OculusCamera::roll(Ogre::Radian ang){

	mLeftCamera->roll(ang);
	mRightCamera->roll(ang);

	mLeftCameraOffset =
		Ogre::Quaternion(
			ang,
			Ogre::Vector3::UNIT_Z
		) * mLeftCameraOffset;

	mRightCameraOffset =
		Ogre::Quaternion(
			ang,
			Ogre::Vector3::UNIT_Z
		) * mRightCameraOffset;

	mLeftCamera->setPosition(mNodePosition);
	mLeftCamera->move(mLeftCameraOffset);

	mRightCamera->setPosition(mNodePosition);
	mRightCamera->move(mRightCameraOffset);

}

void OculusCamera::setPosition(Ogre::Vector3 pos){

	mLeftCamera->setPosition(pos);
	mLeftCamera->move(mLeftCameraOffset);
	mRightCamera->setPosition(pos);
	mRightCamera->move(mRightCameraOffset);
	mNodePosition = pos;

}

Ogre::Quaternion OculusCamera::getOrientation(){
	return mLeftCamera->getOrientation();
}

void OculusCamera::setOrientation(Ogre::Quaternion ori){

	yaw(ori.getYaw() - mLeftCamera->getOrientation().getYaw());
	pitch(ori.getPitch() - mLeftCamera->getOrientation().getPitch());
	roll(ori.getRoll() - mLeftCamera->getOrientation().getRoll());

}

void OculusCamera::lookAt(Ogre::Vector3 vec){

	mLeftCamera->setPosition(mNodePosition);
	mRightCamera->setPosition(mNodePosition);

	mLeftCamera->lookAt(vec);
	mRightCamera->lookAt(vec);

	mLeftCamera->move(mLeftCameraOffset);
	mRightCamera->move(mRightCameraOffset);

}

void OculusCamera::setCameras(Ogre::Camera *leftCam, Ogre::Camera *rightCam){
	mLeftCamera = leftCam;
	mRightCamera = rightCam;
}

void OculusCamera::setLeftCamera(Ogre::Camera *cam){
	mLeftCamera = cam;
}

void OculusCamera::setRightCamera(Ogre::Camera *cam){
	mRightCamera = cam;
}

Ogre::Camera *OculusCamera::getLeftCamera(){
	return mLeftCamera;
}

Ogre::Camera *OculusCamera::getRightCamera(){
	return mRightCamera;
}
