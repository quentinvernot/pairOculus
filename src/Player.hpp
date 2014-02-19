#ifndef __PLAYER_H
#define __PLAYER_H

#include <string>

class Player{

	public:
		Player(std::string name);

	protected:
		//Methods
		std::string getName();
		
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
