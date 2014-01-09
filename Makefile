CC=g++
CFLAGS=-Wall -g
SRCDIR=src/
OBJDIR=obj/
LIBDIR=lib/
BINDIR=dist/bin/

OGRE=-I/usr/include/OGRE -I/usr/local/include/OGRE
OIS=-I/usr/include/OIS
LIBS=-pthread -lGL -lOgreMain -lOIS -lOgreTerrain -lX11 -lXinerama -ludev -lGLU 

all: $(BINDIR)main
main: $(BINDIR)main
re: clean all

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

$(OBJDIR)OculusCameraMan.o: $(SRCDIR)OculusCameraMan.hpp $(SRCDIR)OculusCameraMan.cpp
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c $(SRCDIR)OculusCameraMan.cpp -o $(OBJDIR)OculusCameraMan.o

$(OBJDIR)LocalPlayer.o: $(SRCDIR)LocalPlayer.hpp $(SRCDIR)LocalPlayer.cpp $(OBJDIR)Player.o $(OBJDIR)CameraManager.o
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c $(SRCDIR)LocalPlayer.cpp -o $(OBJDIR)LocalPlayer.o

$(OBJDIR)RemotePlayer.o: $(SRCDIR)RemotePlayer.hpp $(SRCDIR)RemotePlayer.cpp $(OBJDIR)Player.o
	$(CC) $(OGRE) $(CFLAGS) -c $(SRCDIR)RemotePlayer.cpp -o $(OBJDIR)RemotePlayer.o

$(BINDIR)main: main.cpp $(OBJDIR)Game.o
	$(CC) $(OGRE) $(OIS) $(CFLAGS) main.cpp $(OBJDIR)*.o $(LIBS) -o $(BINDIR)main

clean:
	rm -f $(OBJDIR)*.o
	rm -f main
