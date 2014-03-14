#include "Bomb.hpp"

Bomb::Bomb(
	std::string name,
	Ogre::Vector3 position,
	OgreBulletDynamics::DynamicsWorld *world
):
	mRange(3),
	mTTL(CLOCKS_PER_SEC * 3),
	mCreationTime(clock()),
	mName(name),
	mPosition(position),
	mWorld(world),
	mBody(0),
	mGraphicsSetUp(false)
{
}

Bomb::~Bomb(){
	mWorld->getSceneManager()->destroyEntity(mName + "BombEntity");
	delete mBody;
}

bool Bomb::hasExploded(clock_t now){
	return (now - mCreationTime > mTTL);
}

void Bomb::generateGraphics(){

	if(mGraphicsSetUp)
		return;
	
	using namespace OgreBulletCollisions;
	using namespace Ogre;

	Ogre::SceneManager *sceneMgr = mWorld->getSceneManager();
	Entity *entity = sceneMgr->createEntity(mName + "BombEntity", "bomb.mesh");
	entity->setCastShadows(true);
	AxisAlignedBox boundingB = entity->getBoundingBox();
	Vector3 size = boundingB.getSize();
	size /= 10;
	SceneNode *bodyNode = sceneMgr->getRootSceneNode()->createChildSceneNode(mName + "BombBodyNode");
	SceneNode *entityNode = bodyNode->createChildSceneNode(mName + "BombEntityNode");
	entityNode->attachObject(entity);
	entityNode->scale(0.2, 0.2, 0.2);
	entityNode->setPosition(0, -size.x, 0);
	SphereCollisionShape *boxShape = new SphereCollisionShape(size.x);
	mBody = new OgreBulletDynamics::RigidBody(mName + "SphereBomb", mWorld);

	mBody->setShape(
		bodyNode,
		boxShape,
		0.6f,
		0.6f,
		2.85f,
		mPosition
	);

	mBody->disableDeactivation();
	mBody->getBulletRigidBody()->setAngularFactor(1.0f);

	mGraphicsSetUp = true;

}

void Bomb::detonate(){mTTL = 0;}

std::string Bomb::getName(){return mName;}

Ogre::Vector3 Bomb::getPosition(){
	if(mGraphicsSetUp)
		return mBody->getSceneNode()->getPosition();
	return Ogre::Vector3(0, 0, 0);
}

int Bomb::getRange(){return mRange;}

OgreBulletDynamics::RigidBody *Bomb::getBody(){return mBody;}
