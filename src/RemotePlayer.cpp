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

	mGraphicsSetUp = true;

}

bool RemotePlayer::frameRenderingQueued(const Ogre::FrameEvent &evt){

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

	resetCorrection();

	return true;

}
