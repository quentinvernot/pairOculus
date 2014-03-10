CC=g++
CFLAGS=-Wall -g -pthread
SRCDIR=src/
OBJDIR=obj/
LIBDIR=lib/
BINDIR=dist/bin/

BOOST=-I/usr/include/boost
OGRE=`pkg-config --cflags OGRE`
OIS=-I/usr/include/OIS
BULLET=`pkg-config --cflags bullet` -I/usr/local/include/OgreBullet/Dynamics  -I/usr/local/include/OgreBullet/Collisions

LIBBOOST=-lboost_date_time -lboost_system -lboost_thread
LIBOGRE=-lGL -lOgreMain -lOIS -lOgreTerrain -lX11 -lXinerama -ludev -lGLU
LIBBULLET=`pkg-config --libs bullet` /usr/local/lib/libOgreBulletDynamics.a /usr/local/lib/libOgreBulletCollisions.a

all: $(OBJDIR) $(BINDIR)main $(BINDIR)server $(BINDIR)client
re: clean all

$(OBJDIR):
	mkdir -p $(OBJDIR)

MAINOBJ=$(OBJDIR)Game.o $(OBJDIR)GameWindow.o $(OBJDIR)Input.o $(OBJDIR)CameraManager.o $(OBJDIR)SimpleCamera.o $(OBJDIR)OculusCamera.o $(OBJDIR)PlayerAnimation.o $(OBJDIR)LocalPlayer.o $(OBJDIR)LocalPlayerList.o $(OBJDIR)Block.o $(OBJDIR)Cube.o $(OBJDIR)Pyramid.o $(OBJDIR)Map.o $(OBJDIR)LocalMap.o $(OBJDIR)FloorPanel.o $(OBJDIR)BlockFactory.o $(CLIENTOBJ)
$(BINDIR)main: main.cpp $(OBJDIR)Game.o
	$(CC) $(OGRE) $(OIS) $(BULLET) $(CFLAGS) main.cpp $(MAINOBJ) $(LIBOGRE) $(LIBBOOST) $(LIBBULLET) -o $(BINDIR)main

$(OBJDIR)Game.o: $(SRCDIR)Game.hpp $(SRCDIR)Game.cpp $(OBJDIR)CameraManager.o $(OBJDIR)PlayerList.o $(OBJDIR)LocalPlayerList.o $(OBJDIR)Input.o $(OBJDIR)GameWindow.o $(OBJDIR)Cube.o $(OBJDIR)Pyramid.o $(OBJDIR)LocalMap.o $(OBJDIR)GameClient
	$(CC) $(OGRE) $(OIS)  $(BULLET) $(CFLAGS) -c $(SRCDIR)Game.cpp -o $(OBJDIR)Game.o

$(OBJDIR)GameWindow.o: $(SRCDIR)GameWindow.hpp $(SRCDIR)GameWindow.cpp $(OBJDIR)CameraManager.o
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c $(SRCDIR)GameWindow.cpp -o $(OBJDIR)GameWindow.o

$(OBJDIR)Input.o: $(SRCDIR)Input.hpp $(SRCDIR)Input.cpp
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c $(SRCDIR)Input.cpp -o $(OBJDIR)Input.o

$(OBJDIR)Player.o: $(SRCDIR)Player.hpp $(SRCDIR)Player.cpp
	$(CC) $(CFLAGS) -c $(SRCDIR)Player.cpp -o $(OBJDIR)Player.o

$(OBJDIR)PlayerList.o: $(SRCDIR)PlayerList.hpp $(SRCDIR)PlayerList.cpp $(OBJDIR)Player.o
	$(CC) $(CFLAGS) -c $(SRCDIR)PlayerList.cpp -o $(OBJDIR)PlayerList.o

$(OBJDIR)CameraManager.o: $(SRCDIR)CameraManager.hpp $(SRCDIR)CameraManager.cpp $(OBJDIR)SimpleCamera.o $(OBJDIR)OculusCamera.o
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c $(SRCDIR)CameraManager.cpp -o $(OBJDIR)CameraManager.o

$(OBJDIR)SimpleCamera.o: $(SRCDIR)SimpleCamera.hpp $(SRCDIR)SimpleCamera.cpp
	$(CC) $(OGRE) $(CFLAGS) -c $(SRCDIR)SimpleCamera.cpp -o $(OBJDIR)SimpleCamera.o

$(OBJDIR)OculusCamera.o: $(SRCDIR)OculusCamera.hpp $(SRCDIR)OculusCamera.cpp
	$(CC) $(OGRE) $(CFLAGS) -c $(SRCDIR)OculusCamera.cpp -o $(OBJDIR)OculusCamera.o

$(OBJDIR)PlayerAnimation.o: $(SRCDIR)PlayerAnimation.hpp $(SRCDIR)PlayerAnimation.cpp
	$(CC) $(OGRE) $(CFLAGS) -c $(SRCDIR)PlayerAnimation.cpp -o $(OBJDIR)PlayerAnimation.o

$(OBJDIR)LocalPlayer.o: $(SRCDIR)LocalPlayer.hpp $(SRCDIR)LocalPlayer.cpp $(OBJDIR)Player.o $(OBJDIR)CameraManager.o $(OBJDIR)PlayerAnimation.o $(OBJDIR)NetworkMessage
	$(CC) $(OGRE) $(OIS) $(BULLET) $(CFLAGS) -c $(SRCDIR)LocalPlayer.cpp -o $(OBJDIR)LocalPlayer.o

$(OBJDIR)LocalPlayerList.o: $(SRCDIR)LocalPlayerList.hpp $(SRCDIR)LocalPlayerList.cpp $(OBJDIR)LocalPlayer.o
	$(CC) $(OGRE) $(OIS) $(BULLET) $(CFLAGS) -c $(SRCDIR)LocalPlayerList.cpp -o $(OBJDIR)LocalPlayerList.o

$(OBJDIR)Block.o: $(SRCDIR)Block.hpp $(SRCDIR)Block.cpp
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c $(SRCDIR)Block.cpp -o $(OBJDIR)Block.o

$(OBJDIR)Cube.o: $(SRCDIR)Cube.hpp $(SRCDIR)Cube.cpp $(OBJDIR)Block.o
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c $(SRCDIR)Cube.cpp -o $(OBJDIR)Cube.o

$(OBJDIR)Pyramid.o: $(SRCDIR)Pyramid.hpp $(SRCDIR)Pyramid.cpp $(OBJDIR)Block.o
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c $(SRCDIR)Pyramid.cpp -o $(OBJDIR)Pyramid.o

$(OBJDIR)Map.o: $(SRCDIR)Map.hpp $(SRCDIR)Map.cpp $(OBJDIR)Player.o
	$(CC) $(OIS) $(CFLAGS) -c $(SRCDIR)Map.cpp -o $(OBJDIR)Map.o

$(OBJDIR)LocalMap.o: $(SRCDIR)LocalMap.hpp $(SRCDIR)LocalMap.cpp $(OBJDIR)FloorPanel.o $(OBJDIR)BlockFactory.o $(OBJDIR)Map.o
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c $(SRCDIR)LocalMap.cpp -o $(OBJDIR)LocalMap.o

$(OBJDIR)FloorPanel.o: $(SRCDIR)FloorPanel.hpp $(SRCDIR)FloorPanel.cpp
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c $(SRCDIR)FloorPanel.cpp -o $(OBJDIR)FloorPanel.o

$(OBJDIR)BlockFactory.o: $(SRCDIR)BlockFactory.hpp $(SRCDIR)BlockFactory.cpp
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c $(SRCDIR)BlockFactory.cpp -o $(OBJDIR)BlockFactory.o

$(OBJDIR)NetworkIO.o: $(SRCDIR)NetworkIO.hpp $(SRCDIR)NetworkIO.cpp $(OBJDIR)NetworkMessage
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c $(SRCDIR)NetworkIO.cpp -o $(OBJDIR)NetworkIO.o

SERVEROBJ=$(OBJDIR)NetworkIO.o $(OBJDIR)NetworkMessage/*.o $(OBJDIR)GameServer/*.o $(OBJDIR)Player.o $(OBJDIR)PlayerList.o $(OBJDIR)Map.o
$(BINDIR)server: server.cpp $(OBJDIR)GameServer
	$(CC) $(CFLAGS) server.cpp $(SERVEROBJ) $(LIBBOOST) -o $(BINDIR)server

$(OBJDIR)GameServer: $(OBJDIR)NetworkIO.o .FORCE
	cd $(SRCDIR)GameServer/ && make

CLIENTOBJ=$(OBJDIR)NetworkIO.o $(OBJDIR)NetworkMessage/*.o $(OBJDIR)GameClient/*.o $(OBJDIR)Player.o $(OBJDIR)PlayerList.o
$(BINDIR)client: client.cpp $(OBJDIR)GameClient
	$(CC) $(CFLAGS) client.cpp $(CLIENTOBJ) $(LIBBOOST) -o $(BINDIR)client

$(OBJDIR)GameClient: $(OBJDIR)NetworkMessage $(OBJDIR)NetworkIO.o .FORCE
	cd $(SRCDIR)GameClient/ && make

$(OBJDIR)NetworkMessage: .FORCE
	cd $(SRCDIR)NetworkMessage/ && make

clean:
	cd $(SRCDIR)NetworkMessage/ && make clean
	cd $(SRCDIR)GameServer/ && make clean
	cd $(SRCDIR)GameClient/ && make clean
	rm -rf $(OBJDIR)
	rm -f $(BINDIR)main
	rm -f $(BINDIR)server
	rm -f $(BINDIR)client

.FORCE:
