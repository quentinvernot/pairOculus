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
	mMap(0),
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

	Ogre::LogManager::getSingletonPtr()->logMessage("Deleting Inputs");
	delete mInput;
	Ogre::LogManager::getSingletonPtr()->logMessage("Deleting Camera Manager");
	delete mCameraManager;
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
		if(mServerJoined)
			shutDown();
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
			tmp = new LocalPlayer(mNickname, mCameraManager);
		else
			tmp = new LocalPlayer(mNickname);
		mPlayerList->addPlayer(tmp);
	}

	Ogre::LogManager::getSingletonPtr()->logMessage("Creating Local Player");
	mLocalPlayer = mPlayerList->getPlayerByName(mNickname);
	std::cout << pl->size() << std::endl;
	std::cout << mPlayerList->size() << std::endl;

	Ogre::LogManager::getSingletonPtr()->logMessage("Creating Local Map");

	mMap = new Map(
		message->getMapHeight(),
		message->getMapWidth(),
		message->getSeed()
	);

	mGameSetUp = true;

	mGCListener->sendMessage(
		mNMFactory->buildMessage(NetworkMessage::GAMESTART)
	);

}

void Game::injectJoinRefuse(NetworkMessage::JoinRefuse *message){
	shutDown();
}

void Game::injectPlayerJoined(NetworkMessage::PlayerJoined *message){

	if(!mGameRunning){

		Ogre::LogManager::getSingletonPtr()->logMessage("Adding new player");
		LocalPlayer *lp = new LocalPlayer(message->getNickname());
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

	// Create the scene
	createScene();
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
	mLocalPlayer = new LocalPlayer(mNickname, mCameraManager);
	mPlayerList->addPlayer(mLocalPlayer);

	mOnlineMode = false;
	mGameSetUp = true;
	mGameRunning = true;

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

	//TODO : display player models

	Ogre::LogManager::getSingletonPtr()->logMessage("Creating Local Map");
	if(mOnlineMode)
		mLocalMap = new LocalMap(mMap, mSceneMgr, 100);
	else
		mLocalMap = new LocalMap(new Map(17, 17), mSceneMgr, 100);

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

	if(mOnlineMode && mGameSetUp && !mSceneCreated)
		createScene();

	mInput->capture();

	if(mGameRunning){
		for(unsigned int i = 0; i < mPlayerList->size(); i++)
			(*mPlayerList)[i]->frameRenderingQueued(evt);
	}
	
	if(mLocalPlayer->hadUsefulInput())
		sendPlayerInput();

	return true;

}

void Game::sendPlayerInput(){

	mGCListener->sendMessage(
		mNMFactory->buildMessage(NetworkMessage::PLAYERINPUT, mLocalPlayer)
	);

}
