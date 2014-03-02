#include "SimpleCamera.hpp"

SimpleCamera::SimpleCamera(Ogre::Camera *cam):
	mCamera(0)
{
	setCamera(cam);
}

SimpleCamera::~SimpleCamera() {}

void SimpleCamera::move(Ogre::Vector3 vec){
	mCamera->move(vec);
}

void SimpleCamera::yaw(Ogre::Radian ang){
	mCamera->yaw(ang);
}

void SimpleCamera::pitch(Ogre::Radian ang){
	mCamera->pitch(ang);
}

void SimpleCamera::roll(Ogre::Radian ang){
	mCamera->roll(ang);
}

void SimpleCamera::setPosition(Ogre::Vector3 pos){
	mCamera->setPosition(pos);
}

void SimpleCamera::setOrientation(Ogre::Quaternion ori){
	mCamera->setOrientation(ori);
}

void SimpleCamera::setCamera(Ogre::Camera *cam){
	mCamera = cam;
}

Ogre::Camera *SimpleCamera::getCamera(){
	return mCamera;
}
