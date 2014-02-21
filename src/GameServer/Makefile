CC=g++
CFLAGS=-Wall -g -pthread
SRCDIR=
OBJDIR=../../obj/
OBJDIRS=../../obj/GameServer/
OBJDIRN=../../obj/NetworkMessage/
LIBDIR=lib/

LIBBOOST=-lboost_date_time -lboost_serialization -lboost_system -lboost_thread -lboost_wserialization

all: $(OBJDIRS) $(OBJDIRS)GameServer.o
re: clean all

$(OBJDIRS):
	mkdir -p $(OBJDIRS)

MESSAGEOBJ=$(OBJDIRN)NetworkMessageFactory.o $(MESSAGEFACTORYOBJ)
MESSAGEFACTORYOBJ=$(OBJDIRN)NetworkMessage.o $(OBJDIRN)Join.o $(OBJDIRN)Leave.o $(OBJDIRN)JoinAccept.o $(OBJDIRN)JoinRefuse.o $(OBJDIRN)PlayerJoined.o $(OBJDIRN)PlayerLeft.o $(OBJDIRN)GameStart.o $(OBJDIRN)GameEnd.o $(OBJDIRN)PlayerInput.o $(OBJDIRN)PlayerKilled.o

$(OBJDIRS)GameServer.o: $(SRCDIR)GameServer.hpp $(SRCDIR)GameServer.cpp $(OBJDIRS)Instance.o
	$(CC) $(CFLAGS) -c $(SRCDIR)GameServer.cpp -o $(OBJDIRS)GameServer.o

$(OBJDIRS)Instance.o: $(SRCDIR)Instance.hpp $(SRCDIR)Instance.cpp $(OBJDIRS)Session.o $(OBJDIRS)SessionList.o
	$(CC) $(CFLAGS) -c $(SRCDIR)Instance.cpp -o $(OBJDIRS)Instance.o

$(OBJDIRS)Session.o: $(SRCDIR)Session.hpp $(SRCDIR)Session.cpp
	$(CC) $(CFLAGS) -c $(SRCDIR)Session.cpp -o $(OBJDIRS)Session.o

$(OBJDIRS)SessionList.o: $(SRCDIR)SessionList.hpp $(SRCDIR)SessionList.cpp $(OBJDIRS)Session.o
	$(CC) $(CFLAGS) -c $(SRCDIR)SessionList.cpp -o $(OBJDIRS)SessionList.o

clean:
	rm -rf $(OBJDIRS)
