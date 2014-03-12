#include "PlayerAnimation.hpp"

PlayerAnimation::PlayerAnimation(Ogre::SceneManager *sceneMgr, Ogre::Entity *entity) :
	mSceneMgr(sceneMgr) {

	setupIdleAnimation (entity);
	setupHeadAnimation (entity);
	setupRunAnimation (entity);

	doIdleAnimation ();
}

void PlayerAnimation::setupIdleAnimation (Ogre::Entity *entity) {
	// Controle bones individualy
	Ogre::Bone* bHipRight = entity->getSkeleton()->getBone("HIP_RIGHT");
	bHipRight->setManuallyControlled(true);
	Ogre::Bone* bHipLeft = entity->getSkeleton()->getBone("HIP_LEFT");
	bHipLeft->setManuallyControlled(true);
	Ogre::Bone* bShoulderRight = entity->getSkeleton()->getBone("SHOULDER_RIGHT");
	bShoulderRight->setManuallyControlled(true);
	Ogre::Bone* bShoulderLeft = entity->getSkeleton()->getBone("SHOULDER_LEFT");
	bShoulderLeft->setManuallyControlled(true);

	// Setup the animation
	Ogre::Real duration=1.0;
	Ogre::Animation* animation = mSceneMgr->createAnimation(entity->getName() + "Idle",duration);
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack* tHipRight = animation->createNodeTrack(0,entity->getSkeleton()->getBone("HIP_RIGHT"));
	Ogre::NodeAnimationTrack* tHipLeft = animation->createNodeTrack(1,entity->getSkeleton()->getBone("HIP_LEFT"));
	Ogre::NodeAnimationTrack* tShoulderRight = animation->createNodeTrack(2,entity->getSkeleton()->getBone("SHOULDER_RIGHT"));
	Ogre::NodeAnimationTrack* tShoulderLeft = animation->createNodeTrack(3,entity->getSkeleton()->getBone("SHOULDER_LEFT"));

	// Then make the animation
	Ogre::TransformKeyFrame* key;

	// Hip Right
	key = tHipRight->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(20), Ogre::Vector3::UNIT_Z));

	// Hip Left
	key = tHipLeft->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-20), Ogre::Vector3::UNIT_Z));

	// Shoulder Right
	key = tShoulderRight->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(60), Ogre::Vector3::UNIT_Z));

	// Shoulder Left
	key = tShoulderLeft->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-60), Ogre::Vector3::UNIT_Z));

	mPlayerIdle = mSceneMgr->createAnimationState(entity->getName() + "Idle");
}

void PlayerAnimation::setupHeadAnimation (Ogre::Entity *entity) {
	// Controle bones individualy
    Ogre::Bone* bHead = entity->getSkeleton()->getBone("HEAD");
    bHead->setManuallyControlled(true);

	// Setup the animation
	Ogre::Real duration=4.0;
	Ogre::Real step=duration/4.0;
	Ogre::Animation* animation = mSceneMgr->createAnimation(entity->getName() + "HeadRotate",duration);
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0,entity->getSkeleton()->getBone("HEAD"));

	// Then make the animation
	Ogre::TransformKeyFrame* key;

	key = track->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_Y));

	key = track->createNodeKeyFrame(step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_Y));

	key = track->createNodeKeyFrame(2.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_Y));

	key = track->createNodeKeyFrame(3.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-90), Ogre::Vector3::UNIT_Y));

	key = track->createNodeKeyFrame(4.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_Y));

	mPlayerHead = mSceneMgr->createAnimationState(entity->getName() + "HeadRotate");
}

void PlayerAnimation::setupRunAnimation (Ogre::Entity *entity) {
	// Controle bones individualy
	Ogre::Bone* bKneeRight = entity->getSkeleton()->getBone("KNEE_RIGHT");
	bKneeRight->setManuallyControlled(true);
	Ogre::Bone* bHipRight = entity->getSkeleton()->getBone("HIP_RIGHT");
	bHipRight->setManuallyControlled(true);
	Ogre::Bone* bKneeLeft = entity->getSkeleton()->getBone("KNEE_LEFT");
	bKneeLeft->setManuallyControlled(true);
	Ogre::Bone* bHipLeft = entity->getSkeleton()->getBone("HIP_LEFT");
	bHipLeft->setManuallyControlled(true);
	Ogre::Bone* bShoulderRight = entity->getSkeleton()->getBone("SHOULDER_RIGHT");
	bShoulderRight->setManuallyControlled(true);
	Ogre::Bone* bShoulderLeft = entity->getSkeleton()->getBone("SHOULDER_LEFT");
	bShoulderLeft->setManuallyControlled(true);
	Ogre::Bone* bElbowRight = entity->getSkeleton()->getBone("ELBOW_RIGHT");
	bElbowRight->setManuallyControlled(true);
	Ogre::Bone* bElbowLeft = entity->getSkeleton()->getBone("ELBOW_LEFT");
	bElbowLeft->setManuallyControlled(true);

	// Setup the animation
	Ogre::Real duration=1.5;
	Ogre::Real step=duration/4.0;
	Ogre::Animation* animation = mSceneMgr->createAnimation(entity->getName() + "Run",duration);
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack* tKneeRight = animation->createNodeTrack(0,entity->getSkeleton()->getBone("KNEE_RIGHT"));
	Ogre::NodeAnimationTrack* tHipRight = animation->createNodeTrack(1,entity->getSkeleton()->getBone("HIP_RIGHT"));
	Ogre::NodeAnimationTrack* tKneeLeft = animation->createNodeTrack(2,entity->getSkeleton()->getBone("KNEE_LEFT"));
	Ogre::NodeAnimationTrack* tHipLeft = animation->createNodeTrack(3,entity->getSkeleton()->getBone("HIP_LEFT"));
	Ogre::NodeAnimationTrack* tShoulderRight = animation->createNodeTrack(4,entity->getSkeleton()->getBone("SHOULDER_RIGHT"));
	Ogre::NodeAnimationTrack* tShoulderLeft = animation->createNodeTrack(5,entity->getSkeleton()->getBone("SHOULDER_LEFT"));
	Ogre::NodeAnimationTrack* tElbowRight = animation->createNodeTrack(6,entity->getSkeleton()->getBone("ELBOW_RIGHT"));
	Ogre::NodeAnimationTrack* tElbowLeft = animation->createNodeTrack(7,entity->getSkeleton()->getBone("ELBOW_LEFT"));

	// Then make the animation
	Ogre::TransformKeyFrame* key;

	// Knee Right
	key = tKneeRight->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tKneeRight->createNodeKeyFrame(step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(45), Ogre::Vector3::UNIT_X));

	key = tKneeRight->createNodeKeyFrame(2.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tKneeRight->createNodeKeyFrame(3.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(80), Ogre::Vector3::UNIT_X));

	key = tKneeRight->createNodeKeyFrame(4.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	// Hip Right
	key = tHipRight->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tHipRight->createNodeKeyFrame(step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(45), Ogre::Vector3::UNIT_X));

	key = tHipRight->createNodeKeyFrame(2.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tHipRight->createNodeKeyFrame(3.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-80), Ogre::Vector3::UNIT_X));

	key = tHipRight->createNodeKeyFrame(4.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	// Knee Left
	key = tKneeLeft->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tKneeLeft->createNodeKeyFrame(step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(80), Ogre::Vector3::UNIT_X));

	key = tKneeLeft->createNodeKeyFrame(2.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tKneeLeft->createNodeKeyFrame(3.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(45), Ogre::Vector3::UNIT_X));

	key = tKneeLeft->createNodeKeyFrame(4.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	// Hip Right
	key = tHipLeft->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tHipLeft->createNodeKeyFrame(step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-80), Ogre::Vector3::UNIT_X));

	key = tHipLeft->createNodeKeyFrame(2.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tHipLeft->createNodeKeyFrame(3.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(45), Ogre::Vector3::UNIT_X));

	key = tHipLeft->createNodeKeyFrame(4.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	// Shoulder Right
	key = tShoulderRight->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tShoulderRight->createNodeKeyFrame(step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-45), Ogre::Vector3::UNIT_X));

	key = tShoulderRight->createNodeKeyFrame(2.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tShoulderRight->createNodeKeyFrame(3.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(45), Ogre::Vector3::UNIT_X));

	key = tShoulderRight->createNodeKeyFrame(4.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	// Shoulder Left
	key = tShoulderLeft->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tShoulderLeft->createNodeKeyFrame(step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(45), Ogre::Vector3::UNIT_X));

	key = tShoulderLeft->createNodeKeyFrame(2.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tShoulderLeft->createNodeKeyFrame(3.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-45), Ogre::Vector3::UNIT_X));

	key = tShoulderLeft->createNodeKeyFrame(4.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	// Elbow Right
	key = tElbowRight->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-20), Ogre::Vector3::UNIT_X));

	key = tElbowRight->createNodeKeyFrame(step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-60), Ogre::Vector3::UNIT_X));

	key = tElbowRight->createNodeKeyFrame(2.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-20), Ogre::Vector3::UNIT_X));

	key = tElbowRight->createNodeKeyFrame(3.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-20), Ogre::Vector3::UNIT_X));

	key = tElbowRight->createNodeKeyFrame(4.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-20), Ogre::Vector3::UNIT_X));

	// Elbow Left
	key = tElbowLeft->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-20), Ogre::Vector3::UNIT_X));

	key = tElbowLeft->createNodeKeyFrame(step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-20), Ogre::Vector3::UNIT_X));

	key = tElbowLeft->createNodeKeyFrame(2.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-20), Ogre::Vector3::UNIT_X));

	key = tElbowLeft->createNodeKeyFrame(3.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-60), Ogre::Vector3::UNIT_X));

	key = tElbowLeft->createNodeKeyFrame(4.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-20), Ogre::Vector3::UNIT_X));

	mPlayerRun = mSceneMgr->createAnimationState(entity->getName() + "Run");

}

void PlayerAnimation::doIdleAnimation () {
	mPlayerAnimationState = mPlayerIdle;
	mPlayerAnimationState->setEnabled(true);
}

void PlayerAnimation::doHeadAnimation () {
	mPlayerAnimationState = mPlayerHead;
	mPlayerAnimationState->setEnabled(true);
	mPlayerAnimationState->setLoop(true);
}

void PlayerAnimation::doRunAnimation () {
	mPlayerAnimationState = mPlayerRun;
	mPlayerAnimationState->setEnabled(true);
	mPlayerAnimationState->setLoop(true);
}

void PlayerAnimation::stopAnimation () {
	doIdleAnimation ();
//	mPlayerAnimationState = NULL;
}

Ogre::AnimationState* PlayerAnimation::getPlayerAnimationState() {return mPlayerAnimationState;}
