#include "Explosion.hpp"

Explosion::Explosion(
	std::string name,
	Ogre::Vector3 position,
	Ogre::Vector3 velocity,
	OgreBulletDynamics::DynamicsWorld *world
):
	mRange(6),
	mName(name),
	mPosition(position),
	mVelocity(velocity),
	mWorld(world),
	mBody(0),
	mGraphicsSetUp(false)
{
}

Explosion::~Explosion(){
	mWorld->getSceneManager()->destroyEntity(mName + "ExplosionEntity");
	delete mBody;
}

void Explosion::generateGraphics(){

	if(mGraphicsSetUp)
		return;
	
	using namespace OgreBulletCollisions;
	using namespace Ogre;

	Ogre::SceneManager *sceneMgr = mWorld->getSceneManager();
	Entity *entity = sceneMgr->createEntity(mName + "ExplosionEntity", "sphere.mesh");
	entity->setMaterialName("Examples/Smoke");
	AxisAlignedBox boundingB = entity->getBoundingBox();
	Vector3 size = boundingB.getSize();
	size /= 40000;
	SceneNode *bodyNode = sceneMgr->getRootSceneNode()->createChildSceneNode(mName + "ExplosionBodyNode");
	SceneNode *entityNode = bodyNode->createChildSceneNode(mName + "ExplosionEntityNode");
	entityNode->attachObject(entity);
	entityNode->scale(0.0005, 0.0005, 0.0005);
	entityNode->setPosition(0, -size.x, 0);
	SphereCollisionShape *boxShape = new SphereCollisionShape(size.x);
	mBody = new OgreBulletDynamics::RigidBody(mName + "SphereExplosion", mWorld);

	mBody->setShape(
		bodyNode,
		boxShape,
		0.0f,
		0.0f,
		0.001f,
		mPosition
	);

	mBody->disableDeactivation();
	mBody->getBulletRigidBody()->setAngularFactor(1.0f);
	mBody->getBulletRigidBody()->setGravity(btVector3(0, 0, 0));
	mBody->setLinearVelocity(mVelocity);

	mGraphicsSetUp = true;

}

bool Explosion::frameRenderingQueued(const Ogre::FrameEvent &evt){

	mRange -= mVelocity.length() * evt.timeSinceLastFrame;
	return true;

}

Ogre::Vector3 Explosion::getPosition(){
	if(mGraphicsSetUp)
		return mBody->getSceneNode()->getPosition();
	return Ogre::Vector3(0, 0, 0);
}

double Explosion::getRange(){return mRange;}

OgreBulletDynamics::RigidBody *Explosion::getBody(){return mBody;}
