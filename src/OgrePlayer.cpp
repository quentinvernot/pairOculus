#include "OgrePlayer.hpp"

OgrePlayer::OgrePlayer(
	std::string name,
	OgreBulletDynamics::DynamicsWorld *world
):
	Player(name),
	mWorld(world),
	mBody(0),
	mAccelForward(0),
	mAccelBack(0),
	mAccelLeft(0),
	mAccelRight(0),
	mAccelUp(0),
	mAccelDown(0),
	mGraphicsSetUp(false),
	mHadInputUseful(false),
	mYawCorrection(0),
	mPitchCorrection(0),
	mRollCorrection(0),
	mPositionCorrection(Ogre::Vector3::ZERO),
	mOrientationCorrection(Ogre::Quaternion::ZERO)
{
	mTopSpeed = 10;
}

void OgrePlayer::injectPlayerInput(NetworkMessage::PlayerInput *message){

	mYawCorrection += Ogre::Degree(message->getNodeYaw() - mNodeYaw);
	mPitchCorrection += Ogre::Degree(message->getNodePitch() - mNodePitch);
	mRollCorrection += Ogre::Degree(message->getNodeRoll() - mNodeRoll);

	mPositionCorrection.x += message->getNodePositionX() - mNodePositionX;
	mPositionCorrection.y += message->getNodePositionY() - mNodePositionY;
	mPositionCorrection.z += message->getNodePositionZ() - mNodePositionZ;

	mGoingForward = message->getGoingForward();
	mGoingBack = message->getGoingBack();
	mGoingLeft = message->getGoingLeft();
	mGoingRight = message->getGoingRight();
	mGoingUp = message->getGoingUp();
	mGoingDown = message->getGoingDown();

}

Ogre::Vector3 OgrePlayer::getForwardDirection(){
	using namespace Ogre;
	return Quaternion(Degree(mNodeYaw), Vector3::UNIT_Y) * Vector3::UNIT_Z * -1;
}

Ogre::Vector3 OgrePlayer::getUpDirection(){
	return Ogre::Vector3::UNIT_Y;
}

Ogre::Vector3 OgrePlayer::getRightDirection(){
	using namespace Ogre;
	return Quaternion(Degree(mNodeYaw), Vector3::UNIT_Y) * Vector3::UNIT_X;
}
