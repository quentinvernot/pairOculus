#include "CameraManager.hpp"

CameraManager::CameraManager(Ogre::SceneManager *_sceneMgr) :
	mSceneMgr(_sceneMgr),
	mCameraMode("default"),
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

	// Create the camera
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

	if(mCameraMode == "oculus")
		mOculusCamera->move(vec);
	else
		mSimpleCamera->move(vec);

}

void CameraManager::yaw(Ogre::Radian ang){

	mNodeYaw += ang;

	if(mCameraMode == "oculus")
		mOculusCamera->yaw(ang);
	else
		mSimpleCamera->yaw(ang);

}

void CameraManager::pitch(Ogre::Radian ang){

	mNodePitch += ang;

	if(mCameraMode == "oculus")
		mOculusCamera->pitch(ang);
	else
		mSimpleCamera->pitch(ang);

}

void CameraManager::roll(Ogre::Radian ang){

	mNodeRoll += ang;

	if(mCameraMode == "oculus")
		mOculusCamera->roll(ang);
	else
		mSimpleCamera->roll(ang);

}

void CameraManager::setPosition(Ogre::Vector3 pos){

	mNodePosition = pos;

	if(mCameraMode == "oculus")
		mOculusCamera->setPosition(pos);
	else
		mSimpleCamera->setPosition(pos);

}

void CameraManager::setOrientation(Ogre::Quaternion ori){

	mNodeYaw = ori.getYaw();
	mNodePitch = ori.getPitch();
	mNodeRoll = ori.getRoll();

	if(mCameraMode == "oculus")
		mOculusCamera->setOrientation(ori);
	else
		mSimpleCamera->setOrientation(ori);

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

Ogre::Vector3 CameraManager::getForwardDirection(){

	Ogre::Vector3 direction;

	if(mCameraMode == "oculus")
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

	if(mCameraMode == "oculus")
		direction = mOculusCamera->getLeftCamera()->getRight();
	else
		direction = mSimpleCamera->getCamera()->getRight();

	direction.y = 0;
	direction.normalise();

	return direction;

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
