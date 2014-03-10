#include "OculusCamera.hpp"

OculusCamera::OculusCamera(Ogre::Camera *leftCam, Ogre::Camera *rightCam):
	mLeftCamera(0),
	mRightCamera(0),
	mNodeYaw(0),
	mNodePitch(0),
	mNodeRoll(0),
	mNodePosition(0,0,0),
	mLeftCameraOffset(-0.32, 0.5, -0.5),
	mRightCameraOffset(0.32, 0.5, -0.5)
{

	setLeftCamera(leftCam);
	setRightCamera(rightCam);

	mLeftCamera->setPosition(mNodePosition);
	mLeftCamera->move(mLeftCameraOffset);
	mRightCamera->setPosition(mNodePosition);
	mRightCamera->move(mRightCameraOffset);

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
	mNodeYaw = ang;

	mLeftCameraOffset =
		Ogre::Quaternion(
			Ogre::Degree(mNodeYaw),
			Ogre::Vector3::UNIT_Y
		) * mLeftCameraOffset;

	mRightCameraOffset =
		Ogre::Quaternion(
			Ogre::Degree(mNodeYaw),
			Ogre::Vector3::UNIT_Y
		) * mRightCameraOffset;

	mLeftCamera->setPosition(mNodePosition);
	mLeftCamera->move(mLeftCameraOffset);

	mRightCamera->setPosition(mNodePosition);
	mRightCamera->move(mRightCameraOffset);

}

void OculusCamera::pitch(Ogre::Radian ang){

	mLeftCamera->pitch(ang);
	mRightCamera->pitch(ang);
	mNodePitch = ang;

	mLeftCameraOffset =
		Ogre::Quaternion(
			Ogre::Degree(mNodePitch),
			Ogre::Vector3::UNIT_X
		) * mLeftCameraOffset;

	mRightCameraOffset =
		Ogre::Quaternion(
			Ogre::Degree(mNodePitch),
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
	mNodeRoll = ang;

	mLeftCameraOffset =
		Ogre::Quaternion(
			Ogre::Degree(mNodeRoll),
			Ogre::Vector3::UNIT_Z
		) * mLeftCameraOffset;

	mRightCameraOffset =
		Ogre::Quaternion(
			Ogre::Degree(mNodeRoll),
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

	yaw(ori.getYaw() - mNodeYaw);
	pitch(ori.getPitch() - mNodeYaw);
	roll(ori.getRoll() - mNodeYaw);

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
