#include "NetworkMessageFactory.hpp"

namespace NetworkMessage{

	NetworkMessageFactory::NetworkMessageFactory(){
	}

	NetworkMessageFactory::~NetworkMessageFactory(){
	}

	NetworkMessage *NetworkMessageFactory::buildMessage(
		std::string data
	){

		std::deque<std::string> parts;
		std::istringstream buf(data);
		for(std::string token = ""; getline(buf, token, '\n'); )
			parts.push_back(token);

		unsigned int j = 0;
		double x, y, z;
		PlayerList playerList;

		int type = atoi(parts[0].c_str());

		switch(type){
			case JOIN:
				return buildMessage(JOIN, parts[2]);
			case LEAVE:
				return buildMessage(LEAVE);
			case JOINACCEPT:
				for(; j < (parts.size()-2)/4; j++){

					playerList.addPlayer(new Player(parts[4*j+2]));
					x = atof(parts[4*j+3].c_str());
					y = atof(parts[4*j+4].c_str());
					z = atof(parts[4*j+5].c_str());

					playerList[j]->setNodePositionX(x);
					playerList[j]->setNodePositionY(y);
					playerList[j]->setNodePositionZ(z);

				}

				return buildMessage(
					JOINACCEPT,
					&playerList,
					atoi(parts[parts.size()-3].c_str()),
					atoi(parts[parts.size()-2].c_str()),
					atoi(parts[parts.size()-1].c_str())
				);
			case JOINREFUSE:
				return buildMessage(JOINREFUSE, parts[2]);
			case PLAYERJOINED:
				x = atoi(parts[3].c_str());
				y = atoi(parts[4].c_str());
				z = atoi(parts[5].c_str());
				return buildMessage(PLAYERJOINED, parts[2], x, y, z);
			case PLAYERLEFT:
				return buildMessage(PLAYERLEFT, parts[2]);
			case GAMESTART:
				return buildMessage(GAMESTART);
			case GAMEEND:
				return buildMessage(GAMEEND);
			case PLAYERINPUT:
				return buildMessage(
					PLAYERINPUT,
					parts[2],
					atof(parts[3].c_str()),
					atof(parts[4].c_str()),
					atof(parts[5].c_str()),
					atoi(parts[6].c_str()),
					atoi(parts[7].c_str()),
					atoi(parts[8].c_str()),
					atoi(parts[9].c_str()),
					atoi(parts[10].c_str()),
					atoi(parts[11].c_str()),
					atoi(parts[12].c_str()),
					atoi(parts[13].c_str()),
					atoi(parts[14].c_str()),
					atoi(parts[15].c_str())
				);
			case PLAYERKILLED:
				return buildMessage(PLAYERKILLED);
			default:
				break;
		}

		return 0;

	}

	NetworkMessage *NetworkMessageFactory::buildMessage(
		MessageType type
	){

		switch(type){
			case LEAVE:
				return new Leave();
			case GAMESTART:
				return new GameStart();
			case GAMEEND:
				return new GameEnd();
			default:
				break;
		}

		return 0;

	}

	NetworkMessage *NetworkMessageFactory::buildMessage(
		MessageType type,
		std::string data
	){

		switch(type){
			case JOIN:
				return new Join(data);
			case JOINREFUSE:
				return new JoinRefuse(data);
			case PLAYERLEFT:
				return new PlayerLeft(data);
			default:
				break;
		}

		return 0;

	}

	NetworkMessage *NetworkMessageFactory::buildMessage(
		MessageType type,
		std::string data,
		long x,
		long y,
		long z
	){

		switch(type){
			case PLAYERJOINED:
				return new PlayerJoined(data, x, y, z);
			default:
				break;
		}

		return 0;

	}

	NetworkMessage *NetworkMessageFactory::buildMessage(
		MessageType type,
		Player *player
	){

		switch(type){
			case PLAYERJOINED:
				return new PlayerJoined(player);
			case PLAYERINPUT:
				return new PlayerInput(player);
			default:
				break;
		}

		return 0;

	}

	NetworkMessage *NetworkMessageFactory::buildMessage(
		MessageType type,
		PlayerList *playerList,
		unsigned int mapHeight,
		unsigned int mapWidth,
		time_t seed
	){

		switch(type){
			case JOINACCEPT:
				return new JoinAccept(playerList, mapHeight, mapWidth, seed);
			default:
				break;
		}

		return 0;

	}

	NetworkMessage *NetworkMessageFactory::buildMessage(
		MessageType type,
		std::string nickname,
		double nodeYaw,
		double nodePitch,
		double nodeRoll,
		long nodePositionX,
		long nodePositionY,
		long nodePositionZ,
		bool goingForward,
		bool goingBack,
		bool goingLeft,
		bool goingRight,
		bool goingUp,
		bool goingDown,
		bool puttingBomb
	){

		switch(type){
			case PLAYERINPUT:
				return new PlayerInput(
					nickname,
					nodeYaw,
					nodePitch,
					nodeRoll,
					nodePositionX,
					nodePositionY,
					nodePositionZ,
					goingForward,
					goingBack,
					goingLeft,
					goingRight,
					goingUp,
					goingDown,
					puttingBomb
				);
			default:
				break;
		}

		return 0;

	}

	int NetworkMessageFactory::getLengthFromHeader(std::string header){

		std::istringstream buf(header);
		std::string token;
		getline(buf, token);
		getline(buf, token);

		if(token == "")
			return -1;

		return atoi(token.c_str());

	}

};
