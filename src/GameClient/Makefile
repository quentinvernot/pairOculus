CC=g++
CFLAGS=-Wall -g -pthread
SRCDIR=
OBJDIR=../../obj/
OBJDIRC=../../obj/GameClient/
OBJDIRN=../../obj/NetworkMessage/
LIBDIR=lib/

LIBBOOST=-lboost_date_time -lboost_serialization -lboost_system -lboost_thread -lboost_wserialization

all: $(OBJDIRC) $(OBJDIRC)GameClient.o
re: clean all

$(OBJDIRC):
	mkdir -p $(OBJDIRC)

MESSAGEOBJ=$(OBJDIRN)NetworkMessageFactory.o $(MESSAGEFACTORYOBJ)
MESSAGEFACTORYOBJ=$(OBJDIRN)NetworkMessage.o $(OBJDIRN)Join.o $(OBJDIRN)Leave.o $(OBJDIRN)JoinAccept.o $(OBJDIRN)JoinRefuse.o $(OBJDIRN)PlayerJoined.o $(OBJDIRN)PlayerLeft.o $(OBJDIRN)GameStart.o $(OBJDIRN)GameEnd.o $(OBJDIRN)PlayerInput.o $(OBJDIRN)PlayerKilled.o

$(OBJDIRC)GameClient.o: $(SRCDIR)GameClient.hpp $(SRCDIR)GameClient.cpp $(OBJDIRC)Listener.o $(MESSAGEOBJ)
	$(CC) $(CFLAGS) -c $(SRCDIR)GameClient.cpp -o $(OBJDIRC)GameClient.o

$(OBJDIRC)Listener.o: $(SRCDIR)Listener.hpp $(SRCDIR)Listener.cpp
	$(CC) $(CFLAGS) -c $(SRCDIR)Listener.cpp -o $(OBJDIRC)Listener.o

clean:
	rm -rf $(OBJDIRC)
