#include "GameWindow.hpp"

GameWindow::GameWindow() :
	mCameraManager(0),
	mOgreWindow(0),
	mViewMode("default"),
	mStereoConfig(0)
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

	mStereoConfig = new OVR::Util::Render::StereoConfig();

	Ogre::Viewport* vpLeft = mOgreWindow->addViewport(
		mCameraManager->getOculusCameraLeft(), 1, 0, 0, 0.5, 1
	);
	Ogre::Viewport* vpRight = mOgreWindow->addViewport(
		mCameraManager->getOculusCameraRight(), 2, 0.5, 0, 0.5, 1
	);

	vpLeft->setBackgroundColour(Ogre::ColourValue(1,1,1));
	vpRight->setBackgroundColour(Ogre::ColourValue(1,1,1));

	vpLeft->setOverlaysEnabled(false);
	vpRight->setOverlaysEnabled(false);

	Ogre::MaterialPtr matLeft = Ogre::MaterialManager::getSingleton().getByName("Ogre/Compositor/Oculus");
	Ogre::MaterialPtr matRight = matLeft->clone("Ogre/Compositor/Oculus/Right");
	Ogre::GpuProgramParametersSharedPtr pParamsLeft = matLeft->getTechnique(0)->getPass(0)->getFragmentProgramParameters();
	Ogre::GpuProgramParametersSharedPtr pParamsRight = matRight->getTechnique(0)->getPass(0)->getFragmentProgramParameters();

	Ogre::Vector4 hmdwarp(0,0,0,0);

	if(mStereoConfig){
		hmdwarp = Ogre::Vector4(
			mStereoConfig->GetDistortionK(0),
			mStereoConfig->GetDistortionK(1),
			mStereoConfig->GetDistortionK(2),
			mStereoConfig->GetDistortionK(3)
		);
	}

	pParamsLeft->setNamedConstant("HmdWarpParam", hmdwarp);
	pParamsRight->setNamedConstant("HmdWarpParam", hmdwarp);
	pParamsLeft->setNamedConstant("LensCentre", 0.5f+(mStereoConfig->GetProjectionCenterOffset()/2.0f));
	pParamsRight->setNamedConstant("LensCentre", 0.5f-(mStereoConfig->GetProjectionCenterOffset()/2.0f));

	Ogre::CompositorPtr comp = Ogre::CompositorManager::getSingleton().getByName("OculusRight");
	comp->getTechnique(0)->getOutputTargetPass()->getPass(0)->setMaterialName("Ogre/Compositor/Oculus/Right");

	Ogre::CompositorManager::getSingleton().addCompositor(
		vpLeft, "OculusLeft"
	);
	Ogre::CompositorManager::getSingleton().setCompositorEnabled(
		vpLeft, "OculusLeft", true
	);
	Ogre::CompositorManager::getSingleton().addCompositor(
		vpRight, "OculusRight"
	);
	Ogre::CompositorManager::getSingleton().setCompositorEnabled(
		vpRight, "OculusRight", true
	);

}

void GameWindow::destroyViewports(){
	mOgreWindow->removeAllViewports();
}

Ogre::RenderWindow *GameWindow::getWindow(){return mOgreWindow;}
