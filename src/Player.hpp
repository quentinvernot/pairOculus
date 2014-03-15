#ifndef __PLAYER_H
#define __PLAYER_H

#include <string>

class Player{

	public:
		//Methods
		Player(std::string nickname);
		virtual ~Player();

		std::string getNickname();

		double getYaw();
		double getPitch();
		double getRoll();

		virtual double getX();
		virtual double getY();
		virtual double getZ();
		virtual void setX(double x);
		virtual void setY(double y);
		virtual void setZ(double z);
		virtual void setStartingPosition(double x, double y, double z);

		bool getGoingForward();
		bool getGoingBack();
		bool getGoingLeft();
		bool getGoingRight();
		bool getGoingUp();
		bool getGoingDown();

		bool getPuttingBomb();

		virtual void win();
		virtual bool hasWon();
		virtual void die();
		virtual bool isDead();

	protected:
		//Attributes
		std::string mNickname;

		int mTopSpeed;
		int mTopAccel;

		bool mFastMove;

		double mYaw;
		double mPitch;
		double mRoll;

		double mX;
		double mY;
		double mZ;
		double mStartingX;
		double mStartingY;
		double mStartingZ;

		bool mGoingForward;
		bool mGoingBack;
		bool mGoingLeft;
		bool mGoingRight;
		bool mGoingUp;
		bool mGoingDown;

		bool mPuttingBomb;

		bool mHasWon;
		bool mIsDead;

};

#endif //__PLAYER_H
