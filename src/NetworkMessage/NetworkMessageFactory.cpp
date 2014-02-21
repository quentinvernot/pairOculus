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

		double x, y, z;
		PlayerList playerList;

		int type = atoi(parts[0].c_str());

		switch(type){
			case JOIN:
				return new Join(parts[2]);
			case LEAVE:
				return new Leave();
			case JOINACCEPT:
				for(unsigned int i = 0; i < (parts.size()-2)/4; i++){

					playerList.addPlayer(new Player(parts[4*i+2]));
					x = atoi(parts[4*i+3].c_str());
					y = atoi(parts[4*i+4].c_str());
					z = atoi(parts[4*i+5].c_str());

					playerList[i]->setNodePositionX(x);
					playerList[i]->setNodePositionY(y);
					playerList[i]->setNodePositionZ(z);

				}

				return new JoinAccept(&playerList);
			case JOINREFUSE:
				return new JoinRefuse(parts[2]);
			case PLAYERJOINED:
				x = atoi(parts[3].c_str());
				y = atoi(parts[4].c_str());
				z = atoi(parts[5].c_str());
				return new PlayerJoined(parts[2], x, y, z);
			case PLAYERLEFT:
				return new PlayerLeft(parts[2]);
			case GAMESTART:
				return new GameStart();
			case GAMEEND:
				return new GameEnd();
			case PLAYERINPUT:
				return new PlayerInput();
			case PLAYERKILLED:
				return new PlayerKilled();
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
			default:
				break;
		}
		
		return 0;

	}

	NetworkMessage *NetworkMessageFactory::buildMessage(
		MessageType type,
		PlayerList *playerList
	){

		switch(type){
			case JOINACCEPT:
				return new JoinAccept(playerList);
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
