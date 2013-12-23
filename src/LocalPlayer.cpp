#include "LocalPlayer.hpp"

LocalPlayer::LocalPlayer(Ogre::String _name, CameraManager *_cameraManager){

	name = _name;
	cameraManager = _cameraManager;

}

LocalPlayer::~LocalPlayer(){
}

bool LocalPlayer::injectMouseMoved(const OIS::MouseEvent &arg){
	return cameraManager->injectMouseMoved(arg);
}

bool LocalPlayer::injectMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
	return cameraManager->injectMousePressed(arg, id);
}

bool LocalPlayer::injectMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
	return cameraManager->injectMouseReleased(arg, id);
}

bool LocalPlayer::injectKeyDown(const OIS::KeyEvent &arg){
	return cameraManager->injectKeyDown(arg);
}

bool LocalPlayer::injectKeyUp(const OIS::KeyEvent &arg){
	return cameraManager->injectKeyUp(arg);
}

bool LocalPlayer::frameRenderingQueued(const Ogre::FrameEvent &evt){
	return cameraManager->frameRenderingQueued(evt);
}
