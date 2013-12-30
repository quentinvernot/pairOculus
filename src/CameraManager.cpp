#include "CameraManager.hpp"

CameraManager::CameraManager(Ogre::SceneManager *_sceneMgr) :
	mSceneMgr(_sceneMgr),
	mCameraMode("default"),
	mSimpleCamera(NULL),
	mOculusCamera(NULL)
{
}

CameraManager::~CameraManager(){

	if(mSimpleCamera)
		delete mSimpleCamera;
	if(mOculusCamera)
		delete mOculusCamera;

}

void CameraManager::createSimpleCamera(){

	// Create the camera
	Ogre::Camera *camera = mSceneMgr->createCamera("PlayerCam");

	// Position it at 500 in Z direction
	camera->setPosition(Ogre::Vector3(0,0,80));

	// Look back along -Z
	camera->lookAt(Ogre::Vector3(0,0,-300));
	camera->setNearClipDistance(1);

	if(mSimpleCamera == NULL)
		mSimpleCamera = new SimpleCamera(camera);
	else
		mSimpleCamera->setCamera(camera);

}

void CameraManager::createOculusCamera(){

	Ogre::Camera *cameraLeft = mSceneMgr->createCamera("PlayerCamLeft");
	Ogre::Camera *cameraRight = mSceneMgr->createCamera("PlayerCamRight");

	cameraLeft->setPosition(Ogre::Vector3(0,0,80));
	cameraRight->setPosition(Ogre::Vector3(0,0,80));

	cameraLeft->lookAt(Ogre::Vector3(0,0,-300));
	cameraRight->lookAt(Ogre::Vector3(0,0,-300));
	cameraLeft->setNearClipDistance(0.5);
	cameraRight->setNearClipDistance(0.5);

	if(mOculusCamera == 0)
		mOculusCamera = new OculusCamera(cameraLeft, cameraRight);
	else{
		mOculusCamera->setLeftCamera(cameraLeft);
		mOculusCamera->setRightCamera(cameraRight);
	}

}

void CameraManager::destroyCameras(){
	mSceneMgr->destroyAllCameras();
}

void CameraManager::move(const Ogre::Vector3 vec){

	if(mCameraMode == "oculus")
		mOculusCamera->move(vec);
	else
		mSimpleCamera->move(vec);

}

void CameraManager::yaw(Ogre::Radian ang){

	if(mCameraMode == "oculus")
		mOculusCamera->yaw(ang);
	else
		mSimpleCamera->yaw(ang);

}

void CameraManager::pitch(Ogre::Radian ang){

	if(mCameraMode == "oculus")
		mOculusCamera->pitch(ang);
	else
		mSimpleCamera->pitch(ang);

}

void CameraManager::roll(Ogre::Radian ang){

	if(mCameraMode == "oculus")
		mOculusCamera->roll(ang);
	else
		mSimpleCamera->roll(ang);

}

Ogre::Vector3 CameraManager::getDirection(){

	if(mCameraMode == "oculus")
		return mOculusCamera->getLeftCamera()->getDirection();
	return mSimpleCamera->getCamera()->getDirection();

}

Ogre::Vector3 CameraManager::getUp(){

	if(mCameraMode == "oculus")
		return mOculusCamera->getLeftCamera()->getUp();
	return mSimpleCamera->getCamera()->getUp();

}

Ogre::Vector3 CameraManager::getRight(){

	if(mCameraMode == "oculus")
		return mOculusCamera->getLeftCamera()->getRight();
	return mSimpleCamera->getCamera()->getRight();

}

void CameraManager::switchCameraMode(){

	if(mCameraMode == "default")
		setCameraMode("default");
	else if(mCameraMode == "oculus")
		setCameraMode("oculus");

}

Ogre::String CameraManager::getCameraMode(){return mCameraMode;}

void CameraManager::setCameraMode(Ogre::String mode){

	if(mode == "default"){

		mCameraMode = "default";
		destroyCameras();
		createSimpleCamera();

	}
	else if(mode == "oculus"){

		mCameraMode = "oculus";
		destroyCameras();
		createOculusCamera();

	}

}

Ogre::Camera *CameraManager::getCamera(){return mSimpleCamera->getCamera();}
Ogre::Camera *CameraManager::getOculusCameraLeft(){return mOculusCamera->getLeftCamera();}
Ogre::Camera *CameraManager::getOculusCameraRight(){return mOculusCamera->getRightCamera();}
