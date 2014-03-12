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
LIBOGRE=-lGL -lOgreMain -lOIS -lX11 -lXinerama -ludev -lGLU
LIBBULLET=`pkg-config --libs bullet` /usr/local/lib/libOgreBulletDynamics.a /usr/local/lib/libOgreBulletCollisions.a

all: $(OBJDIR) $(BINDIR)main $(BINDIR)server
re: clean all

$(OBJDIR): .FORCE
	cd $(SRCDIR) && make

$(OBJDIR)GameServer: $(OBJDIR)
$(OBJDIR)GameClient: $(OBJDIR)

MAINOBJ=$(OBJDIR)*.o $(OBJDIR)NetworkMessage/*.o $(OBJDIR)GameClient/*.o
$(BINDIR)main: main.cpp $(OBJDIR)
	$(CC) $(OGRE) $(OIS) $(BULLET) $(CFLAGS) main.cpp $(MAINOBJ) $(LIBOGRE) $(LIBBOOST) $(LIBBULLET) -o $(BINDIR)main

SERVEROBJ=$(OBJDIR)NetworkIO.o $(OBJDIR)NetworkMessage/*.o $(OBJDIR)GameServer/*.o $(OBJDIR)Player.o $(OBJDIR)PlayerList.o $(OBJDIR)Map.o
$(BINDIR)server: server.cpp $(OBJDIR)GameServer
	$(CC) $(CFLAGS) server.cpp $(SERVEROBJ) $(LIBBOOST) -o $(BINDIR)server

clean:
	cd $(SRCDIR) && make clean
	rm -f $(BINDIR)main
	rm -f $(BINDIR)server

.FORCE:
