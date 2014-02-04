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

all: obj $(BINDIR)main $(BINDIR)server
re: clean all

obj:
	mkdir -p obj

$(OBJDIR)Game.o: $(SRCDIR)Game.hpp $(SRCDIR)Game.cpp $(OBJDIR)CameraManager.o $(OBJDIR)LocalPlayer.o $(OBJDIR)Input.o $(OBJDIR)GameWindow.o
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

MAINOBJ=$(OBJDIR)Game.o $(OBJDIR)GameWindow.o $(OBJDIR)Input.o $(OBJDIR)Player.o $(OBJDIR)CameraManager.o $(OBJDIR)SimpleCamera.o $(OBJDIR)OculusCamera.o $(OBJDIR)LocalPlayer.o
$(BINDIR)main: main.cpp $(OBJDIR)Game.o
	$(CC) $(OGRE) $(OIS) $(CFLAGS) main.cpp $(MAINOBJ) $(LIBOGRE) -o $(BINDIR)main

$(OBJDIR)GameServer.o: $(SRCDIR)GameServer.hpp $(SRCDIR)GameServer.cpp $(OBJDIR)GameServerInstance.o
	$(CC) $(OGRE) $(CFLAGS) -c $(SRCDIR)GameServer.cpp -o $(OBJDIR)GameServer.o

$(OBJDIR)GameServerInstance.o: $(SRCDIR)GameServerInstance.hpp $(SRCDIR)GameServerInstance.cpp $(OBJDIR)GameSession.o
	$(CC) $(OGRE) $(CFLAGS) -c $(SRCDIR)GameServerInstance.cpp -o $(OBJDIR)GameServerInstance.o

$(OBJDIR)GameSession.o: $(SRCDIR)GameSession.hpp $(SRCDIR)GameSession.cpp
	$(CC) $(OGRE) $(CFLAGS) -c $(SRCDIR)GameSession.cpp -o $(OBJDIR)GameSession.o

SERVEROBJ=$(OBJDIR)GameServer.o $(OBJDIR)GameServerInstance.o $(OBJDIR)GameSession.o
$(BINDIR)server: server.cpp $(OBJDIR)GameServer.o
	$(CC) $(CFLAGS) server.cpp $(SERVEROBJ) $(LIBBOOST) -o $(BINDIR)server

clean:
	rm -f $(OBJDIR)*.o
	rm -f main
	rm -f server
