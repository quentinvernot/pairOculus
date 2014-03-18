/*
This source file is part of pairOculus, a student project aiming at creating a
simple 3D multiplayer game for the Oculus Rift.

Repository can be found here : https://github.com/Target6/pairOculus 

Copyright (c) 2013 Target6

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "CameraManager.hpp"

CameraManager::CameraManager(Ogre::SceneManager *sceneMgr) :
	mSceneMgr(sceneMgr),
	mCameraMode(SIMPLE),
	mSimpleCamera(NULL),
	mOculusCamera(NULL),
	mNodeYaw(0),
	mNodePitch(0),
	mNodeRoll(0),
	mNodePosition(0, 0, 0)
{
}

CameraManager::~CameraManager(){

	if(mSimpleCamera)
		delete mSimpleCamera;
	if(mOculusCamera)
		delete mOculusCamera;

}

void CameraManager::createSimpleCamera(){

	Ogre::Camera *camera = mSceneMgr->createCamera("PlayerCam");

	camera->setNearClipDistance(0.5);

	if(mSimpleCamera == NULL)
		mSimpleCamera = new SimpleCamera(camera);
	else
		mSimpleCamera->setCamera(camera);
	
	mSimpleCamera->setPosition(mNodePosition);
	mSimpleCamera->yaw(mNodeYaw);
	mSimpleCamera->pitch(mNodePitch);
	mSimpleCamera->roll(mNodeRoll);

}

void CameraManager::createOculusCamera(){

	Ogre::Camera *cameraLeft = mSceneMgr->createCamera("PlayerCamLeft");
	Ogre::Camera *cameraRight = mSceneMgr->createCamera("PlayerCamRight");

	cameraLeft->setNearClipDistance(0.5);
	cameraRight->setNearClipDistance(0.5);

	if(mOculusCamera == 0)
		mOculusCamera = new OculusCamera(cameraLeft, cameraRight);
	else{
		mOculusCamera->setLeftCamera(cameraLeft);
		mOculusCamera->setRightCamera(cameraRight);
	}

	mOculusCamera->setPosition(mNodePosition);
	mOculusCamera->yaw(mNodeYaw);
	mOculusCamera->pitch(mNodePitch);
	mOculusCamera->roll(mNodeRoll);

}

void CameraManager::destroyCameras(){
	mSceneMgr->destroyAllCameras();
}

void CameraManager::move(const Ogre::Vector3 vec){

	mNodePosition += vec;

	if(mCameraMode == OCULUS)
		mOculusCamera->move(vec);
	else
		mSimpleCamera->move(vec);

}

void CameraManager::yaw(Ogre::Radian ang){

	mNodeYaw += ang;

	if(mCameraMode == OCULUS)
		mOculusCamera->yaw(ang);
	else
		mSimpleCamera->yaw(ang);

}

void CameraManager::pitch(Ogre::Radian ang){

	mNodePitch += ang;

	if(mCameraMode == OCULUS)
		mOculusCamera->pitch(ang);
	else
		mSimpleCamera->pitch(ang);

}

void CameraManager::roll(Ogre::Radian ang){

	mNodeRoll += ang;

	if(mCameraMode == OCULUS)
		mOculusCamera->roll(ang);
	else
		mSimpleCamera->roll(ang);

}

void CameraManager::setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z){
	setPosition(Ogre::Vector3(x, y, z));
}

void CameraManager::setPosition(Ogre::Vector3 pos){

	mNodePosition = pos;

	if(mCameraMode == OCULUS)
		mOculusCamera->setPosition(pos);
	else
		mSimpleCamera->setPosition(pos);

}

Ogre::Quaternion CameraManager::getOrientation(){

	if(mCameraMode == OCULUS)
		return mOculusCamera->getOrientation();
	else
		return mSimpleCamera->getOrientation();

}

void CameraManager::setOrientation(Ogre::Quaternion ori){

	mNodeYaw = ori.getYaw();
	mNodePitch = ori.getPitch();
	mNodeRoll = ori.getRoll();

	if(mCameraMode == OCULUS)
		mOculusCamera->setOrientation(ori);
	else
		mSimpleCamera->setOrientation(ori);

}

void CameraManager::lookAt(Ogre::Vector3 vec){

	if(mCameraMode == OCULUS){
		mOculusCamera->lookAt(vec);
		mNodeYaw = mOculusCamera->getLeftCamera()->getOrientation().getYaw();
		mNodePitch = mOculusCamera->getLeftCamera()->getOrientation().getPitch();
		mNodeRoll = 0;
	}
	else{
		mSimpleCamera->lookAt(vec);
		mNodeYaw = mSimpleCamera->getCamera()->getOrientation().getYaw();
		mNodePitch = mSimpleCamera->getCamera()->getOrientation().getPitch();
		mNodeRoll = 0;
	}

}

void CameraManager::increaseIPD(){
	if(mOculusCamera)
		mOculusCamera->increaseIPD();
}
void CameraManager::decreaseIPD(){
	if(mOculusCamera)
		mOculusCamera->decreaseIPD();
}

Ogre::Vector3 CameraManager::getDirection(){

	if(mCameraMode == OCULUS)
		return mOculusCamera->getLeftCamera()->getDirection();
	return mSimpleCamera->getCamera()->getDirection();

}

Ogre::Vector3 CameraManager::getUp(){

	if(mCameraMode == OCULUS)
		return mOculusCamera->getLeftCamera()->getUp();
	return mSimpleCamera->getCamera()->getUp();

}

Ogre::Vector3 CameraManager::getRight(){

	if(mCameraMode == OCULUS)
		return mOculusCamera->getLeftCamera()->getRight();
	return mSimpleCamera->getCamera()->getRight();

}

Ogre::Vector3 CameraManager::getForwardDirection(){

	Ogre::Vector3 direction;

	if(mCameraMode == OCULUS)
		direction = mOculusCamera->getLeftCamera()->getDirection();
	else
		direction = mSimpleCamera->getCamera()->getDirection();

	direction.y = 0;
	direction.normalise();

	return direction;

}

Ogre::Vector3 CameraManager::getUpDirection(){
	return Ogre::Vector3::UNIT_Y;
}

Ogre::Vector3 CameraManager::getRightDirection(){

	Ogre::Vector3 direction;

	if(mCameraMode == OCULUS)
		direction = mOculusCamera->getLeftCamera()->getRight();
	else
		direction = mSimpleCamera->getCamera()->getRight();

	direction.y = 0;
	direction.normalise();

	return direction;

}

void CameraManager::switchCameraMode(){

	if(mCameraMode == SIMPLE)
		setCameraMode(SIMPLE);
	else if(mCameraMode == OCULUS)
		setCameraMode(OCULUS);

}

ViewMode CameraManager::getCameraMode(){return mCameraMode;}

void CameraManager::setCameraMode(ViewMode mode){

	if(mode == SIMPLE){

		mCameraMode = SIMPLE;
		destroyCameras();
		createSimpleCamera();

	}
	else if(mode == OCULUS){

		mCameraMode = OCULUS;
		destroyCameras();
		createOculusCamera();

	}

}

Ogre::Camera *CameraManager::getCamera(){return mSimpleCamera->getCamera();}
Ogre::Camera *CameraManager::getOculusCameraLeft(){return mOculusCamera->getLeftCamera();}
Ogre::Camera *CameraManager::getOculusCameraRight(){return mOculusCamera->getRightCamera();}
