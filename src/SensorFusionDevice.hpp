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

#ifndef __SENSORFUSIONDEVICE_HPP
#define __SENSORFUSIONDEVICE_HPP

#include "SensorFusionListener.hpp"
#include <OVR.h>

/// A sensor fusion device.
class SensorFusionDevice{

	public:
		//Methods
		/// Constructor.
		SensorFusionDevice();
		/// Destructor.
		~SensorFusionDevice();

		/// Connects to the Oculus Rift.
		bool connect();
		/// Captures the current inputs and calls the listener when necessery.
		void capture();
		/// Sets the SensorFusionListener.
		void setEventCallback(SensorFusionListener *listener);
		/// Returns whether or not the Oculus Rift is connected.
		bool hasOculusRift();

	private:
		//Attributes
		/// Last recorded angles.
		Ogre::Vector3 mLast;
		/// The listener.
		SensorFusionListener *mListener;
		/// The OVR device manager.
		OVR::Ptr<OVR::DeviceManager> mManager;
		/// The OVR HMD device.
		OVR::Ptr<OVR::HMDDevice> mHMD;
		/// The OVR sensor.
		OVR::Ptr<OVR::SensorDevice> mSensor;
		/// The actual sensor fusion instance.
		OVR::SensorFusion *mSensorFusion;

};

#endif //__SENSORFUSIONDEVICE_HPP
