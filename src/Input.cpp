#include "Input.hpp"

Input::Input(Ogre::RenderWindow *_window){

	Ogre::LogManager::getSingletonPtr()->logMessage("Initializing OIS");

	window = _window;

	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	window->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	OIS::ParamList pl;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
	inputManager = OIS::InputManager::createInputSystem(pl);

	Ogre::LogManager::getSingletonPtr()->logMessage("OIS Initialized");

}

Input::~Input(){

	Ogre::LogManager::getSingletonPtr()->logMessage("Destroying OIS");

	Ogre::WindowEventUtilities::removeWindowEventListener(window, this);

	if(inputManager){

		inputManager->destroyInputObject(mouse);
		inputManager->destroyInputObject(keyboard);
		OIS::InputManager::destroyInputSystem(inputManager);
		inputManager = 0;

	}

	Ogre::LogManager::getSingletonPtr()->logMessage("OIS Destroyed");

}

void Input::capture(){

	mouse->capture();
	keyboard->capture();

}

void Input::setMouseListener(
	boost::function<bool (const OIS::MouseEvent&)> _callbackMouseMoved,
	boost::function<
		bool (const OIS::MouseEvent&, OIS::MouseButtonID)
	> _callbackMousePressed,
	boost::function<
		bool (const OIS::MouseEvent&, OIS::MouseButtonID)
	> _callbackMouseReleased
){

	mouse = static_cast<OIS::Mouse*>(
		inputManager->createInputObject(OIS::OISMouse, true)
	);
	callbackMouseMoved = _callbackMouseMoved;
	callbackMousePressed = _callbackMousePressed;
	callbackMouseReleased = _callbackMouseReleased;
	mouse->setEventCallback(this);

}

void Input::setKeyboardListener(
	boost::function<bool (const OIS::KeyEvent&)> _callbackKeyPressed,
	boost::function<bool (const OIS::KeyEvent&)> _callbackKeyReleased
){

	keyboard = static_cast<OIS::Keyboard*>(
		inputManager->createInputObject(OIS::OISKeyboard, true)
	);
	callbackKeyPressed = _callbackKeyPressed;
	callbackKeyReleased = _callbackKeyReleased;
	keyboard->setEventCallback(this);

}

bool Input::mouseMoved(const OIS::MouseEvent &arg){

	if(callbackMouseMoved == NULL)
		return true;

	return callbackMouseMoved(arg);

}

bool Input::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id){

	if(callbackMousePressed == NULL)
		return true;

	return callbackMousePressed(arg, id);
}

bool Input::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){

	if(callbackMouseReleased == NULL)
		return true;

	return callbackMouseReleased(arg, id);
}

bool Input::keyPressed(const OIS::KeyEvent &arg){

	if(callbackKeyPressed == NULL)
		return true;
	return callbackKeyPressed(arg);

}

bool Input::keyReleased(const OIS::KeyEvent &arg){

	if(callbackKeyReleased == NULL)
		return true;
	return callbackKeyReleased(arg);

}

OIS::Mouse *Input::getMouse(){return mouse;}
OIS::Keyboard *Input::getKeyboard(){return keyboard;}
