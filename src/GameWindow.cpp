#include "GameWindow.hpp"

GameWindow::GameWindow() :
	mCameraManager(0),
	mOgreWindow(0),
	mViewMode("default")
{
}

GameWindow::GameWindow(
	CameraManager *cameraManager,
	Ogre::RenderWindow *ogreWindow
) :
	mCameraManager(cameraManager),
	mOgreWindow(ogreWindow),
	mViewMode("default")
{
}

GameWindow::~GameWindow(){
}

void GameWindow::switchViewMode(){

	if(mViewMode == "default")
		setViewMode("oculus");
	else if(mViewMode == "oculus")
		setViewMode("default");

}

void GameWindow::setViewMode(Ogre::String mode){

	if(mode == "default"){

		mViewMode = "default";
		destroyViewports();
		mCameraManager->setCameraMode(mode);
		createSimpleViewport();

	}
	else if(mode == "oculus"){

		mViewMode = "oculus";
		destroyViewports();
		mCameraManager->setCameraMode(mode);
		createOculusViewports();

	}

}

bool GameWindow::injectKeyDown(const OIS::KeyEvent &arg){

	if(arg.key == OIS::KC_A)
		switchViewMode();

	return true;

}

void GameWindow::createSimpleViewport(){

	// Create one viewport, entire window
	Ogre::Viewport* vp = mOgreWindow->addViewport(
		mCameraManager->getCamera(), 0, 0, 0, 1, 1
	);

	vp->setBackgroundColour(Ogre::ColourValue(1,1,1));

	// Alter the camera aspect ratio to match the viewport
	mCameraManager->getCamera()->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

}

void GameWindow::createOculusViewports(){

	Ogre::Viewport* vpLeft = mOgreWindow->addViewport(
		mCameraManager->getOculusCameraLeft(), 1, 0, 0, 0.5, 1
	);
	Ogre::Viewport* vpRight = mOgreWindow->addViewport(
		mCameraManager->getOculusCameraRight(), 2, 0.5, 0, 0.5, 1
	);

	vpLeft->setBackgroundColour(Ogre::ColourValue(1,1,1));
	vpRight->setBackgroundColour(Ogre::ColourValue(1,1,1));

	mCameraManager->getOculusCameraLeft()->setAspectRatio(
		Ogre::Real(vpLeft->getActualWidth())
		/ Ogre::Real(vpLeft->getActualHeight())
	);
	mCameraManager->getOculusCameraRight()->setAspectRatio(
		Ogre::Real(vpRight->getActualWidth())
		/ Ogre::Real(vpRight->getActualHeight())
	);

	vpLeft->setOverlaysEnabled(false);
	vpRight->setOverlaysEnabled(false);

	Ogre::CompositorManager::getSingleton().addCompositor(
		mCameraManager->getOculusCameraLeft()->getViewport(), "Oculus"
	);
	Ogre::CompositorManager::getSingleton().setCompositorEnabled(
		mCameraManager->getOculusCameraLeft()->getViewport(), "Oculus", true
	);
	Ogre::CompositorManager::getSingleton().addCompositor(
		mCameraManager->getOculusCameraRight()->getViewport(), "Oculus"
	);
	Ogre::CompositorManager::getSingleton().setCompositorEnabled(
		mCameraManager->getOculusCameraRight()->getViewport(), "Oculus", true
	);

}

void GameWindow::destroyViewports(){
	mOgreWindow->removeAllViewports();
}

Ogre::RenderWindow *GameWindow::getWindow(){return mOgreWindow;}
