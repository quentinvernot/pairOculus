#ifndef PLAYERANIMATION_H
#define PLAYERANIMATION_H

#include <OgreEntity.h>
#include <OgreSceneManager.h>

class PlayerAnimation {
	public:
		PlayerAnimation (Ogre::SceneManager *sceneMgr, Ogre::Entity *entity);
		~PlayerAnimation ();

		// Setup
		void setupHeadAnimation (Ogre::Entity *entity);
		void setupRunAnimation (Ogre::Entity *entity);
		void setupIdleAnimation (Ogre::Entity *entity);

		// Enable/disable Animations
		void stopAnimation ();
		void doIdleAnimation ();
		void doHeadAnimation ();
		void doRunAnimation ();
		Ogre::AnimationState *getPlayerAnimationState();
	private:
		//Attributes
		Ogre::SceneManager *mSceneMgr;
		Ogre::AnimationState *mPlayerAnimationState;
		Ogre::AnimationState *mPlayerIdle;
		Ogre::AnimationState *mPlayerHead;
		Ogre::AnimationState *mPlayerRun;
};
#endif /* PLAYERANIMATION_H */
