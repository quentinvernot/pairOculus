#include "SensorFusionDevice.hpp"

SensorFusionDevice::SensorFusionDevice():
	mLast(Ogre::Vector3::ZERO),
	mListener(0)
{

	mManager = *OVR::DeviceManager::Create();
	mHMD = *mManager->EnumerateDevices<OVR::HMDDevice>().CreateDevice();
	mSensorFusion = new OVR::SensorFusion();

	if(mHMD){

		mSensor = *mHMD->GetSensor();
		if(mSensor){
			mSensorFusion->AttachToSensor(mSensor);
			mSensorFusion->SetPredictionEnabled(true);
		}

	}

}

SensorFusionDevice::~SensorFusionDevice(){

	mSensor.Clear();
	mHMD.Clear();
	mManager.Clear();
	delete mSensorFusion;

}

void SensorFusionDevice::setEventCallback(SensorFusionListener *listener){
	mListener = listener;
}

#include <iostream>
void SensorFusionDevice::capture(){

	if(mSensor){

		using namespace OVR;

		float yaw = 0, pitch = 0, roll = 0;
		Quatf oriQuat = mSensorFusion->GetOrientation();
		oriQuat.GetEulerAngles<Axis_Y, Axis_X, Axis_Z>(&yaw, &pitch, &roll);
		Ogre::Vector3 current(yaw, pitch, roll);
		std::cout << current.x << "\t" << current.y << "\t" << current.z << "\t" << std::endl;
		
		if(mListener)
			mListener->headMoved(current - mLast);
		
		mLast = current;
	
	}

}
