#ifndef PLAYERANIMATION_H
#define PLAYERANIMATION_H

#include <OgreEntity.h>
#include <OgreSceneManager.h>

class PlayerAnimation {
	public:
		PlayerAnimation (Ogre::SceneManager *sceneMgr, Ogre::Entity *entity);
		~PlayerAnimation ();

		Ogre::AnimationState *getPlayerAnimationState();
	private:
		//Attributes
		Ogre::SceneManager *mSceneMgr;
		Ogre::AnimationState *mPlayerAnimationState;
};
#endif /* PLAYERANIMATION_H */
