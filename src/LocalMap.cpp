#include "LocalMap.hpp"

LocalMap::LocalMap(
	Ogre::SceneManager *sceneMgr,
	OgreBulletDynamics::DynamicsWorld *world,
	unsigned int height,
	unsigned int width,
	time_t seed
):
	Map(height, width, seed),
	mSceneMgr(sceneMgr),
	mWorld(world)
{
}

LocalMap::~LocalMap() {
}

void LocalMap::generate() {

	FloorPanel* fp = new FloorPanel(
		mSceneMgr->createManualObject("floor"),
		mScale*mHeight,
		mScale*mWidth
	);
	BlockFactory* bf = new BlockFactory(mSceneMgr);

	//mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(fp->GetManualFloor());
	Ogre::ManualObject *object;

	Ogre::Vector3 size(mScale/2, mScale/2, mScale/2);
	Ogre::Vector3 pos;
	Ogre::SceneNode *node;

	OgreBulletCollisions::BoxCollisionShape *boxShape;
	OgreBulletDynamics::RigidBody *body;
	
	stringstream genName;

	for (unsigned int i = 0; i < mHeight; i++) {
		for (unsigned int j = 0; j < mWidth; j++) {
			object = bf->createBlock(mMap[i][j], i, j, mScale);
			if (object != NULL){

				node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
				node->attachObject(object);
				node->setPosition(i*mScale, 0.0f, j*mScale);

				boxShape = new OgreBulletCollisions::BoxCollisionShape(size);
				genName << "box_" << i << "_" << j;
				body = new OgreBulletDynamics::RigidBody(genName.str(), mWorld);

				pos  = Ogre::Vector3(
					i*mScale + mScale/2,
					mScale/2,
					j*mScale + mScale/2
				);

				body->setStaticShape(
					boxShape,
					0.6f,					// dynamic body restitution
					0.6f,					// dynamic body friction
					pos
				);

			}
		}
	}

}

void LocalMap::viewMap() {
}
