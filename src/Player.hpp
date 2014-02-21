#ifndef __PLAYER_H
#define __PLAYER_H

#include <string>

class Player{

	public:
		Player(std::string name);

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
		//Methods
		
		//Attributes
		std::string mName;

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
