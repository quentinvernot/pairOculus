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

	mGraphicsSetUp = true;

}

bool RemotePlayer::frameRenderingQueued(const Ogre::FrameEvent &evt){

	computeAcceleration();
	computeVelocity(evt);
	computeNodePosition(evt);

	resetCorrection();

	return true;

}
