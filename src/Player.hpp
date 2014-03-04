#ifndef __PLAYER_H
#define __PLAYER_H

#include <string>

class Player{

	public:
		//Methods
		Player(std::string name);
		virtual ~Player();

		std::string getNickname();

		double getNodeYaw();
		double getNodePitch();
		double getNodeRoll();

		long getNodePositionX();
		long getNodePositionY();
		long getNodePositionZ();
		void setNodePositionX(long nodePositionX);
		void setNodePositionY(long nodePositionY);
		void setNodePositionZ(long nodePositionZ);

		bool getGoingForward();
		bool getGoingBack();
		bool getGoingLeft();
		bool getGoingRight();
		bool getGoingUp();
		bool getGoingDown();

	protected:
		//Attributes
		std::string mNickname;

		int mTopSpeed;
		int mTopAccel;

		bool mFastMove;

		double mNodeYaw;
		double mNodePitch;
		double mNodeRoll;

		long mNodePositionX;
		long mNodePositionY;
		long mNodePositionZ;

		bool mGoingForward;
		bool mGoingBack;
		bool mGoingLeft;
		bool mGoingRight;
		bool mGoingUp;
		bool mGoingDown;

};

#endif //__PLAYER_H