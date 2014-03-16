#include "RemotePlayer.hpp"

RemotePlayer::RemotePlayer(
	std::string name,
	OgreBulletDynamics::DynamicsWorld *world,
	BombManager *bombManager
):
	OgrePlayer(name, world, bombManager),
	mBombCooldown(0)
{
}

RemotePlayer::~RemotePlayer(){
}

void RemotePlayer::generateGraphics(){

	if(mGraphicsSetUp)
		return;

	using namespace Ogre;

	mEntity = mWorld->getSceneManager()->createEntity("bomberman.mesh");
	mEntity->setCastShadows(true);
	Vector3 size = computeHitboxSize();

	SceneNode *bodyNode = mWorld->getSceneManager()->getRootSceneNode()->createChildSceneNode();

	SceneNode *entityNode = bodyNode->createChildSceneNode();
	entityNode->attachObject(mEntity);
	entityNode->scale(0.1, 0.1, 0.1);
	entityNode->setPosition(0, -0.3, 0);

	generateHitbox(size, bodyNode);

	mPlayerAnimationState = new PlayerAnimation(mWorld->getSceneManager(), mEntity);

	mGraphicsSetUp = true;

}

bool RemotePlayer::frameRenderingQueued(const Ogre::FrameEvent &evt){

	computeAcceleration();
	computeVelocity(evt);
	computeNodePosition(evt);

	mBombCooldown -= evt.timeSinceLastFrame;

	if(mPuttingBomb && mBombCooldown <= 0) {
		mBombManager->add(mNickname + "bomb", Ogre::Vector3(getX() ,getY() ,getZ()) + getForwardDirection());
		mBombCooldown = 1;
	}

	if(mGraphicsSetUp){
		if (mVelocity.x != 0 && mVelocity.z != 0)
			mPlayerAnimationState->doRunAnimation();
		else {
			mPlayerAnimationState->doIdleAnimation();
		}

		mBody->getBulletRigidBody()->proceedToTransform(
			btTransform(
				btQuaternion(Ogre::Degree(mYaw + 180).valueRadians(), 0, 0),
				btVector3(mX, mY, mZ)
			)
		);

		mBody->setLinearVelocity(Ogre::Vector3::ZERO);

		mPlayerAnimationState->getPlayerAnimationState()->addTime(evt.timeSinceLastFrame);
	}

	resetCorrection();

	return true;

}

void RemotePlayer::win(){

	if(mIsDead)
		return;

	mHasWon = true;

	mGoingForward = false;
	mGoingBack = false;
	mGoingLeft = false;
	mGoingRight = false;
	mPuttingBomb = false;
	mGoingUp = false;
	mGoingDown = false;
	mFastMove = false;

	mX = mStartingX;
	mY = mStartingY + 10;
	mZ = mStartingZ;

	mWasTeleported = true;

}

void RemotePlayer::die(){

	if(mHasWon)
		return;

	mIsDead = true;

	mGoingForward = false;
	mGoingBack = false;
	mGoingLeft = false;
	mGoingRight = false;
	mPuttingBomb = false;
	mGoingUp = false;
	mGoingDown = false;
	mFastMove = false;

	mX = mStartingX;
	mY = mStartingY + 10;
	mZ = mStartingZ;

	mWasTeleported = true;

}
