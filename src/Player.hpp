#ifndef __PLAYER_H
#define __PLAYER_H

#include <string>

class Player{

	public:
		//Methods
		Player(std::string nickname);
		virtual ~Player();

		std::string getNickname();

		double getNodeYaw();
		double getNodePitch();
		double getNodeRoll();

		virtual double getNodePositionX();
		virtual double getNodePositionY();
		virtual double getNodePositionZ();
		virtual void setNodePositionX(double nodePositionX);
		virtual void setNodePositionY(double nodePositionY);
		virtual void setNodePositionZ(double nodePositionZ);

		bool getGoingForward();
		bool getGoingBack();
		bool getGoingLeft();
		bool getGoingRight();
		bool getGoingUp();
		bool getGoingDown();

		bool getPuttingBomb();

		virtual void die();

	protected:
		//Attributes
		std::string mNickname;

		int mTopSpeed;
		int mTopAccel;

		bool mFastMove;

		double mNodeYaw;
		double mNodePitch;
		double mNodeRoll;

		double mNodePositionX;
		double mNodePositionY;
		double mNodePositionZ;

		bool mGoingForward;
		bool mGoingBack;
		bool mGoingLeft;
		bool mGoingRight;
		bool mGoingUp;
		bool mGoingDown;

		bool mPuttingBomb;

		bool mIsDead;

};

#endif //__PLAYER_H
