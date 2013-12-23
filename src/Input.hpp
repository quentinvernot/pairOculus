#ifndef __INPUT_H
#define __INPUT_H

//#include "WindowInput.hpp"

#include <list>

#include <boost/function.hpp>

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

class Input :
	public Ogre::WindowEventListener,
	public OIS::MouseListener,
	public OIS::KeyListener
{

	public:
		//Methods
		Input(Ogre::RenderWindow *window);
		~Input();
		
		void capture();

		void setMouseListener(
			boost::function<bool (const OIS::MouseEvent&)> _callbackMouseMoved,
			boost::function<
				bool (const OIS::MouseEvent&, OIS::MouseButtonID)
			> _callbackMousePressed,
			boost::function<
				bool (const OIS::MouseEvent&, OIS::MouseButtonID)
			> _callbackMouseReleased
		);
		void setKeyboardListener(
			boost::function<bool (const OIS::KeyEvent&)> _callbackKeyPressed,
			boost::function<bool (const OIS::KeyEvent&)> _callbackKeyReleased
		);

		OIS::Mouse *getMouse();
		OIS::Keyboard *getKeyboard();

	private:
		//Method
		bool mouseMoved(const OIS::MouseEvent &arg);
		bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		bool keyPressed(const OIS::KeyEvent &arg);
		bool keyReleased(const OIS::KeyEvent &arg);
	
		//Arguments
		Ogre::RenderWindow *window;
		OIS::InputManager *inputManager;

		OIS::Mouse *mouse;
		boost::function<bool (const OIS::MouseEvent&)> callbackMouseMoved;
		boost::function<
			bool (const OIS::MouseEvent&, OIS::MouseButtonID)
		> callbackMousePressed;
		boost::function<
			bool (const OIS::MouseEvent&, OIS::MouseButtonID)
		> callbackMouseReleased;

		OIS::Keyboard *keyboard;
		boost::function<bool (const OIS::KeyEvent&)> callbackKeyPressed;
		boost::function<bool (const OIS::KeyEvent&)> callbackKeyReleased;

};

#endif //__INPUT_H
