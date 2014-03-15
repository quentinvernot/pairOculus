#include "OculusCamera.hpp"

OculusCamera::OculusCamera(Ogre::Camera *leftCam, Ogre::Camera *rightCam):
	mIPD(0.64),
	mLeftCamera(0),
	mRightCamera(0),
	mNodePosition(0,0,0),
	mBaseOffset(mIPD/8, 0.15, 0.25),
	mCameraOffset(0, 0, 0)
{

	setLeftCamera(leftCam);
	setRightCamera(rightCam);
	setPosition(mNodePosition);
	applyOffset();

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
	removeOffset();
	applyOffset();

}

void OculusCamera::pitch(Ogre::Radian ang){

	mLeftCamera->pitch(ang);
	mRightCamera->pitch(ang);
	removeOffset();
	applyOffset();

}

void OculusCamera::roll(Ogre::Radian ang){

	mLeftCamera->roll(ang);
	mRightCamera->roll(ang);
	removeOffset();
	applyOffset();

}

void OculusCamera::setPosition(Ogre::Vector3 pos){

	mLeftCamera->setPosition(pos);
	mRightCamera->setPosition(pos);
	mNodePosition = pos;
	applyOffset();

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

	removeOffset();
	mLeftCamera->lookAt(vec);
	mRightCamera->lookAt(vec);
	applyOffset();

}

void OculusCamera::increaseIPD(){
	mIPD += 0.02;
	mBaseOffset.x = mIPD/8;
}

void OculusCamera::decreaseIPD(){
	mIPD -= 0.02;
	mBaseOffset.x = mIPD/8;
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

void OculusCamera::removeOffset(){

	mRightCamera->setPosition(mNodePosition);
	mLeftCamera->setPosition(mNodePosition);

}

void OculusCamera::applyOffset(){

	mCameraOffset = Ogre::Vector3::ZERO;
	mCameraOffset += mRightCamera->getRight() * mBaseOffset.x;
	mCameraOffset += mRightCamera->getUp() * mBaseOffset.y;
	mCameraOffset += mRightCamera->getDirection() * mBaseOffset.z;

	mRightCamera->move(mCameraOffset);
	mCameraOffset -= 2 * mRightCamera->getRight() * mBaseOffset.x;
	mLeftCamera->move(mCameraOffset);

}
