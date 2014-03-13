#include "RemotePlayer.hpp"

RemotePlayer::RemotePlayer(
	std::string name,
	OgreBulletDynamics::DynamicsWorld *world
):
	OgrePlayer(name, world)
{
}

RemotePlayer::~RemotePlayer(){
}

void RemotePlayer::generateGraphics(){

	if(mGraphicsSetUp)
		return;

	using namespace OgreBulletCollisions;
	using namespace Ogre;

	Entity *entity = mWorld->getSceneManager()->createEntity("bomberman.mesh");
	entity->setCastShadows(true);
	AxisAlignedBox boundingB = entity->getBoundingBox();
	Vector3 size = boundingB.getSize();
	size /= 20;
	SceneNode *bodyNode = mWorld->getSceneManager()->getRootSceneNode()->createChildSceneNode();

	SceneNode *entityNode = bodyNode->createChildSceneNode();
	entityNode->attachObject(entity);
	entityNode->scale(0.1, 0.1, 0.1);
	entityNode->setPosition(0, -0.3, 0);

	BoxCollisionShape *boxShape = new BoxCollisionShape(size);
	mBody = new OgreBulletDynamics::RigidBody(mNickname + "Box", mWorld);

	Vector3 position(
		mNodePositionX,
		mNodePositionY,
		mNodePositionZ
	);

	mBody->setShape(
		bodyNode,
		boxShape,
		0.6f,
		0.0f,
		50.0f,
		position
	);

	mBody->disableDeactivation();
	mBody->getBulletRigidBody()->setAngularFactor(btVector3(0, 0, 0));
	mBody->getBulletRigidBody()->setGravity(btVector3(0, 0, 0));

	mPlayerAnimationState = new PlayerAnimation(mWorld->getSceneManager(), entity);

	mGraphicsSetUp = true;

}

bool RemotePlayer::frameRenderingQueued(const Ogre::FrameEvent &evt){
	Ogre::LogManager::getSingletonPtr()->logMessage("REMOTEPLAYER frameRenderingQueued");

	if(mGoingForward && mAccelForward < mTopAccel) mAccelForward += 1;
	else if(!mGoingForward && mAccelForward > 0) mAccelForward -= 1;

	if(mGoingLeft && mAccelLeft < mTopAccel) mAccelLeft += 1;
	else if(!mGoingLeft && mAccelLeft > 0) mAccelLeft -= 1;

	if(mGoingBack && mAccelBack < mTopAccel) mAccelBack += 1;
	else if(!mGoingBack && mAccelBack > 0) mAccelBack -= 1;

	if(mGoingRight && mAccelRight < mTopAccel) mAccelRight += 1;
	else if(!mGoingRight && mAccelRight > 0) mAccelRight -= 1;

	if(mGoingUp && mAccelUp < mTopAccel) mAccelUp += 1;
	else if(!mGoingUp && mAccelUp > 0) mAccelUp -= 1;

	if(mGoingDown && mAccelDown < mTopAccel) mAccelDown += 1;
	else if(!mGoingDown && mAccelDown > 0) mAccelDown -= 1;

	Ogre::Vector3 velocity = Ogre::Vector3::ZERO;

	if(mGoingForward || mAccelForward) {
		velocity += mAccelForward * getForwardDirection() / mTopAccel;
//		mPlayerAnimationState->doRunAnimation();
	}
	if(mGoingLeft || mAccelLeft) {
		velocity -= mAccelLeft * getRightDirection() / mTopAccel;
//		mPlayerAnimationState->doRunAnimation();
	}
	if(mGoingBack || mAccelBack) {
		velocity -= mAccelBack * getForwardDirection() / mTopAccel;
//		mPlayerAnimationState->doRunAnimation();
	}
	if(mGoingRight || mAccelRight) {
		velocity += mAccelRight * getRightDirection() / mTopAccel;
//		mPlayerAnimationState->doRunAnimation();
	}

	if (mGraphicsSetUp) {
		if (velocity != Ogre::Vector3::ZERO)
			mPlayerAnimationState->doRunAnimation();
		else {
			Ogre::LogManager::getSingletonPtr()->logMessage("Before doIdleAnimation()");
			mPlayerAnimationState->doIdleAnimation();
			Ogre::LogManager::getSingletonPtr()->logMessage("After doIdleAnimation()");
		}
	}

	if(mGoingUp || mAccelUp)
		velocity += mAccelUp * getUpDirection()  / mTopAccel;
	if(mGoingDown || mAccelDown)
		velocity -= mAccelDown * getUpDirection()  / mTopAccel;

	if(mGraphicsSetUp){
		mNodePositionX = mBody->getSceneNode()->getPosition().x;
		mNodePositionY = mBody->getSceneNode()->getPosition().y;
		mNodePositionZ = mBody->getSceneNode()->getPosition().z;
	}

	mNodePositionX += velocity.x * evt.timeSinceLastFrame * mTopSpeed;
	mNodePositionY += velocity.y * evt.timeSinceLastFrame * mTopSpeed;
	mNodePositionZ += velocity.z * evt.timeSinceLastFrame * mTopSpeed;

	mNodeYaw += mYawCorrection.valueDegrees();
	mNodePitch += mPitchCorrection.valueDegrees();
	mNodeRoll += mRollCorrection.valueDegrees();

	mNodePositionX += mPositionCorrection.x;
	mNodePositionY += mPositionCorrection.y;
	mNodePositionZ += mPositionCorrection.z;

	if(mGraphicsSetUp){

		mBody->getBulletRigidBody()->proceedToTransform(
			btTransform(
				btQuaternion(Ogre::Degree(mNodeYaw + 180).valueRadians(), 0, 0),
				btVector3(mNodePositionX, mNodePositionY, mNodePositionZ)
			)
		);

		mBody->setLinearVelocity(Ogre::Vector3::ZERO);

		Ogre::LogManager::getSingletonPtr()->logMessage("Before addTime()");
		mPlayerAnimationState->getPlayerAnimationState()->addTime(evt.timeSinceLastFrame);
		Ogre::LogManager::getSingletonPtr()->logMessage("After addTime()");
	}

	mYawCorrection = 0;
	mPitchCorrection = 0;
	mRollCorrection = 0;
	mPositionCorrection = Ogre::Vector3::ZERO;

	return true;

}
