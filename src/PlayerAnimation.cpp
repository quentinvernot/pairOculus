#include "PlayerAnimation.hpp"

PlayerAnimation::PlayerAnimation(Ogre::SceneManager *sceneMgr, Ogre::Entity *entity) :
	mSceneMgr(sceneMgr) {
// Controle bones individualy
    Ogre::Bone* bHead = entity->getSkeleton()->getBone("HEAD");
    bHead->setManuallyControlled(true);
// Setup the animation
	Ogre::Real duration=4.0;
	Ogre::Real step=duration/4.0;
	Ogre::Animation* animation = mSceneMgr->createAnimation("HeadRotate",duration);
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0,entity->getSkeleton()->getBone("HEAD"));
// Then make the animation
	Ogre::TransformKeyFrame* key;

	key = track->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Radian(0), Ogre::Vector3::UNIT_Y));

	key = track->createNodeKeyFrame(step);
	key->setRotation(Ogre::Quaternion(Ogre::Radian(3.14/2), Ogre::Vector3::UNIT_Y));

	key = track->createNodeKeyFrame(2.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Radian(0), Ogre::Vector3::UNIT_Y));

	key = track->createNodeKeyFrame(3.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Radian(-3.14/2), Ogre::Vector3::UNIT_Y));

	key = track->createNodeKeyFrame(4.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Radian(0), Ogre::Vector3::UNIT_Y));
// Implement the animation
	mPlayerAnimationState = mSceneMgr->createAnimationState("HeadRotate");
	mPlayerAnimationState->setEnabled(true);
	mPlayerAnimationState->setLoop(true);
}

Ogre::AnimationState* PlayerAnimation::getPlayerAnimationState() {return mPlayerAnimationState;}
