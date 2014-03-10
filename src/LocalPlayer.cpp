#include "LocalPlayer.hpp"

LocalPlayer::LocalPlayer(
	std::string name,
	Ogre::SceneManager *sceneMgr,
	OgreBulletDynamics::DynamicsWorld *world,
	CameraManager *cameraManager
):
	Player(name),
	mSceneMgr(sceneMgr),
	mWorld(world),
	mBody(0),
	mCameraManager(cameraManager),
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
	mTopSpeed = 100;
	//mNodePositionX = 100;
	//mNodePositionY = 100;
	//mNodePositionZ = 100;
}

LocalPlayer::~LocalPlayer(){
}

void LocalPlayer::generateGraphics(){

	using namespace OgreBulletCollisions;
	using namespace Ogre;

	Entity *entity = mSceneMgr->createEntity("bomberman.mesh");
	entity->setCastShadows(true);
	AxisAlignedBox boundingB = entity->getBoundingBox();
	Vector3 size = boundingB.getSize();
	size /= 2;
	SceneNode *bodyNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();

	if(!mCameraManager){
		SceneNode *entityNode = bodyNode->createChildSceneNode();
		entityNode->attachObject(entity);
		entityNode->setPosition(0, -3, 0);
	}

	BoxCollisionShape *boxShape = new BoxCollisionShape(size);
	mBody = new OgreBulletDynamics::RigidBody(mNickname + "box", mWorld);

	Vector3 position(
		mNodePositionX,
		mNodePositionY,
		mNodePositionZ
	);

	mBody->setShape(
		bodyNode,
		boxShape,
		0.0f,
		0.0f,
		50.0f,
		position
	);

	mBody->disableDeactivation();
	mBody->getBulletRigidBody()->setAngularFactor(btVector3(0, 0, 0));
	mBody->getBulletRigidBody()->setGravity(btVector3(0, 0, 0));

	mGraphicsSetUp = true;

}

void LocalPlayer::lookAt(Ogre::Vector3 vec){

	if(mCameraManager){

		mCameraManager->lookAt(vec);

		mNodeYaw = mCameraManager->getOrientation().getYaw().valueDegrees();
		mNodePitch = mCameraManager->getOrientation().getPitch().valueDegrees();
		mNodeRoll = mCameraManager->getOrientation().getRoll().valueDegrees();

	}

}

bool LocalPlayer::injectMouseMove(const OIS::MouseEvent &arg){

	mYawCorrection += Ogre::Degree(-arg.state.X.rel * 0.15f);
	mPitchCorrection  += Ogre::Degree(-arg.state.Y.rel * 0.15f);;
	//mRollCorrection += Ogre::Degree(-arg.state.Z.rel * 0.15f);

	mHadInputUseful = true;

	return true;

}

bool LocalPlayer::injectMouseDown(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
	return true;
}

bool LocalPlayer::injectMouseUp(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
	return true;
}

bool LocalPlayer::injectKeyDown(const OIS::KeyEvent &arg){

	if (arg.key == OIS::KC_Z || arg.key == OIS::KC_UP)
		mGoingForward = true;
	else if (arg.key == OIS::KC_S || arg.key == OIS::KC_DOWN)
		mGoingBack = true;
	else if (arg.key == OIS::KC_Q || arg.key == OIS::KC_LEFT)
		mGoingLeft = true;
	else if (arg.key == OIS::KC_D || arg.key == OIS::KC_RIGHT)
		mGoingRight = true;
	else if (arg.key == OIS::KC_PGUP)
		mGoingUp = true;
	else if (arg.key == OIS::KC_PGDOWN)
		mGoingDown = true;
	else if (arg.key == OIS::KC_LSHIFT)
		mFastMove = true;

	if(
		arg.key == OIS::KC_Z ||
		arg.key == OIS::KC_UP ||
		arg.key == OIS::KC_S ||
		arg.key == OIS::KC_DOWN ||
		arg.key == OIS::KC_Q ||
		arg.key == OIS::KC_LEFT ||
		arg.key == OIS::KC_D ||
		arg.key == OIS::KC_RIGHT ||
		arg.key == OIS::KC_PGUP ||
		arg.key == OIS::KC_PGDOWN
	)
		mHadInputUseful = true;

	return true;

}

bool LocalPlayer::injectKeyUp(const OIS::KeyEvent &arg){

	if (arg.key == OIS::KC_Z || arg.key == OIS::KC_UP)
		mGoingForward = false;
	else if (arg.key == OIS::KC_S || arg.key == OIS::KC_DOWN)
		mGoingBack = false;
	else if (arg.key == OIS::KC_Q || arg.key == OIS::KC_LEFT)
		mGoingLeft = false;
	else if (arg.key == OIS::KC_D || arg.key == OIS::KC_RIGHT)
		mGoingRight = false;
	else if (arg.key == OIS::KC_PGUP)
		mGoingUp = false;
	else if (arg.key == OIS::KC_PGDOWN)
		mGoingDown = false;
	else if (arg.key == OIS::KC_LSHIFT)
		mFastMove = false;

	if(
		arg.key == OIS::KC_Z ||
		arg.key == OIS::KC_UP ||
		arg.key == OIS::KC_S ||
		arg.key == OIS::KC_DOWN ||
		arg.key == OIS::KC_Q ||
		arg.key == OIS::KC_LEFT ||
		arg.key == OIS::KC_D ||
		arg.key == OIS::KC_RIGHT ||
		arg.key == OIS::KC_PGUP ||
		arg.key == OIS::KC_PGDOWN
	)
		mHadInputUseful = true;

	return true;

}

void LocalPlayer::injectPlayerInput(NetworkMessage::PlayerInput *message){

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

bool LocalPlayer::frameRenderingQueued(const Ogre::FrameEvent &evt){

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

	if(mGoingForward || mAccelForward)
		velocity += mAccelForward * getForwardDirection() / mTopAccel;
	if(mGoingLeft || mAccelLeft)
		velocity -= mAccelLeft * getRightDirection() / mTopAccel;
	if(mGoingBack || mAccelBack)
		velocity -= mAccelBack * getForwardDirection() / mTopAccel;
	if(mGoingRight || mAccelRight)
		velocity += mAccelRight * getRightDirection() / mTopAccel;

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

	}

	if(mCameraManager){

		mCameraManager->setPosition(
			Ogre::Vector3(mNodePositionX, mNodePositionY + 7, mNodePositionZ)
		);

		mCameraManager->yaw(mYawCorrection);
		mCameraManager->pitch(mPitchCorrection);
		mCameraManager->roll(mRollCorrection);
		
	}

	mYawCorrection = 0;
	mPitchCorrection = 0;
	mRollCorrection = 0;
	mPositionCorrection = Ogre::Vector3::ZERO;

	return true;

}

bool LocalPlayer::hadUsefulInput(){

	if(!mHadInputUseful)
		return false;

	mHadInputUseful = false;

	return true;

}

Ogre::Vector3 LocalPlayer::getForwardDirection(){
	using namespace Ogre;
	return Quaternion(Degree(mNodeYaw), Vector3::UNIT_Y) * Vector3::UNIT_Z * -1;
}

Ogre::Vector3 LocalPlayer::getUpDirection(){
	return Ogre::Vector3::UNIT_Y;
}

Ogre::Vector3 LocalPlayer::getRightDirection(){
	using namespace Ogre;
	return Quaternion(Degree(mNodeYaw), Vector3::UNIT_Y) * Vector3::UNIT_X;
}
