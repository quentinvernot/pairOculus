/*
This source file is part of pairOculus, a student project aiming at creating a
simple 3D multiplayer game for the Oculus Rift.

Repository can be found here : https://github.com/Target6/pairOculus 

Copyright (c) 2013 Target6

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef __PLAYER_HPP
#define __PLAYER_HPP

#include <string>

/** Abstract representation of a Player.
 * 	Stores the player's nickname, coordinates, starting coordinates,
 * 	maximum speed and acceleration, direction in which it is moving	and
 * 	status.
 */
class Player{

	public:
		//Methods	
		/// Constructor.
		Player(std::string nickname);
		/// Default destructor.
		virtual ~Player();

		/// Gets the player's nickname.
		std::string getNickname();

		/// Gets the body's yaw.
		double getYaw();
		/// Gets the body's pitch.
		double getPitch();
		/// Gets the body's roll.
		double getRoll();

		/// Gets the body's position on the X axis.
		virtual double getX();
		/// Gets the body's position on the Y axis.
		virtual double getY();
		/// Gets the body's position on the Z axis.
		virtual double getZ();
		/// Sets the body's position on the X axis.
		virtual void setX(double x);
		/// Sets the body's position on the Y axis.
		virtual void setY(double y);
		/// Sets the body's position on the Z axis.
		virtual void setZ(double z);
		/** Gets the player's starting position.
		 *  \remarks 
		 * 		The starting position is stored and can be used be children
		 *  	classes.
		 */
		virtual void setStartingPosition(double x, double y, double z);

		/// Gets the flag indicating that the player is moving forward.
		bool getGoingForward();
		/// Gets the flag indicating that the player is moving back.
		bool getGoingBack();
		/// Gets the flag indicating that the player is moving left.
		bool getGoingLeft();
		/// Gets the flag indicating that the player is moving right.
		bool getGoingRight();
		/// Gets the flag indicating that the player is moving up.
		bool getGoingUp();
		/// Gets the flag indicating that the player is moving down.
		bool getGoingDown();

		/// Gets the flag indicating that the player is placing a bomb.
		bool getPuttingBomb();

		/// Sets the player as the winner.
		virtual void win();
		/// Gets the flag indicating if the player has won or not.
		virtual bool hasWon();
		/// Sets the player as dead.
		virtual void die();
		/// Gets the flag indicating if the player has died or not.
		virtual bool isDead();

	protected:
		//Attributes
		/// The player's nickname.
		std::string mNickname;

		/// The player's maximum speed without outside forces (such as gravity).
		int mTopSpeed;
		/// The player's maximum acceleration without outside forces.
		int mTopAccel;

		/// Flag indicating if the player is moving fast (e.g. running).
		bool mFastMove;

		/// The player's body's yaw.
		double mYaw;
		/// The player's body's pitch.
		double mPitch;
		/// The player's body's roll.
		double mRoll;

		/// The player's body's position on the X axis.
		double mX;
		/// The player's body's position on the Y axis.
		double mY;
		/// The player's body's position on the Z axis.
		double mZ;
		/// The player's body's starting position on the X axis.
		double mStartingX;
		/// The player's body's starting position on the Y axis.
		double mStartingY;
		/// The player's body's starting position on the Z axis.
		double mStartingZ;

		/// Flag indicating whether the player tries to move forward or not.
		bool mGoingForward;
		/// Flag indicating whether the player tries to move back or not.
		bool mGoingBack;
		/// Flag indicating whether the player tries to move left or not.
		bool mGoingLeft;
		/// Flag indicating whether the player tries to move right or not.
		bool mGoingRight;
		/// Flag indicating whether the player tries to move up or not.
		bool mGoingUp;
		/// Flag indicating whether the player tries to move down or not.
		bool mGoingDown;

		/// Flag indicating whether the player is placing a bomb or not.
		bool mPuttingBomb;

		/// Flag indicating whether the player has won or not.
		bool mHasWon;
		/// Flag indicating whether the player is dead or not.
		bool mIsDead;

};

#endif //__PLAYER_HPP
