#include "Game.hpp"

Game::Game(std::string nickname, std::string address, std::string port):
	mOgreRoot(0),
	mOgreResourcesCfg(Ogre::StringUtil::BLANK),
	mOgrePluginsCfg(Ogre::StringUtil::BLANK),
	mSceneMgr(0),
	mCameraManager(0),
	mGameWindow(0),
	mInput(0),
	mNickname(nickname),
	mLocalPlayer(0),
	mPlayerList(new LocalPlayerList()),
	mLocalMap(0),
	mAddress(address),
	mPort(port),
	mNMFactory(new NetworkMessage::NetworkMessageFactory()),
	mGCListener(0),
	mOnlineMode(false),
	mServerJoined(false),
	mGameSetUp(false),
	mSceneCreated(false),
	mGameRunning(false),
	mShutDownFlag(false)
{
	if(mAddress != "")
		mOnlineMode = true;
}

Game::~Game(){

	Ogre::LogManager::getSingletonPtr()->logMessage("Deleting Client Listener");
	delete mGCListener;
	Ogre::LogManager::getSingletonPtr()->logMessage("Deleting Inputs");
	delete mInput;
	Ogre::LogManager::getSingletonPtr()->logMessage("Deleting Camera Manager");
	delete mCameraManager;
	Ogre::LogManager::getSingletonPtr()->logMessage("Deleting Local Map");
	delete mLocalMap;
	Ogre::LogManager::getSingletonPtr()->logMessage("Deleting Local Player");
	delete mLocalPlayer;
	Ogre::LogManager::getSingletonPtr()->logMessage("Deleting Game Window");
	delete mGameWindow;
	Ogre::LogManager::getSingletonPtr()->logMessage("Deleting OGRE Root");
	delete mOgreRoot;

}

void Game::go(){

#ifdef _DEBUG
	mOgreResourcesCfg = "resources_d.cfg";
	mOgrePluginsCfg = "plugins_d.cfg";
#else
	mOgreResourcesCfg = "resources.cfg";
	mOgrePluginsCfg = "plugins.cfg";
#endif

	if (!setup())
		return;

	mOgreRoot->startRendering();

	// clean up
	destroyScene();

}

void Game::shutDown(){
	mShutDownFlag = true;
}

bool Game::injectMouseMove(const OIS::MouseEvent &arg){

	if(mGameSetUp)
		return mLocalPlayer->injectMouseMove(arg);

	return true;

}

bool Game::injectMouseDown(
	const OIS::MouseEvent &arg, OIS::MouseButtonID id
){

	if(mGameSetUp)
		return mLocalPlayer->injectMouseDown(arg, id);

	return true;

}

bool Game::injectMouseUp(
	const OIS::MouseEvent &arg, OIS::MouseButtonID id
){

	if(mGameSetUp)
		return mLocalPlayer->injectMouseUp(arg, id);

	return true;

}

bool Game::injectKeyDown(const OIS::KeyEvent &arg){

	if(arg.key == OIS::KC_ESCAPE)
		mShutDownFlag = true;
	if(mOnlineMode && arg.key == OIS::KC_R)
		mGCListener->sendMessage(
			mNMFactory->buildMessage(NetworkMessage::GAMESTART)
		);

	mGameWindow->injectKeyDown(arg);

	if(mGameSetUp)
		return mLocalPlayer->injectKeyDown(arg);

	return true;

}

bool Game::injectKeyUp(const OIS::KeyEvent &arg){

	if(mGameSetUp)
		return mLocalPlayer->injectKeyUp(arg);

	return true;

}

void Game::injectClientClose(){

	if(!mGameSetUp){
		if(mServerJoined){
			Ogre::LogManager::getSingletonPtr()->logMessage("Lost connection to the server, shutting down");
			shutDown();
		}
		else{
			Ogre::LogManager::getSingletonPtr()->logMessage("Error while joining server, setting up the game as single player");
			offlineSetup();
		}
	}

}

void Game::injectJoinAccept(NetworkMessage::JoinAccept *message){

	mServerJoined = true;

	PlayerList *pl = message->getPlayerList();
	LocalPlayer *tmp;

	Ogre::LogManager::getSingletonPtr()->logMessage("Filling player list");
	for(unsigned int i = 0; i < pl->size(); i++){
		if((*pl)[i]->getNickname() == mNickname)
			tmp = new LocalPlayer(mNickname, mSceneMgr, mWorld, mCameraManager);
		else
			tmp = new LocalPlayer((*pl)[i]->getNickname(), mSceneMgr, mWorld);

		tmp->setNodePositionX((*pl)[i]->getNodePositionX());
		tmp->setNodePositionY((*pl)[i]->getNodePositionY());
		tmp->setNodePositionZ((*pl)[i]->getNodePositionZ());

		mPlayerList->addPlayer(tmp);

	}

	Ogre::LogManager::getSingletonPtr()->logMessage("Creating Local Player");
	mLocalPlayer = mPlayerList->getPlayerByName(mNickname);

	Ogre::LogManager::getSingletonPtr()->logMessage("Creating Local Map");
	mLocalMap = new LocalMap(
		mSceneMgr,
		mWorld,
		message->getMapHeight(),
		message->getMapWidth(),
		message->getSeed()
	);

	mGameSetUp = true;

}

void Game::injectJoinRefuse(NetworkMessage::JoinRefuse *message){
	shutDown();
}

void Game::injectPlayerJoined(NetworkMessage::PlayerJoined *message){

	if(!mGameRunning){

		Ogre::LogManager::getSingletonPtr()->logMessage("Adding new player");
		LocalPlayer *lp = new LocalPlayer(message->getNickname(), mSceneMgr, mWorld);
		lp->setNodePositionX(message->getPositionX());
		lp->setNodePositionY(message->getPositionY());
		lp->setNodePositionZ(message->getPositionZ());
		mPlayerList->addPlayer(lp);

	}

}

void Game::injectPlayerLeft(NetworkMessage::PlayerLeft *message){

	Ogre::LogManager::getSingletonPtr()->logMessage("Removing player");
	mPlayerList->removePlayer(
		mPlayerList->getPlayerByName(message->getNickname())
	);

}

void Game::injectGameStart(NetworkMessage::GameStart *message){
	Ogre::LogManager::getSingletonPtr()->logMessage("Starting game");
	mGameRunning = true;
}

void Game::injectGameEnd(NetworkMessage::GameEnd *message){
	Ogre::LogManager::getSingletonPtr()->logMessage("Ending game");
	mGameRunning = false;
}

void Game::injectPlayerInput(NetworkMessage::PlayerInput *message){

	std::string nickname = message->getNickname();

	if(nickname != mNickname)
		mPlayerList->getPlayerByName(nickname)->injectPlayerInput(message);

}

bool Game::setup(){

	mOgreRoot = new Ogre::Root(mOgrePluginsCfg);

	setupResources();

	chooseSceneManager();

	if(!configure())
		return false;

	// Create any resource listeners (for loading screens)
	createResourceListener();
	// Load resources
	loadResources();
	mGameWindow->setViewMode("oculus");

	// Create the frame listener
	createFrameListener();

	return true;

}

void Game::chooseSceneManager(){
	// Get the SceneManager, in this case a generic one
	mSceneMgr = mOgreRoot->createSceneManager(Ogre::ST_GENERIC);
}

bool Game::configure(){

	// Show the configuration dialog and initialise the system
	// You can skip this and use root.restoreConfig() to load configuration
	// settings if you were sure there are valid ones saved in ogre.cfg
	if(mOgreRoot->showConfigDialog()){

		Ogre::LogManager::getSingletonPtr()->logMessage("Creating Camera Manager");
		mCameraManager = new CameraManager(mSceneMgr);

		Ogre::LogManager::getSingletonPtr()->logMessage("Creating Game Window");
		mGameWindow = new GameWindow(
			mCameraManager,
			mOgreRoot->initialise(true, "Game Render Window")
		);

		bulletSetup();

		if(mOnlineMode)
			networkSetup();
		else
			offlineSetup();

		return true;

	}
	else
		return false;

}

bool Game::networkSetup(){

	Ogre::LogManager::getSingletonPtr()->logMessage("Starting Game Client");
	mGCListener = new GameClient::Listener(mAddress, mPort);
	createNetworkListener();
	mGCListener->start();

	mGCListener->sendMessage(mNMFactory->buildMessage(NetworkMessage::JOIN, mNickname));

	return true;

}

bool Game::offlineSetup(){

	Ogre::LogManager::getSingletonPtr()->logMessage("Creating Local Player");
	mLocalPlayer = new LocalPlayer(mNickname, mSceneMgr, mWorld, mCameraManager);
	mPlayerList->addPlayer(mLocalPlayer);

	Ogre::LogManager::getSingletonPtr()->logMessage("Generating Local Map");
	mLocalMap = new LocalMap(mSceneMgr, mWorld, 15, 15);

	mLocalMap->setStartingPosition(0, mLocalPlayer);

	mOnlineMode = false;
	mGameSetUp = true;
	mGameRunning = true;

	return true;

}

bool Game::bulletSetup(){

	AxisAlignedBox bounds(
		Ogre::Vector3 (-10000, -10000, -10000),
		Ogre::Vector3 (10000,  10000,  10000)
	);
	Vector3 gravityVector(0,-98.1,0);

	mWorld = new OgreBulletDynamics::DynamicsWorld(mSceneMgr, bounds, gravityVector);
	debugDrawer = new OgreBulletCollisions::DebugDrawer();
	debugDrawer->setDrawWireframe(true);	// we want to see the Bullet containers

	mWorld->setDebugDrawer(debugDrawer);
	mWorld->setShowDebugShapes(true);		// enable it if you want to see the Bullet containers
	SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode("debugDrawer", Ogre::Vector3::ZERO);
	node->attachObject(static_cast <SimpleRenderable *> (debugDrawer));

	//bomberman test mesh
	Ogre::Entity *entity = mSceneMgr->createEntity("Box", "bomberman.mesh");
	entity->setCastShadows(true);
	// we need the bounding box of the box to be able to set the size of the Bullet-box
	Ogre::AxisAlignedBox boundingB = entity->getBoundingBox();
	Ogre::Vector3 size = boundingB.getSize();
	size /= 2;
	Ogre::SceneNode *bodyNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::SceneNode *entityNode = bodyNode->createChildSceneNode();
	entityNode->setPosition(0, -3, 0);
	entityNode->attachObject(entity);

	// after that create the Bullet shape with the calculated size
	OgreBulletCollisions::BoxCollisionShape *sceneBoxShape = new OgreBulletCollisions::BoxCollisionShape(size);
	// and the Bullet rigid body
	OgreBulletDynamics::RigidBody *defaultBody = new OgreBulletDynamics::RigidBody(
		"defaultBoxRigid", mWorld
	);

	Ogre::Vector3 pos(-100, 100, -100);

	defaultBody->setShape(
		bodyNode,
		sceneBoxShape,
		0.6f,			// dynamic body restitution
		0.6f,			// dynamic body friction
		1.0f, 			// dynamic bodymass
		pos				// starting position of the box
	);

	return true;

}

void Game::createNetworkListener(){

	mGCListener->setCallbackClose(boost::bind(&Game::injectClientClose, this));
	mGCListener->setCallbackJoinAccept(
		boost::bind(&Game::injectJoinAccept, this, _1)
	);
	mGCListener->setCallbackJoinRefuse(
		boost::bind(&Game::injectJoinRefuse, this, _1)
	);
	mGCListener->setCallbackPlayerJoined(
		boost::bind(&Game::injectPlayerJoined, this, _1)
	);
	mGCListener->setCallbackPlayerLeft(
		boost::bind(&Game::injectPlayerLeft, this, _1)
	);
	mGCListener->setCallbackGameStart(
		boost::bind(&Game::injectGameStart, this, _1)
	);
	mGCListener->setCallbackGameEnd(
		boost::bind(&Game::injectGameEnd, this, _1)
	);
	mGCListener->setCallbackPlayerInput(
		boost::bind(&Game::injectPlayerInput, this, _1)
	);

}

void Game::createFrameListener(){

	Ogre::LogManager::getSingletonPtr()->logMessage("Creating Input");
	mInput = new Input(mGameWindow->getWindow());

	mInput->setMouseListener(
		boost::bind(&Game::injectMouseMove, this, _1),
		boost::bind(&Game::injectMouseDown, this, _1, _2),
		boost::bind(&Game::injectMouseUp, this, _1, _2)
	);

	mInput->setKeyboardListener(
		boost::bind(&Game::injectKeyDown, this, _1),
		boost::bind(&Game::injectKeyUp, this, _1)
	);

	mOgreRoot->addFrameListener(this);

}

void Game::createScene(){

	Animation::setDefaultInterpolationMode(Animation::IM_LINEAR);
	Animation::setDefaultRotationInterpolationMode(Animation::RIM_LINEAR);

	for(unsigned int i = 0; i < mPlayerList->size(); i++)
		(*mPlayerList)[i]->generateGraphics();
/*
	Ogre::LogManager::getSingletonPtr()->logMessage("Creating Local Map");
	if(mOnlineMode)
		mLocalMap = new LocalMap(15, 15);	// TODO add the seed, put the H and W of the server
	else
		mLocalMap = new LocalMap(15, 15);
*/
	mLocalPlayer->lookAt(mLocalMap->getMapCenter());

	Ogre::LogManager::getSingletonPtr()->logMessage("Generating Local Map");
	mLocalMap->generate();

	// Lights
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(0, 80, 0);

	mSceneCreated = true;

}

void Game::destroyScene(){}

void Game::setupResources(){

	// Load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load(mOgreResourcesCfg);

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;

	while (seci.hasMoreElements()){

		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;

		for (i = settings->begin(); i != settings->end(); ++i){

			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);

		}

	}

}

void Game::createResourceListener(){}

void Game::loadResources(){
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

bool Game::frameRenderingQueued(const Ogre::FrameEvent &evt){

	if(mShutDownFlag)
		return false;

	if(mOnlineMode && mGCListener->isClosed())
		return false;

	mInput->capture();

	if(mGameRunning){

		if(!mSceneCreated)
			createScene();

		for(unsigned int i = 0; i < mPlayerList->size(); i++)
			(*mPlayerList)[i]->frameRenderingQueued(evt);

		if(mOnlineMode && mLocalPlayer->hadUsefulInput())
			sendPlayerInput();

		mWorld->stepSimulation(evt.timeSinceLastFrame);
	}

	return true;

}

void Game::sendPlayerInput(){

	mGCListener->sendMessage(
		mNMFactory->buildMessage(NetworkMessage::PLAYERINPUT, mLocalPlayer)
	);

}
