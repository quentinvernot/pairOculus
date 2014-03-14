#ifndef __NETWORKMESSAGEPLAYERINPUT_H
#define __NETWORKMESSAGEPLAYERINPUT_H

#include <string>
#include <sstream>
#include "../Player.hpp"
#include "NetworkMessage.hpp"

namespace NetworkMessage{

	class PlayerInput : public NetworkMessage{

		public:
			//methods
			PlayerInput(Player *player);
			PlayerInput(
				std::string nickname,
				double nodeYaw,
				double nodePitch,
				double nodeRoll,
				double nodePositionX,
				double nodePositionY,
				double nodePositionZ,
				bool goingForward,
				bool goingBack,
				bool goingLeft,
				bool goingRight,
				bool goingUp,
				bool goingDown,
				bool puttingBomb
			);
			~PlayerInput();

			std::string getNickname();

			double getNodeYaw();
			double getNodePitch();
			double getNodeRoll();

			double getNodePositionX();
			double getNodePositionY();
			double getNodePositionZ();

			bool getGoingForward();
			bool getGoingBack();
			bool getGoingLeft();
			bool getGoingRight();
			bool getGoingUp();
			bool getGoingDown();

			bool getPuttingBomb();

		private:
			//methods
			void buildSelf();

			//arguments
			std::string mNickname;

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

	};

};

#endif //__NETWORKMESSAGEPLAYERINPUT_H
