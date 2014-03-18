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

#ifndef __SIMPLECAMERA_HPP
#define __SIMPLECAMERA_HPP

#include <OgreCamera.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>

/// A wrapper to control the standard Ogre::Camera.
class SimpleCamera{

	public:
		/// Constructor.
		SimpleCamera(Ogre::Camera *cam);
		/// Destructor.
		~SimpleCamera();

		/// Moves the camera.
		void move(Ogre::Vector3 vec);
		/// Angles the camera around the Y axis.
		void yaw(Ogre::Radian ang);
		/// Angles the camera around the X axis.
		void pitch(Ogre::Radian ang);
		/// Angles the camera around the Z axis.
		void roll(Ogre::Radian ang);

		/// Sets the camera's position.
		void setPosition(Ogre::Vector3 pos);
		/// Returns the camera's orientation.
		Ogre::Quaternion getOrientation();
		/// Sets the camera's orientation.
		void setOrientation(Ogre::Quaternion ori);
		/// Orients the camera toward the specified point.
		void lookAt(Ogre::Vector3 vec);

		/// Sets the camera to be used.
		void setCamera(Ogre::Camera *cam);
		/// Returns the current camera.
		Ogre::Camera *getCamera();

	private:
		/// The camera.
		Ogre::Camera *mCamera;

};

#endif // __SIMPLECAMERA_HPP
