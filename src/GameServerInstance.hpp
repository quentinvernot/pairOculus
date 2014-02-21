#ifndef __GAMESERVERINSTANCE_H
#define __GAMESERVERINSTANCE_H

#include "GameServerSession.hpp"
#include "GameServerSessionList.hpp"
#include "PlayerList.hpp"

#include <iostream>
#include <deque>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class GameServerInstance{

	public:
		//Methods
		GameServerInstance(
			unsigned short port,
			boost::asio::io_service& io_service
		);
		~GameServerInstance();

		void start();
		void handleAccept(
			GameServerSession *gss,
			const boost::system::error_code& error
		);
		void handleReceive(
			NetworkMessage::NetworkMessage *message,
			GameServerSession *sourceSession
		);

	private:
		//Methods
		void onJoin(
			NetworkMessage::Join *message,
			GameServerSession *sourceSession
		);
		void onLeave(
			NetworkMessage::Leave *message,
			GameServerSession *sourceSession
		);
		void onJoinAccept(
			NetworkMessage::JoinAccept *message,
			GameServerSession *sourceSession
		);
		void onJoinRefuse(
			NetworkMessage::JoinRefuse *message,
			GameServerSession *sourceSession
		);
		void onPlayerJoined(
			NetworkMessage::PlayerJoined *message,
			GameServerSession *sourceSession
		);
		void onPlayerLeft(
			NetworkMessage::PlayerLeft *message,
			GameServerSession *sourceSession
		);
		void onGameStart(
			NetworkMessage::GameStart *message,
			GameServerSession *sourceSession
		);
		void onGameEnd(
			NetworkMessage::GameEnd *message,
			GameServerSession *sourceSession
		);
		void onPlayerInput(
			NetworkMessage::PlayerInput *message,
			GameServerSession *sourceSession
		);
		void onPlayerKilled(
			NetworkMessage::PlayerKilled *message,
			GameServerSession *sourceSession
		);

		//Attributes
		boost::asio::io_service& mIo_service;
		tcp::acceptor mAcceptor;
		GameServerSession *mGameServerSession;
		GameServerSessionList *mSessionList;
		PlayerList *mPlayerList;
		NetworkMessage::NetworkMessageFactory *mNMFactory;

};

#endif //__GAMESERVERINSTANCE_H
