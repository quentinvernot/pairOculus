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

#ifndef __OCULUSCAMERA_HPP
#define __OCULUSCAMERA_HPP

#include <OVR.h>

#include <OgreCamera.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>

/** Allows to control 2 cameras in tandem for the Oculus Rift.
 *  Both cameras have an offset from their original position, to simulate the
 *  position of the eyes and the movement of the head.
 */
class OculusCamera{

	public:
		/// Constructor.
		OculusCamera(Ogre::Camera *leftCam, Ogre::Camera *rightCam);
		/// Destructor.
		~OculusCamera();

		/// Moves the cameras.
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

		/// Increases the space between the cameras.
		void increaseIPD();
		/// Decreases the space between the cameras.
		void decreaseIPD();

		/// Sets the cameras to be used.
		void setCameras(Ogre::Camera *leftCam, Ogre::Camera *rightCam);
		/// Sets the left camera.
		void setLeftCamera(Ogre::Camera *cam);
		/// Sets the right camera.
		void setRightCamera(Ogre::Camera *cam);
		/// Returns the left camera.
		Ogre::Camera *getLeftCamera();
		/// Returns the right camera.
		Ogre::Camera *getRightCamera();

	private:
		//Methods
		/// Removes the cameras' offsets.
		void removeOffset();
		/// Applies the cameras' offsets.
		void applyOffset();

		//Attributes
		/// Interpupillary Distance, the distance between the cameras.
		Ogre::Real mIPD;
		/// The left camera.
		Ogre::Camera *mLeftCamera;
		/// The right camera.
		Ogre::Camera *mRightCamera;

		/// The reference position.
		Ogre::Vector3 mNodePosition;
		/// The offset of the cameras.
		Ogre::Vector3 mBaseOffset;
		/// The the corrected offset after a rotation.
		Ogre::Vector3 mCameraOffset;

		/// Oculus Rift config.
		OVR::Util::Render::StereoConfig *mStereoConfig;

};

#endif // __OCULUSCAMERA_HPP
