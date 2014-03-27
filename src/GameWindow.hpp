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

#ifndef __GAMEWINDOW_HPP
#define __GAMEWINDOW_HPP

#include "CameraManager.hpp"
#include "KeyboardPressListener.hpp"

#include <OVR.h>

#include <OgreCamera.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreCompositorManager.h>
#include <OgreCompositionTargetPass.h>
#include <OgreCompositionPass.h>

#include <OISEvents.h>
#include <OISKeyboard.h>

/// The game's window.
class GameWindow : public KeyboardPressListener{

	public:
		//Methods
		/// Constructor.
		GameWindow(
			CameraManager *cameraManager,
			Ogre::RenderWindow *ogreWindow
		);
		/// Destructor.
		~GameWindow();
		/// Switches the view between SIMPLE and OCULUS.
		void switchViewMode();
		/// Sets the view mode.
		void setViewMode(ViewMode mode);
		/// Returns the render window.
		Ogre::RenderWindow *getWindow();

		/// Treats the keyboard inputs.
		bool keyPressed(const OIS::KeyEvent &arg);

	private:
		//Methods
		/// Creates the vieport for a simple/normal view.
		void createSimpleViewport();
		/// Creates the viewports for the Oculus Rift display.
		void createOculusViewports();
		/// Destroys all viewports.
		void destroyViewports();

		//Attributes
		/// The game's CameraManager.
		CameraManager *mCameraManager;
		/// The game's RenderWindow.
		Ogre::RenderWindow *mOgreWindow;
		/// The current ViewMode.
		ViewMode mViewMode;

		/// The Oculus Rift's config.
		OVR::Util::Render::StereoConfig *mStereoConfig;

};

#endif //__GAMEWINDOW_HPP
