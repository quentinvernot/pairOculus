#ifndef PLAYERANIMATION_H
#define PLAYERANIMATION_H

#include <OgreEntity.h>
#include <OgreSceneManager.h>

class PlayerAnimation {
	public:
		PlayerAnimation (Ogre::SceneManager *sceneMgr, Ogre::Entity *entity);
		~PlayerAnimation ();

		// Setup
		void setupHeadAnimation ();
		void setupRunAnimation ();
		void setupIdleAnimation ();

		// Enable/disable Animations
		void stopAnimation ();
		void doIdleAnimation ();
		void doHeadAnimation ();
		void doRunAnimation ();
		Ogre::AnimationState *getPlayerAnimationState();
	private:
		//Attributes
		Ogre::SceneManager *mSceneMgr;
		Ogre::Entity *mEntity;

		Ogre::AnimationState *mPlayerAnimationState;
};
#endif /* PLAYERANIMATION_H */
