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

#ifndef __INPUT_HPP
#define __INPUT_HPP

#include <set>

#include <OgreLogManager.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include "MouseMoveListener.hpp"
#include "MousePressListener.hpp"
#include "MouseReleaseListener.hpp"
#include "KeyboardPressListener.hpp"
#include "KeyboardReleaseListener.hpp"

#include "SensorFusionDevice.hpp"
#include "SensorFusionListener.hpp"

/** Class managing the Game's inputs.
 *  So far, this manages the following devices :
 *  	- The mouse (move, button down, button up)
 *  	- The keyboard (key down, key up)
 *  	- The Oculus Rift 'Sensor Fusion' (head move)
 * 
 *  It also listens for events regarding the Game's window.
 */
class Input :
	public Ogre::WindowEventListener,
	public OIS::MouseListener,
	public OIS::KeyListener,
	public SensorFusionListener
{

	public:
		//Methods
		/// Constructor.
		Input(Ogre::RenderWindow *window);
		/// Destructor.
		~Input();

		/// Captures the current inputs and sends callbacks if they changed.
		void capture();

		/// Adds a MouseMoveListener.
		void addMouseMoveListener(MouseMoveListener *listener);
		/// Removes a MouseMoveListener.
		void removeMouseMoveListener(MouseMoveListener *listener);
		/// Adds a MousePressListener.
		void addMousePressListener(MousePressListener *listener);
		/// Removes a MousePressListener.
		void removeMousePressListener(MousePressListener *listener);
		/// Adds a MouseReleaseListener.
		void addMouseReleaseListener(MouseReleaseListener *listener);
		/// Removes a MouseReleaseListener.
		void removeMouseReleaseListener(MouseReleaseListener *listener);

		/// Adds a KeyboardPressListener.
		void addKeyboardPressListener(KeyboardPressListener *listener);
		/// Removes a KeyboardPressListener.
		void removeKeyboardPressListener(KeyboardPressListener *listener);
		/// Adds a KeyboardReleaseListener.
		void addKeyboardReleaseListener(KeyboardReleaseListener *listener);
		/// Removes a KeyboardReleaseListener.
		void removeKeyboardReleaseListener(KeyboardReleaseListener *listener);

		/// Adds a SensorFusionListener.
		void addSensorFusionListener(SensorFusionListener *listener);
		/// Removes a SensorFusionListener.
		void removeSensorFusionListener(SensorFusionListener *listener);

		/// Asks the SensorFusionDevice to try to connect to the Oculus Rift.
		bool connectOculusRift();
		/// Returns whether or not the Oculus Rift is connected.
		bool hasOculusRift();

	private:
		//Methods
		/// Calls the mouse move callback function.
		bool mouseMoved(const OIS::MouseEvent &arg);
		/// Calls the mouse button press callback function.
		bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		/// Calls the mouse button release callback function.
		bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		/// Calls the keyboard key press callback function.
		bool keyPressed(const OIS::KeyEvent &arg);
		/// Calls the keyboard key release callback function.
		bool keyReleased(const OIS::KeyEvent &arg);
		/// Calls the sensor fusion head move callback function.
		bool headMoved(const Ogre::Vector3 &evt);
	
		//Attributes
		/// The Game's window.
		Ogre::RenderWindow *mWindow;
		/// OIS input manager.
		OIS::InputManager *mInputManager;

		/// The mouse device.
		OIS::Mouse *mMouse;
		/// The keyboard device.
		OIS::Keyboard *mKeyboard;
		/// The sensor fusion device.
		SensorFusionDevice *mSensorFusionDevice;

		/// List of all the registered MouseMoveListeners.
		std::set<MouseMoveListener *> mMouseMoveListeners;
		/// List of all the registered MousePressListener.
		std::set<MousePressListener *> mMousePressListeners;
		/// List of all the registered MouseReleaseListener.
		std::set<MouseReleaseListener *> mMouseReleaseListeners;
		/// List of all the registered KeyboardPressListener.
		std::set<KeyboardPressListener *> mKeyboardPressListeners;
		/// List of all the registered KeyboardReleaseListener.
		std::set<KeyboardReleaseListener *> mKeyboardReleaseListeners;
		/// List of all the registered SensorFusionListener.
		std::set<SensorFusionListener *> mSensorFusionListeners;

};

#endif //__INPUT_HPP
