#include "LocalPlayer.hpp"

LocalPlayer::LocalPlayer(
	std::string name,
	OgreBulletDynamics::DynamicsWorld *world,
	CameraManager *cameraManager
):
	OgrePlayer(name, world),
	mCameraManager(cameraManager)
{
}

LocalPlayer::~LocalPlayer(){
}

void LocalPlayer::generateGraphics(){

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

	if(!mCameraManager){
		SceneNode *entityNode = bodyNode->createChildSceneNode();
		entityNode->attachObject(entity);
		entityNode->scale(0.1, 0.1, 0.1);
		entityNode->setPosition(0, -0.3, 0);
	}

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
	mPitchCorrection  += Ogre::Degree(-arg.state.Y.rel * 0.15f);
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

bool LocalPlayer::injectHeadMove(const Ogre::Vector3 &evt){

	mYawCorrection += Ogre::Degree(evt.x);
	mPitchCorrection  += Ogre::Degree(evt.y);
	mRollCorrection += Ogre::Degree(evt.z);

	mHadInputUseful = true;

	return true;

}

bool LocalPlayer::frameRenderingQueued(const Ogre::FrameEvent &evt){

	computeAcceleration();
	computeVelocity(evt);
	computeNodePosition(evt);

	if(mGraphicsSetUp){

		mBody->getBulletRigidBody()->proceedToTransform(
			btTransform(
				btQuaternion(Ogre::Degree(mNodeYaw + 180).valueRadians(), 0, 0),
				btVector3(mNodePositionX, mNodePositionY, mNodePositionZ)
			)
		);

		mBody->setLinearVelocity(Ogre::Vector3::ZERO);

	}

	mCameraManager->setPosition(
		Ogre::Vector3(mNodePositionX, mNodePositionY + 0.7, mNodePositionZ)
	);

	mCameraManager->yaw(mYawCorrection);
	mCameraManager->pitch(mPitchCorrection);
	mCameraManager->roll(mRollCorrection);

	resetCorrection();

	return true;

}

bool LocalPlayer::hadUsefulInput(){

	if(!mHadInputUseful)
		return false;

	mHadInputUseful = false;

	return true;

}
