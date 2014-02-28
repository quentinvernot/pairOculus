CC=g++
CFLAGS=-Wall -g -pthread
SRCDIR=
OBJDIR=../../obj/
OBJDIRC=../../obj/GameClient/
OBJDIRN=../../obj/NetworkMessage/
LIBDIR=../lib/

LIBBOOST=-lboost_date_time -lboost_system -lboost_thread

all: $(OBJDIRC) $(OBJDIRC)Listener.o
re: clean all

$(OBJDIRC):
	mkdir -p $(OBJDIRC)

DEP=$(OBJDIR)NetworkIO.o $(OBJDIR)NetworkMessage $(OBJDIR)PlayerList.o $(OBJDIR)Map.o 

$(OBJDIRC)Listener.o: $(SRCDIR)Listener.hpp $(SRCDIR)Listener.cpp $(OBJDIRC)Connector.o
	$(CC) $(CFLAGS) -c $(SRCDIR)Listener.cpp -o $(OBJDIRC)Listener.o

$(OBJDIRC)Connector.o: $(SRCDIR)Connector.hpp $(SRCDIR)Connector.cpp $(DEP)
	$(CC) $(CFLAGS) -c $(SRCDIR)Connector.cpp -o $(OBJDIRC)Connector.o

clean:
	rm -rf $(OBJDIRC)
