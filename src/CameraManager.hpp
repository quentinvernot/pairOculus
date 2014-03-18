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

#ifndef __CAMERAMANAGER_HPP
#define __CAMERAMANAGER_HPP

#include <OgreCamera.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>

#include "SimpleCamera.hpp"
#include "OculusCamera.hpp"

/// Types of rendering modes.
enum ViewMode {
	SIMPLE,	/// Single camera.
	OCULUS	/// Stereo cameras for the Oculus Rift.
};

/** Handles the cameras (coordinates and mode).
 *  Can switch between a simple camera and a stereo camera.
 */
class CameraManager{

	public:
		//Methods
		/// Constructor.
		CameraManager(Ogre::SceneManager *sceneMgr);
		/// Destructor.
		~CameraManager();

		/// Moves the controlled camera.
		void move(const Ogre::Vector3 vec);
		/// Angles the controlled camera around the Y axis.
		void yaw(Ogre::Radian ang);
		/// Angles the controlled camera around the X axis.
		void pitch(Ogre::Radian ang);
		/// Angles the controlled camera around the Z axis.
		void roll(Ogre::Radian ang);

		/// Sets the controlled camera's position.
		void setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z);
		/// Sets the controlled camera's position.
		void setPosition(Ogre::Vector3 pos);
		/// Gets the controlled camera's orientation.
		Ogre::Quaternion getOrientation();
		/// Sets the controlled camera's orientation.
		void setOrientation(Ogre::Quaternion ori);
		/// Sets the controlled camera's to look at the specified point.
		void lookAt(Ogre::Vector3 vec);

		/// Increases the space between the cameras in OCULUS mode.
		void increaseIPD();
		/// Decreases the space between the cameras in OCULUS mode.
		void decreaseIPD();

		/// Returns the forward direction vector.
		Ogre::Vector3 getDirection();
		/// Returns the up direction vector.
		Ogre::Vector3 getUp();
		/// Returns the right direction vector.
		Ogre::Vector3 getRight();

		/** Returns the forward direction vector on a flat plane.
		 *  Returns the vector representing the direction towards which the 
		 *  player is looking, projected on the x0z plane and normalized.
		 */
		Ogre::Vector3 getForwardDirection();
		/// Returns the up direction vector on a flat plane (always the Y axis).
		Ogre::Vector3 getUpDirection();
		/** Returns the right direction vector on a flat plane.
		 *  Returns the vector representing the player's right, projected on the
		 *  x0z plane and normalized.
		 */
		 Ogre::Vector3 getRightDirection();

		/// Switches the cameras between SIMPLE and OCULUS.
		void switchCameraMode();
		/// Returns the camera mode.
		ViewMode getCameraMode();
		/// Sets the camera mode.
		void setCameraMode(ViewMode mode);

		/// Returns the camera when in SIMPLE mode.
		Ogre::Camera *getCamera();
		/// Returns the left camera when in OCULUS mode.
		Ogre::Camera *getOculusCameraLeft();
		/// Returns the right camera when in OCULUS mode.
		Ogre::Camera *getOculusCameraRight();

	private:
		//Methods
		/// Creates the camera in SIMPLE mode.
		void createSimpleCamera();
		/// Creates the cameras in OCULUS mode.
		void createOculusCamera();
		/// Destroys all cameras.
		void destroyCameras();

		//Arguments
		/// The game's SceneManager.
		Ogre::SceneManager *mSceneMgr;
		/// The current ViewMode.
		ViewMode mCameraMode;

		SimpleCamera *mSimpleCamera;
		OculusCamera *mOculusCamera;

		/// The reference yaw.
		Ogre::Radian mNodeYaw;
		/// The reference pitch.
		Ogre::Radian mNodePitch;
		/// The reference roll.
		Ogre::Radian mNodeRoll;
		/// The reference position.
		Ogre::Vector3 mNodePosition;

};

#endif //__CAMERAMANAGER_HPP
