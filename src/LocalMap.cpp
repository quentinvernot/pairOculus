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

	SceneNode *floorNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("floorNode");
	floorNode->attachObject(fp->GetManualFloor());

	Ogre::ManualObject *object;

	Ogre::Vector3 size(mScale/2, mScale/6, mScale/2);
	Ogre::Vector3 pos;
	Ogre::SceneNode *node;

	BoxCollisionShape *boxShape;
	
	stringstream genName;

	mBodies = new OgreBulletDynamics::RigidBody **[mHeight];
	for (unsigned int i = 0; i < mHeight; i++) {

		mBodies[i] = new OgreBulletDynamics::RigidBody *[mWidth];
		for (unsigned int j = 0; j < mWidth; j++) {

			object = bf->createBlock(mMap[i][j], i, j, mScale);
			mBodies[i][j] = 0;

			if (object != NULL){

				genName << i << "_" << j;
				node = mSceneMgr->getRootSceneNode()->createChildSceneNode("node_" + genName.str());
				node->attachObject(object);

				boxShape = new BoxCollisionShape(size);
				mBodies[i][j] = new OgreBulletDynamics::RigidBody("box_" + genName.str(), mWorld);
				genName.str("");
				genName.clear();

				pos = Ogre::Vector3(
					i*mScale + mScale/2,
					mScale/6,
					j*mScale + mScale/2
				);

				mBodies[i][j]->setStaticShape(
					node,
					boxShape,
					0.6f,					// dynamic body restitution
					0.6f,					// dynamic body friction
					pos
				);

			}

		}

	}
	
	Entity *entity = mWorld->getSceneManager()->createEntity("bomb.mesh");
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	node->setPosition(Ogre::Vector3(0, mScale/2, 0));
	node->attachObject(entity);
	node->scale(0.1, 0.1, 0.1);

	Ogre::Light* light = mSceneMgr->createLight("light");
	light->setPosition(16, 80, 16);

}

Ogre::Vector3 LocalMap::getMapCenter(){
	return Ogre::Vector3(mHeight * (mScale+0.1f), 0, mWidth * (mScale+0.1f));
}

void LocalMap::createExplosion(Ogre::Vector3 pos, int range){

	if(pos.y < 0 || pos.y >= mScale/3) //above or below the map
		return;

	int row = getRow(pos), col = getCol(pos), i;

	if(row == -1 || col == -1) //outside the map
		return;

	if(!isUnbreakable(row, col)){

		mMap[row][col] = EMPTY;

		i = 1;
		while(!isUnbreakable(row + i, col) && range - i > 0){
			destroyBlock(row + i, col);
			i++;
		}

		i = -1;
		while(!isUnbreakable(row + i, col) && range + i > 0){
			destroyBlock(row + i, col);
			i--;
		}
		
		i = 1;
		while(!isUnbreakable(row, col + i) && range - i > 0){
			destroyBlock(row, col + i);
			i++;
		}

		i = -1;
		while(!isUnbreakable(row, col + i) && range + i > 0){
			destroyBlock(row, col + i);
			i--;
		}

	}

}

int LocalMap::getRow(Ogre::Vector3 pos){

	if(pos.x < 0 || pos.x >= mHeight * mScale)
		return -1;

	return pos.x / mScale;

}

int LocalMap::getCol(Ogre::Vector3 pos){

	if(pos.z < 0 || pos.x >= mWidth * mScale)
		return -1;

	return pos.z / mScale;

}

void LocalMap::viewMap() {
}

void LocalMap::destroyBlock(unsigned int i, unsigned int j){

	stringstream genName;

	mMap[i][j] = EMPTY;
	genName << "manualBlock_" << i << "_" << j;
	mWorld->getSceneManager()->destroyManualObject(genName.str());

	if(mBodies[i][j] != 0){
		delete mBodies[i][j];
		mBodies[i][j] = 0;
	}

}
