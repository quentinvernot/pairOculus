#ifndef __INPUT_H
#define __INPUT_H

#include <boost/function.hpp>

#include <OgreLogManager.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include "SensorFusionDevice.hpp"
#include "SensorFusionListener.hpp"

class Input :
	public Ogre::WindowEventListener,
	public OIS::MouseListener,
	public OIS::KeyListener,
	public SensorFusionListener
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
		void setSensorFusionListener(
			boost::function<bool (const Ogre::Vector3 &evt)> callbackHeadMoved
		);

		bool connectOculusRift();
		bool hasOculusRift();

	private:
		//Method
		bool mouseMoved(const OIS::MouseEvent &arg);
		bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		bool keyPressed(const OIS::KeyEvent &arg);
		bool keyReleased(const OIS::KeyEvent &arg);
		bool headMoved(const Ogre::Vector3 &evt);
	
		//Arguments
		Ogre::RenderWindow *mWindow;
		OIS::InputManager *mInputManager;

		OIS::Mouse *mMouse;
		boost::function<bool (const OIS::MouseEvent&)> mCallbackMouseMoved;
		boost::function<
			bool (const OIS::MouseEvent&, OIS::MouseButtonID)
		> mCallbackMousePressed;
		boost::function<
			bool (const OIS::MouseEvent&, OIS::MouseButtonID)
		> mCallbackMouseReleased;

		OIS::Keyboard *mKeyboard;
		boost::function<bool (const OIS::KeyEvent&)> mCallbackKeyPressed;
		boost::function<bool (const OIS::KeyEvent&)> mCallbackKeyReleased;

		SensorFusionDevice *mSensorFusionDevice;
		boost::function<bool (const  Ogre::Vector3 &evt)> mCallbackHeadMoved;

};

#endif //__INPUT_H
