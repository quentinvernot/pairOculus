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

#include "GameWindow.hpp"

GameWindow::GameWindow(
	CameraManager *cameraManager,
	Ogre::RenderWindow *ogreWindow
) :
	mCameraManager(cameraManager),
	mOgreWindow(ogreWindow),
	mViewMode(SIMPLE),
	mStereoConfig(0)
{
}

GameWindow::~GameWindow(){
}

void GameWindow::switchViewMode(){

	if(mViewMode == SIMPLE)
		setViewMode(OCULUS);
	else if(mViewMode == OCULUS)
		setViewMode(SIMPLE);

}

void GameWindow::setViewMode(ViewMode mode){

	if(mode == SIMPLE){

		mViewMode = SIMPLE;
		destroyViewports();
		mCameraManager->setCameraMode(mode);
		createSimpleViewport();

	}
	else if(mode == OCULUS){

		mViewMode = OCULUS;
		destroyViewports();
		mCameraManager->setCameraMode(mode);
		createOculusViewports();

	}

}

bool GameWindow::keyPressed(const OIS::KeyEvent &arg){

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
