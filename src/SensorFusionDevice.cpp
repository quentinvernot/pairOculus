#include "SensorFusionDevice.hpp"

SensorFusionDevice::SensorFusionDevice():
	mLast(Ogre::Vector3::ZERO),
	mListener(0)
{

	mManager = *OVR::DeviceManager::Create();
	mSensorFusion = new OVR::SensorFusion();
	connect();

}

SensorFusionDevice::~SensorFusionDevice(){

	mSensor.Clear();
	mHMD.Clear();
	mManager.Clear();
	delete mSensorFusion;

}

bool SensorFusionDevice::connect(){

	mHMD = *mManager->EnumerateDevices<OVR::HMDDevice>().CreateDevice();

	if(mHMD){

		mSensor = *mHMD->GetSensor();
		if(mSensor){
			mSensorFusion->AttachToSensor(mSensor);
			mSensorFusion->SetPredictionEnabled(true);
		}

	}

	return hasOculusRift();

}

void SensorFusionDevice::setEventCallback(SensorFusionListener *listener){
	mListener = listener;
}

void SensorFusionDevice::capture(){

	if(mSensor){

		using namespace OVR;

		float yaw = 0, pitch = 0, roll = 0;
		Quatf oriQuat = mSensorFusion->GetOrientation();
		oriQuat.GetEulerAngles<Axis_Y, Axis_X, Axis_Z>(&yaw, &pitch, &roll);
		Ogre::Vector3 current(yaw, pitch, roll);

		if(mListener)
			mListener->headMoved(current - mLast);
		
		mLast = current;
	
	}

}

bool SensorFusionDevice::hasOculusRift(){return mSensor != 0;}
