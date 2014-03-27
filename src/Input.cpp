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

#include "Input.hpp"

Input::Input(Ogre::RenderWindow *window){

	Ogre::LogManager::getSingletonPtr()->logMessage("Initializing OIS");

	mWindow = window;

	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	OIS::ParamList pl;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
	mInputManager = OIS::InputManager::createInputSystem(pl);

	mMouse = static_cast<OIS::Mouse*>(
		mInputManager->createInputObject(OIS::OISMouse, true)
	);
	mMouse->setEventCallback(this);

	mKeyboard = static_cast<OIS::Keyboard*>(
		mInputManager->createInputObject(OIS::OISKeyboard, true)
	);
	mKeyboard->setEventCallback(this);

	Ogre::LogManager::getSingletonPtr()->logMessage("OIS Initialized");
	
	Ogre::LogManager::getSingletonPtr()->logMessage("Initializing OVR");
	OVR::System::Init(OVR::Log::ConfigureDefaultLog(OVR::LogMask_All));
	
	mSensorFusionDevice = new SensorFusionDevice();
	mSensorFusionDevice->setEventCallback(this);
	
	Ogre::LogManager::getSingletonPtr()->logMessage("OVR Initialized");

}

Input::~Input(){

	Ogre::LogManager::getSingletonPtr()->logMessage("Destroying OIS");

	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);

	if(mInputManager){

		mInputManager->destroyInputObject(mMouse);
		mInputManager->destroyInputObject(mKeyboard);
		OIS::InputManager::destroyInputSystem(mInputManager);
		mInputManager = 0;

	}

	Ogre::LogManager::getSingletonPtr()->logMessage("OIS Destroyed");

}

void Input::capture(){

	mMouse->capture();
	mKeyboard->capture();
	mSensorFusionDevice->capture();

}

void Input::addMouseMoveListener(MouseMoveListener *listener){
	mMouseMoveListeners.insert(listener);
}
void Input::removeMouseMoveListener(MouseMoveListener *listener){
	mMouseMoveListeners.erase(listener);
}

void Input::addMousePressListener(MousePressListener *listener){
	mMousePressListeners.insert(listener);
}
void Input::removeMousePressListener(MousePressListener *listener){
	mMousePressListeners.erase(listener);
}

void Input::addMouseReleaseListener(MouseReleaseListener *listener){
	mMouseReleaseListeners.insert(listener);
}
void Input::removeMouseReleaseListener(MouseReleaseListener *listener){
	mMouseReleaseListeners.erase(listener);
}

void Input::addKeyboardPressListener(KeyboardPressListener *listener){
	mKeyboardPressListeners.insert(listener);
}
void Input::removeKeyboardPressListener(KeyboardPressListener *listener){
	mKeyboardPressListeners.erase(listener);
}

void Input::addKeyboardReleaseListener(KeyboardReleaseListener *listener){
	mKeyboardReleaseListeners.insert(listener);
}
void Input::removeKeyboardReleaseListener(KeyboardReleaseListener *listener){
	mKeyboardReleaseListeners.erase(listener);
}

void Input::addSensorFusionListener(SensorFusionListener *listener){
	mSensorFusionListeners.insert(listener);
}
void Input::removeSensorFusionListener(SensorFusionListener *listener){
	mSensorFusionListeners.erase(listener);
}

bool Input::connectOculusRift(){

	if(mSensorFusionDevice->hasOculusRift())
		return true;

	return mSensorFusionDevice->connect();

}
bool Input::hasOculusRift(){return mSensorFusionDevice->hasOculusRift();}

bool Input::mouseMoved(const OIS::MouseEvent &arg){

	std::set<MouseMoveListener *>::iterator it;
	for (it = mMouseMoveListeners.begin(); it != mMouseMoveListeners.end(); ++it)
		(*it)->mouseMoved(arg);

	return true;

}

bool Input::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id){

	std::set<MousePressListener *>::iterator it;
	for (it = mMousePressListeners.begin(); it != mMousePressListeners.end(); it++)
		(*it)->mousePressed(arg, id);

	return true;
}

bool Input::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){

	std::set<MouseReleaseListener *>::iterator it;
	for (it = mMouseReleaseListeners.begin(); it != mMouseReleaseListeners.end(); it++)
		(*it)->mouseReleased(arg, id);

	return true;
}

bool Input::keyPressed(const OIS::KeyEvent &arg){

	std::set<KeyboardPressListener *>::iterator it;
	for (it = mKeyboardPressListeners.begin(); it != mKeyboardPressListeners.end(); it++)
		(*it)->keyPressed(arg);
	
	return true;

}

bool Input::keyReleased(const OIS::KeyEvent &arg){

	std::set<KeyboardReleaseListener *>::iterator it;
	for (it = mKeyboardReleaseListeners.begin(); it != mKeyboardReleaseListeners.end(); it++)
		(*it)->keyReleased(arg);
	
	return true;

}

bool Input::headMoved(const Ogre::Vector3 &evt){

	std::set<SensorFusionListener *>::iterator it;
	for (it = mSensorFusionListeners.begin(); it != mSensorFusionListeners.end(); it++)
		(*it)->headMoved(evt);

	return true;

}
