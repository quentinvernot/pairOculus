#include "Game.hpp"

Game::Game() :
	ogreRoot(0),
	ogreResourcesCfg(Ogre::StringUtil::BLANK),
	ogrePluginsCfg(Ogre::StringUtil::BLANK),
	sceneMgr(0),
	cameraManager(0),
	localPlayer(0),
	gameWindow(0),
	input(0),
	shutDownFlag(false)
{
}

Game::~Game(){

	Ogre::LogManager::getSingletonPtr()->logMessage("Deleting Inputs");
	delete input;
	Ogre::LogManager::getSingletonPtr()->logMessage("Deleting Camera Manager");
	delete cameraManager;
	Ogre::LogManager::getSingletonPtr()->logMessage("Deleting Local Player");
	delete localPlayer;
	Ogre::LogManager::getSingletonPtr()->logMessage("Deleting GameWindow");
	delete gameWindow;
	Ogre::LogManager::getSingletonPtr()->logMessage("Deleting OGRE Root");
	delete ogreRoot;

}

void Game::go(){
#ifdef _DEBUG
	ogreResourcesCfg = "resources_d.cfg";
	ogrePluginsCfg = "plugins_d.cfg";
#else
	ogreResourcesCfg = "resources.cfg";
	ogrePluginsCfg = "plugins.cfg";
#endif

	if (!setup())
		return;

	ogreRoot->startRendering();

	// clean up
	destroyScene();
}

bool Game::injectMouseMoved(const OIS::MouseEvent &arg){
	return localPlayer->injectMouseMoved(arg);
}

bool Game::injectMousePressed(
	const OIS::MouseEvent &arg, OIS::MouseButtonID id
){
	return localPlayer->injectMousePressed(arg, id);
}

bool Game::injectMouseReleased(
	const OIS::MouseEvent &arg, OIS::MouseButtonID id
){
	return localPlayer->injectMouseReleased(arg, id);
}

bool Game::injectKeyDown(const OIS::KeyEvent &arg){

	if(arg.key == OIS::KC_ESCAPE)
		shutDownFlag = true;

	return localPlayer->injectKeyDown(arg);

}

bool Game::injectKeyUp(const OIS::KeyEvent &arg){
	return localPlayer->injectKeyUp(arg);
}

bool Game::setup(){

	ogreRoot = new Ogre::Root(ogrePluginsCfg);

	setupResources();
	
	chooseSceneManager();

	if(!configure())
		return false;

	// Create any resource listeners (for loading screens)
	createResourceListener();
	// Load resources
	loadResources();
	gameWindow->setViewMode("oculus");

	// Create the scene
	createScene();

	createFrameListener();

	return true;

};

bool Game::configure(){

	// Show the configuration dialog and initialise the system
	// You can skip this and use root.restoreConfig() to load configuration
	// settings if you were sure there are valid ones saved in ogre.cfg
	if(ogreRoot->showConfigDialog()){

		Ogre::LogManager::getSingletonPtr()->logMessage("Creating Camera Manager");
		cameraManager = new CameraManager(sceneMgr);
		
		Ogre::LogManager::getSingletonPtr()->logMessage("Creating Game Window");
		gameWindow = new GameWindow(
			cameraManager,
			ogreRoot->initialise(true, "Game Render Window")
		);

		Ogre::LogManager::getSingletonPtr()->logMessage("Creating Local Player");
		localPlayer = new LocalPlayer("Player 1", cameraManager);

		return true;

	}
	else
		return false;

}

void Game::chooseSceneManager(){
	// Get the SceneManager, in this case a generic one
	sceneMgr = ogreRoot->createSceneManager(Ogre::ST_GENERIC);
}

void Game::createFrameListener(){

	Ogre::LogManager::getSingletonPtr()->logMessage("Creating Input");
	input = new Input(gameWindow->getWindow());

	input->setMouseListener(
		boost::bind(&Game::injectMouseMoved, this, _1),
		boost::bind(&Game::injectMousePressed, this, _1, _2),
		boost::bind(&Game::injectMouseReleased, this, _1, _2)
	);

	input->setKeyboardListener(
		boost::bind(&Game::injectKeyDown, this, _1),
		boost::bind(&Game::injectKeyUp, this, _1)
	);

	ogreRoot->addFrameListener(this);

}

void Game::createScene(){

	sceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

	Ogre::SceneNode* headNode = sceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode");
	Ogre::Entity* ogreHead = sceneMgr->createEntity("Head", "ogrehead.mesh");
	headNode->attachObject(ogreHead);

	headNode->setPosition(50,-50,-70);

	Ogre::Light* light = sceneMgr->createLight("MainLight");
	light->setPosition(0, 80, 0);

}

void Game::destroyScene(){
}

void Game::setupResources(){
	// Load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load(ogreResourcesCfg);

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
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

void Game::createResourceListener(){
}

void Game::loadResources(){
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

bool Game::frameRenderingQueued(const Ogre::FrameEvent &evt){

	if(shutDownFlag)
		return false;

	input->capture();
	
	localPlayer->frameRenderingQueued(evt);

	return true;

}
