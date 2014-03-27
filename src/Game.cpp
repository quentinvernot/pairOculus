#include "Game.hpp"

Game::Game(std::string nickname, std::string address):
	mOgreRoot(0),
	mOgreResourcesCfg(Ogre::StringUtil::BLANK),
	mOgrePluginsCfg(Ogre::StringUtil::BLANK),
	mSceneMgr(0),
	mCameraManager(0),
	mGameWindow(0),
	mInput(0),
	mNickname(nickname),
	mLocalPlayer(0),
	mPlayerList(new OgrePlayerList()),
	mBombManager(0),
	mLocalMap(0),
	mAddress(address),
	mPort("1337"),
	mNMFactory(new NetworkMessage::NetworkMessageFactory()),
	mGCListener(0),
	mOnlineMode(false),
	mServerJoined(false),
	mGameSetUp(false),
	mSceneCreated(false),
	mGameRunning(false),
	mGameEnded(false),
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
	Ogre::LogManager::getSingletonPtr()->logMessage("Deleting Players");
	for(unsigned int i = 0; i < mPlayerList->size(); i++)
		delete (*mPlayerList)[i];
	delete mPlayerList;
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

bool Game::keyPressed(const OIS::KeyEvent &arg){

	if(arg.key == OIS::KC_ESCAPE)
		mShutDownFlag = true;

	if(arg.key == OIS::KC_P)
		mCameraManager->increaseIPD();

	if(arg.key == OIS::KC_M)
		mCameraManager->decreaseIPD();
		
	if(arg.key == OIS::KC_N)
		mWorld->setShowDebugShapes(!mWorld->getShowDebugShapes());

	if(mOnlineMode && arg.key == OIS::KC_R)
		mGCListener->sendMessage(
			mNMFactory->buildMessage(NetworkMessage::GAMESTART)
		);

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
	OgrePlayer *tmp;

	mBombManager = new BombManager(mWorld);

	Ogre::LogManager::getSingletonPtr()->logMessage("Creating Local Map");
	mLocalMap = new LocalMap(
		mWorld,
		mPlayerList,
		mBombManager,
		message->getMapHeight(),
		message->getMapWidth(),
		message->getSeed()
	);

	Ogre::LogManager::getSingletonPtr()->logMessage("Filling player list");
	for(unsigned int i = 0; i < pl->size(); i++){
		if((*pl)[i]->getNickname() == mNickname){
			Ogre::LogManager::getSingletonPtr()->logMessage("Creating Local Player");
			mLocalPlayer = new LocalPlayer(mNickname, mWorld, mBombManager, mCameraManager);
			tmp = mLocalPlayer;
		}
		else
			tmp = new RemotePlayer((*pl)[i]->getNickname(), mWorld, mBombManager);

		tmp->setStartingPosition(
			(*pl)[i]->getX(),
			(*pl)[i]->getY(),
			(*pl)[i]->getZ()
		);

		mPlayerList->addPlayer(tmp);

	}

	mLocalPlayer->setPlayerEventListener(this);

	mGameSetUp = true;

}

void Game::injectJoinRefuse(NetworkMessage::JoinRefuse *message){
	shutDown();
}

void Game::injectPlayerJoined(NetworkMessage::PlayerJoined *message){

	if(!mGameRunning){

		Ogre::LogManager::getSingletonPtr()->logMessage("Adding new player");

		RemotePlayer *rp = new RemotePlayer(message->getNickname(), mWorld, mBombManager);
		rp->setStartingPosition(
			message->getX(),
			message->getY(),
			message->getZ()
		);
		mPlayerList->addPlayer(rp);

	}

}

void Game::injectPlayerLeft(NetworkMessage::PlayerLeft *message){

	Ogre::LogManager::getSingletonPtr()->logMessage("Removing player");
	if(mPlayerList->getPlayerByName(message->getNickname()))
		mPlayerList->getPlayerByName(
			message->getNickname()
		)->die();

}

void Game::injectGameStart(NetworkMessage::GameStart *message){
	Ogre::LogManager::getSingletonPtr()->logMessage("Starting game");
	mGameRunning = true;
}

void Game::injectGameEnd(NetworkMessage::GameEnd *message){

	Ogre::LogManager::getSingletonPtr()->logMessage("Ending game");
	mGameEnded = true;

	for(unsigned int i = 0; i < mPlayerList->size(); i++){
		if(!(*mPlayerList)[i]->isDead()){
			(*mPlayerList)[i]->win();
			std::cout << (*mPlayerList)[i]->getNickname() << " wins !" << std::endl;
		}
	}

}

void Game::injectPlayerInput(NetworkMessage::PlayerInput *message){

	std::string nickname = message->getNickname();

	if(nickname != mNickname)
		mPlayerList->getPlayerByName(nickname)->injectPlayerInput(message);

}

void Game::injectPlayerKilled(NetworkMessage::PlayerKilled *message){

	std::string nickname = message->getNickname();

	if(nickname != mNickname)
		mPlayerList->getPlayerByName(nickname)->die();

}

bool Game::playerInput(){

	if(!mOnlineMode || mGCListener->isClosed())
		return false;

	mGCListener->sendMessage(
		mNMFactory->buildMessage(NetworkMessage::PLAYERINPUT, mLocalPlayer)
	);

	return true;

}

bool Game::playerDied(){

	if(!mOnlineMode || mGCListener->isClosed())
		return false;

	mGCListener->sendMessage(
		mNMFactory->buildMessage(NetworkMessage::PLAYERKILLED, mNickname)
	);

	return true;

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

	// Create the frame listener
	createFrameListener();

	bulletSetup();

	if(mOnlineMode)
		networkSetup();
	else
		offlineSetup();

	if(mInput->hasOculusRift())
		mGameWindow->setViewMode(OCULUS);
	else
		mGameWindow->setViewMode(SIMPLE);

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

	mBombManager = new BombManager(mWorld);

	Ogre::LogManager::getSingletonPtr()->logMessage("Generating Local Map");
	mLocalMap = new LocalMap(mWorld, mPlayerList, mBombManager, 15, 15);

	Ogre::LogManager::getSingletonPtr()->logMessage("Creating Local Player");
	mLocalPlayer = new LocalPlayer(mNickname, mWorld, mBombManager, mCameraManager);
	mPlayerList->addPlayer(mLocalPlayer);

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
	Vector3 gravityVector(0,-9.81 * 2,0);

	mWorld = new OgreBulletDynamics::DynamicsWorld(mSceneMgr, bounds, gravityVector);
	debugDrawer = new OgreBulletCollisions::DebugDrawer();
	debugDrawer->setDrawWireframe(true);	// we want to see the Bullet containers

	mWorld->setDebugDrawer(debugDrawer);
	mWorld->setShowDebugShapes(false);
	SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode("debugDrawer", Ogre::Vector3::ZERO);
	node->attachObject(static_cast <SimpleRenderable *> (debugDrawer));

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
	mGCListener->setCallbackPlayerKilled(
		boost::bind(&Game::injectPlayerKilled, this, _1)
	);

}

void Game::createFrameListener(){

	Ogre::LogManager::getSingletonPtr()->logMessage("Creating Input");
	mInput = new Input(mGameWindow->getWindow());

	mInput->addKeyboardPressListener(this);
	mInput->addKeyboardPressListener(mGameWindow);

	mOgreRoot->addFrameListener(this);

}

void Game::createScene(){

	Animation::setDefaultInterpolationMode(Animation::IM_LINEAR);
	Animation::setDefaultRotationInterpolationMode(Animation::RIM_LINEAR);

	Ogre::LogManager::getSingletonPtr()->logMessage("Generating Player Graphics");

	for(unsigned int i = 0; i < mPlayerList->size(); i++)
		(*mPlayerList)[i]->generateGraphics();

	mLocalPlayer->lookAt(mLocalMap->getMapCenter());

	Ogre::LogManager::getSingletonPtr()->logMessage("Generating Local Map");
	mLocalMap->generate();

	// Lights
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

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

		if(!mSceneCreated){

			// Creates the scene.
			createScene();

			// Enables the player's inputs.
			mInput->addMouseMoveListener(mLocalPlayer);
			mInput->addKeyboardPressListener(mLocalPlayer);
			mInput->addKeyboardReleaseListener(mLocalPlayer);
			mInput->addSensorFusionListener(mLocalPlayer);

		}

		for(unsigned int i = 0; i < mPlayerList->size(); i++)
			(*mPlayerList)[i]->frameRenderingQueued(evt);

		mLocalMap->frameRenderingQueued(evt);
		mBombManager->frameRenderingQueued(evt);
		mWorld->stepSimulation(evt.timeSinceLastFrame);

	}

	return true;

}
