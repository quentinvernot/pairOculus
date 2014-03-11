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

	using namespace OgreBulletCollisions;

	FloorPanel* fp = new FloorPanel(
		mSceneMgr->createManualObject("floor"),
		mScale*mHeight,
		mScale*mWidth
	);
	BlockFactory* bf = new BlockFactory(mSceneMgr);

	CollisionShape *Shape;
	Shape = new StaticPlaneCollisionShape(Ogre::Vector3(0,1,0), 0);
	OgreBulletDynamics::RigidBody *planeBody;
	planeBody = new OgreBulletDynamics::RigidBody("MapFloor", mWorld);
	planeBody->setStaticShape(Shape, 0.6f, 0.6f);

	SceneNode *floorNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	floorNode->attachObject(fp->GetManualFloor());

	Ogre::ManualObject *object;

	Ogre::Vector3 size(mScale/2, mScale/6, mScale/2);
	Ogre::Vector3 pos;
	Ogre::SceneNode *node;

	BoxCollisionShape *boxShape;
	OgreBulletDynamics::RigidBody *body;
	
	stringstream genName;

	for (unsigned int i = 0; i < mHeight; i++) {
		for (unsigned int j = 0; j < mWidth; j++) {

			object = bf->createBlock(mMap[i][j], i, j, mScale);

			if (object != NULL){

				node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
				node->attachObject(object);

				boxShape = new BoxCollisionShape(size);
				genName << "box_" << i << "_" << j;
				body = new OgreBulletDynamics::RigidBody(genName.str(), mWorld);
				genName.str("");
				genName.clear();

				pos = Ogre::Vector3(
					i*mScale + mScale/2,
					mScale/6,
					j*mScale + mScale/2
				);

				body->setStaticShape(
					node,
					boxShape,
					0.6f,					// dynamic body restitution
					0.6f,					// dynamic body friction
					pos
				);

			}

		}
	}
	
	Ogre::Light* light = mSceneMgr->createLight("light");
	light->setPosition(16, 80, 16);

}

Ogre::Vector3 LocalMap::getMapCenter(){
	return Ogre::Vector3(mHeight * (mScale+0.1f), 0, mWidth * (mScale+0.1f));
}

void LocalMap::viewMap() {
}
