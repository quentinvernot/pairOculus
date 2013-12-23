#include "GameWindow.hpp"

GameWindow::GameWindow() :
	cameraManager(0),
	ogreWindow(0),
	viewMode("default")
{
}

GameWindow::GameWindow(
	CameraManager *_cameraManager,
	Ogre::RenderWindow *_ogreWindow
) :
	viewMode("default")
{

	cameraManager = _cameraManager;
	ogreWindow = _ogreWindow;

}

GameWindow::~GameWindow(){
}

void GameWindow::switchViewMode(){

	if(viewMode == "default")
		setViewMode("default");
	else if(viewMode == "oculus")
		setViewMode("oculus");

}

void GameWindow::setViewMode(Ogre::String mode){

	if(mode == "default"){

		viewMode = "default";
		destroyViewports();
		cameraManager->setCameraMode(mode);
		createSimpleViewport();

	}
	else if(mode == "oculus"){

		viewMode = "oculus";
		destroyViewports();
		cameraManager->setCameraMode(mode);
		createOculusViewports();

	}

}

void GameWindow::createSimpleViewport(){
	// Create one viewport, entire window
	Ogre::Viewport* vp = ogreWindow->addViewport(
		cameraManager->getCamera(), 0, 0, 0, 1, 1
	);

	vp->setBackgroundColour(Ogre::ColourValue(1,1,1));

	// Alter the camera aspect ratio to match the viewport
	cameraManager->getCamera()->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

}

void GameWindow::createOculusViewports(){

	Ogre::Viewport* vpLeft = ogreWindow->addViewport(
		cameraManager->getOculusCameraLeft(), 1, 0, 0, 0.5, 1
	);
	Ogre::Viewport* vpRight = ogreWindow->addViewport(
		cameraManager->getOculusCameraRight(), 2, 0.5, 0, 0.5, 1
	);

	vpLeft->setBackgroundColour(Ogre::ColourValue(1,1,1));
	vpRight->setBackgroundColour(Ogre::ColourValue(1,1,1));

	cameraManager->getOculusCameraLeft()->setAspectRatio(
		Ogre::Real(vpLeft->getActualWidth())
		/ Ogre::Real(vpLeft->getActualHeight())
	);
	cameraManager->getOculusCameraRight()->setAspectRatio(
		Ogre::Real(vpRight->getActualWidth())
		/ Ogre::Real(vpRight->getActualHeight())
	);

	vpLeft->setOverlaysEnabled(false);
	vpRight->setOverlaysEnabled(false);

	Ogre::CompositorManager::getSingleton().addCompositor(
		cameraManager->getOculusCameraLeft()->getViewport(), "Oculus"
	);
	Ogre::CompositorManager::getSingleton().setCompositorEnabled(
		cameraManager->getOculusCameraLeft()->getViewport(), "Oculus", true
	);
	Ogre::CompositorManager::getSingleton().addCompositor(
		cameraManager->getOculusCameraRight()->getViewport(), "Oculus"
	);
	Ogre::CompositorManager::getSingleton().setCompositorEnabled(
		cameraManager->getOculusCameraRight()->getViewport(), "Oculus", true
	);

}

void GameWindow::destroyViewports(){
	ogreWindow->removeAllViewports();
}

Ogre::RenderWindow *GameWindow::getWindow(){return ogreWindow;}
