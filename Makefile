CC=g++
CFLAGS=-Wall -g -pthread
SRCDIR=src/
OBJDIR=obj/
LIBDIR=lib/
BINDIR=dist/bin/

BOOST=-I/usr/include/boost
OGRE=-I/usr/include/OGRE -I/usr/local/include/OGRE
OIS=-I/usr/include/OIS

LIBBOOST=-lboost_date_time -lboost_serialization -lboost_system -lboost_thread -lboost_wserialization
LIBOGRE=-lGL -lOgreMain -lOIS -lOgreTerrain -lX11 -lXinerama -ludev -lGLU

all: obj $(BINDIR)main $(BINDIR)server $(BINDIR)client
re: clean all

$(OBJDIR):
	mkdir -p $(OBJDIR)

MAINOBJ=$(OBJDIR)Game.o $(OBJDIR)GameWindow.o $(OBJDIR)Input.o $(OBJDIR)Player.o $(OBJDIR)CameraManager.o $(OBJDIR)SimpleCamera.o $(OBJDIR)OculusCamera.o $(OBJDIR)LocalPlayer.o $(OBJDIR)Block.o $(OBJDIR)Cube.o $(OBJDIR)Pyramid.o $(OBJDIR)Map.o $(OBJDIR)LocalMap.o $(OBJDIR)FloorPanel.o $(OBJDIR)BlockFactory.o
$(BINDIR)main: main.cpp $(OBJDIR)Game.o
	$(CC) $(OGRE) $(OIS) $(CFLAGS) main.cpp $(MAINOBJ) $(LIBOGRE) $(LIBBOOST) -o $(BINDIR)main

$(OBJDIR)Game.o: $(SRCDIR)Game.hpp $(SRCDIR)Game.cpp $(OBJDIR)CameraManager.o $(OBJDIR)LocalPlayer.o $(OBJDIR)Input.o $(OBJDIR)GameWindow.o $(OBJDIR)Cube.o $(OBJDIR)Pyramid.o $(OBJDIR)Map.o $(OBJDIR)LocalMap.o
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c $(SRCDIR)Game.cpp -o $(OBJDIR)Game.o

$(OBJDIR)GameWindow.o: $(SRCDIR)GameWindow.hpp $(SRCDIR)GameWindow.cpp $(OBJDIR)CameraManager.o
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c $(SRCDIR)GameWindow.cpp -o $(OBJDIR)GameWindow.o

$(OBJDIR)Input.o: $(SRCDIR)Input.hpp $(SRCDIR)Input.cpp
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c $(SRCDIR)Input.cpp -o $(OBJDIR)Input.o

$(OBJDIR)Player.o: $(SRCDIR)Player.hpp $(SRCDIR)Player.cpp
	$(CC) $(OGRE) $(CFLAGS) -c $(SRCDIR)Player.cpp -o $(OBJDIR)Player.o

$(OBJDIR)CameraManager.o: $(SRCDIR)CameraManager.hpp $(SRCDIR)CameraManager.cpp $(OBJDIR)SimpleCamera.o $(OBJDIR)OculusCamera.o
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c $(SRCDIR)CameraManager.cpp -o $(OBJDIR)CameraManager.o

$(OBJDIR)SimpleCamera.o: $(SRCDIR)SimpleCamera.hpp $(SRCDIR)SimpleCamera.cpp
	$(CC) $(OGRE) $(CFLAGS) -c $(SRCDIR)SimpleCamera.cpp -o $(OBJDIR)SimpleCamera.o

$(OBJDIR)OculusCamera.o: $(SRCDIR)OculusCamera.hpp $(SRCDIR)OculusCamera.cpp
	$(CC) $(OGRE) $(CFLAGS) -c $(SRCDIR)OculusCamera.cpp -o $(OBJDIR)OculusCamera.o

$(OBJDIR)LocalPlayer.o: $(SRCDIR)LocalPlayer.hpp $(SRCDIR)LocalPlayer.cpp $(OBJDIR)Player.o $(OBJDIR)CameraManager.o
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c $(SRCDIR)LocalPlayer.cpp -o $(OBJDIR)LocalPlayer.o

$(OBJDIR)RemotePlayer.o: $(SRCDIR)RemotePlayer.hpp $(SRCDIR)RemotePlayer.cpp $(OBJDIR)Player.o
	$(CC) $(OGRE) $(CFLAGS) -c $(SRCDIR)RemotePlayer.cpp -o $(OBJDIR)RemotePlayer.o

$(OBJDIR)Block.o: $(SRCDIR)Block.hpp $(SRCDIR)Block.cpp
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c $(SRCDIR)Block.cpp -o $(OBJDIR)Block.o

$(OBJDIR)Cube.o: $(SRCDIR)Cube.hpp $(SRCDIR)Cube.cpp $(OBJDIR)Block.o
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c $(SRCDIR)Cube.cpp -o $(OBJDIR)Cube.o

$(OBJDIR)Pyramid.o: $(SRCDIR)Pyramid.hpp $(SRCDIR)Pyramid.cpp $(OBJDIR)Block.o
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c $(SRCDIR)Pyramid.cpp -o $(OBJDIR)Pyramid.o

$(OBJDIR)Map.o: $(SRCDIR)Map.hpp $(SRCDIR)Map.cpp
	$(CC) $(OIS) $(CFLAGS) -c $(SRCDIR)Map.cpp -o $(OBJDIR)Map.o

$(OBJDIR)LocalMap.o: $(SRCDIR)LocalMap.hpp $(SRCDIR)LocalMap.cpp $(OBJDIR)FloorPanel.o $(OBJDIR)BlockFactory.o $(OBJDIR)Map.o
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c $(SRCDIR)LocalMap.cpp -o $(OBJDIR)LocalMap.o

$(OBJDIR)FloorPanel.o: $(SRCDIR)FloorPanel.hpp $(SRCDIR)FloorPanel.cpp
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c $(SRCDIR)FloorPanel.cpp -o $(OBJDIR)FloorPanel.o

$(OBJDIR)BlockFactory.o: $(SRCDIR)BlockFactory.hpp $(SRCDIR)BlockFactory.cpp
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c $(SRCDIR)BlockFactory.cpp -o $(OBJDIR)BlockFactory.o

MESSAGEOBJ=$(OBJDIR)NetworkMessage/NetworkMessageFactory.o $(MESSAGEFACTORYOBJ)
MESSAGEFACTORYOBJ=$(OBJDIR)NetworkMessage/NetworkMessage.o $(OBJDIR)NetworkMessage/Join.o $(OBJDIR)NetworkMessage/Leave.o $(OBJDIR)NetworkMessage/JoinAccept.o $(OBJDIR)NetworkMessage/JoinRefuse.o $(OBJDIR)NetworkMessage/PlayerJoined.o $(OBJDIR)NetworkMessage/PlayerLeft.o $(OBJDIR)NetworkMessage/GameStart.o $(OBJDIR)NetworkMessage/GameEnd.o $(OBJDIR)NetworkMessage/PlayerInput.o $(OBJDIR)NetworkMessage/PlayerKilled.o
SERVEROBJ=$(OBJDIR)GameServer.o $(OBJDIR)GameServerInstance.o $(OBJDIR)GameServerSession.o $(OBJDIR)GameServerSessionList.o $(OBJDIR)Player.o $(OBJDIR)PlayerList.o $(MESSAGEOBJ)
$(BINDIR)server: server.cpp $(OBJDIR)GameServer.o
	$(CC) $(CFLAGS) server.cpp $(SERVEROBJ) $(LIBBOOST) -o $(BINDIR)server

$(OBJDIR)GameServer.o: $(SRCDIR)GameServer.hpp $(SRCDIR)GameServer.cpp $(OBJDIR)GameServerInstance.o
	$(CC) $(CFLAGS) -c $(SRCDIR)GameServer.cpp -o $(OBJDIR)GameServer.o

$(OBJDIR)GameServerInstance.o: $(SRCDIR)GameServerInstance.hpp $(SRCDIR)GameServerInstance.cpp $(OBJDIR)GameServerSession.o $(OBJDIR)GameServerSessionList.o
	$(CC) $(CFLAGS) -c $(SRCDIR)GameServerInstance.cpp -o $(OBJDIR)GameServerInstance.o

$(OBJDIR)GameServerSession.o: $(SRCDIR)GameServerSession.hpp $(SRCDIR)GameServerSession.cpp $(OBJDIR)NetworkMessage $(OBJDIR)PlayerList.o
	$(CC) $(CFLAGS) -c $(SRCDIR)GameServerSession.cpp -o $(OBJDIR)GameServerSession.o

$(OBJDIR)GameServerSessionList.o: $(SRCDIR)GameServerSessionList.hpp $(SRCDIR)GameServerSessionList.cpp $(OBJDIR)GameServerSession.o
	$(CC) $(CFLAGS) -c $(SRCDIR)GameServerSessionList.cpp -o $(OBJDIR)GameServerSessionList.o

CLIENTOBJ=$(OBJDIR)GameClient/GameClient.o $(OBJDIR)GameClient/Listener.o $(OBJDIR)Player.o $(OBJDIR)PlayerList.o $(MESSAGEOBJ)
$(BINDIR)client: client.cpp $(OBJDIR)GameClient
	$(CC) $(CFLAGS) client.cpp $(CLIENTOBJ) $(LIBBOOST) -o $(BINDIR)client

$(OBJDIR)GameClient: .FORCE $(OBJDIR)NetworkMessage $(OBJDIR)Player.o
	cd $(SRCDIR)GameClient/ && make

$(OBJDIR)NetworkMessage: .FORCE $(OBJDIR)Player.o $(OBJDIR)PlayerList.o
	cd $(SRCDIR)NetworkMessage/ && make

clean:
	cd $(SRCDIR)NetworkMessage/ && make clean
	cd $(SRCDIR)GameClient/ && make clean
	rm -rf $(OBJDIR)
	rm -f $(BINDIR)main
	rm -f $(BINDIR)server
	rm -f $(BINDIR)client

.FORCE:
