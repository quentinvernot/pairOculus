#include "CameraManager.hpp"

CameraManager::CameraManager(Ogre::SceneManager *_sceneMgr) :
	sceneMgr(_sceneMgr),
	camera(0),
	cameraLeft(0),
	cameraRight(0),
	cameraMode("default"),
	cameraMan(0),
	oculusCameraMan(0)
{
}

CameraManager::~CameraManager(){

	if(cameraMan)
		delete cameraMan;
	if(oculusCameraMan)
		delete oculusCameraMan;

}

void CameraManager::createCamera(){

	// Create the camera
	camera = sceneMgr->createCamera("PlayerCam");

	// Position it at 500 in Z direction
	camera->setPosition(Ogre::Vector3(0,0,80));

	// Look back along -Z
	camera->lookAt(Ogre::Vector3(0,0,-300));
	camera->setNearClipDistance(1);

	if(cameraMan == 0)
		cameraMan = new OgreBites::SdkCameraMan(camera);
	else
		cameraMan->setCamera(camera);

}

void CameraManager::createOculusCamera(){

	cameraLeft = sceneMgr->createCamera("PlayerCamLeft");
	cameraRight = sceneMgr->createCamera("PlayerCamRight");

	cameraLeft->setPosition(Ogre::Vector3(0,0,80));
	cameraRight->setPosition(Ogre::Vector3(0,0,80));

	cameraLeft->lookAt(Ogre::Vector3(0,0,-300));
	cameraRight->lookAt(Ogre::Vector3(0,0,-300));
	cameraLeft->setNearClipDistance(0.5);
	cameraRight->setNearClipDistance(0.5);

	if(oculusCameraMan == 0)
		oculusCameraMan = new OculusUtils::OculusCameraMan(cameraLeft, cameraRight);
	else{
		oculusCameraMan->setLeftCamera(cameraLeft);
		oculusCameraMan->setRightCamera(cameraRight);
	}

}

void CameraManager::destroyCameras(){
	sceneMgr->destroyAllCameras();
}

bool CameraManager::injectMouseMoved(const OIS::MouseEvent &arg){

	if(cameraMode == "oculus")
		oculusCameraMan->injectMouseMove(arg);
	else
		cameraMan->injectMouseMove(arg);

	return true;
}

bool CameraManager::injectMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id){

	if(cameraMode == "oculus")
		oculusCameraMan->injectMouseDown(arg, id);
	else
		cameraMan->injectMouseDown(arg, id);

	return true;
}

bool CameraManager::injectMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){

	if(cameraMode == "oculus")
		oculusCameraMan->injectMouseUp(arg, id);
	else
		cameraMan->injectMouseUp(arg, id);

	return true;
}

bool CameraManager::injectKeyDown(const OIS::KeyEvent &arg){

	if (arg.key == OIS::KC_A)
		switchCameraMode();

	if(cameraMode == "oculus")
		oculusCameraMan->injectKeyDown(arg);
	else
		cameraMan->injectKeyDown(arg);

	return true;

}

bool CameraManager::injectKeyUp(const OIS::KeyEvent &arg){

	if(cameraMode == "oculus")
		oculusCameraMan->injectKeyUp(arg);
	else
		cameraMan->injectKeyUp(arg);

	return true;

}

bool CameraManager::frameRenderingQueued(const Ogre::FrameEvent &evt){

	if(cameraMode == "oculus")
		oculusCameraMan->frameRenderingQueued(evt);
	else
		cameraMan->frameRenderingQueued(evt);

	return true;

}

Ogre::Camera *CameraManager::getCamera(){return camera;}
Ogre::Camera *CameraManager::getOculusCameraLeft(){return cameraLeft;}
Ogre::Camera *CameraManager::getOculusCameraRight(){return cameraRight;}

void CameraManager::switchCameraMode(){

	if(cameraMode == "default")
		setCameraMode("default");
	else if(cameraMode == "oculus")
		setCameraMode("oculus");

}

Ogre::String CameraManager::getCameraMode(){return cameraMode;}

void CameraManager::setCameraMode(Ogre::String mode){

	if(mode == "default"){

		cameraMode = "default";
		destroyCameras();
		createCamera();

	}
	else if(mode == "oculus"){

		cameraMode = "oculus";
		destroyCameras();
		createOculusCamera();

	}

}
