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

$(OBJDIRC)GameClient.o: $(SRCDIR)GameClient.hpp $(SRCDIR)GameClient.cpp $(OBJDIRC)Listener.o
	$(CC) $(CFLAGS) -c $(SRCDIR)GameClient.cpp -o $(OBJDIRC)GameClient.o

$(OBJDIRC)Listener.o: $(SRCDIR)Listener.hpp $(SRCDIR)Listener.cpp $(OBJDIRN)*.o $(OBJDIR)NetworkIO.o
	$(CC) $(CFLAGS) -c $(SRCDIR)Listener.cpp -o $(OBJDIRC)Listener.o

clean:
	rm -rf $(OBJDIRC)
