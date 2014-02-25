CC=g++
CFLAGS=-Wall -g -pthread
SRCDIR=
OBJDIR=../../obj/
OBJDIRN=../../obj/NetworkMessage/
LIBDIR=lib/

LIBBOOST=-lboost_date_time -lboost_system -lboost_thread

all: $(OBJDIRN) $(OBJDIRN)NetworkMessageFactory.o
re: clean all

$(OBJDIRN):
	mkdir -p $(OBJDIRN)

MESSAGEFACTORYOBJ=$(OBJDIRN)Join.o $(OBJDIRN)Leave.o $(OBJDIRN)JoinAccept.o $(OBJDIRN)JoinRefuse.o $(OBJDIRN)PlayerJoined.o $(OBJDIRN)PlayerLeft.o $(OBJDIRN)GameStart.o $(OBJDIRN)GameEnd.o $(OBJDIRN)PlayerInput.o $(OBJDIRN)PlayerKilled.o

$(OBJDIRN)NetworkMessageFactory.o: $(SRCDIR)NetworkMessageFactory.hpp $(SRCDIR)NetworkMessageFactory.cpp $(MESSAGEFACTORYOBJ)
	$(CC) $(CFLAGS) -c $(SRCDIR)NetworkMessageFactory.cpp -o $(OBJDIRN)NetworkMessageFactory.o

$(OBJDIRN)NetworkMessage.o: $(SRCDIR)NetworkMessage.hpp $(SRCDIR)NetworkMessage.cpp
	$(CC) $(CFLAGS) -c $(SRCDIR)NetworkMessage.cpp -o $(OBJDIRN)NetworkMessage.o

$(OBJDIRN)Join.o: $(SRCDIR)Join.hpp $(SRCDIR)Join.cpp $(OBJDIRN)NetworkMessage.o
	$(CC) $(CFLAGS) -c $(SRCDIR)Join.cpp -o $(OBJDIRN)Join.o

$(OBJDIRN)Leave.o: $(SRCDIR)Leave.hpp $(SRCDIR)Leave.cpp $(OBJDIRN)NetworkMessage.o
	$(CC) $(CFLAGS) -c $(SRCDIR)Leave.cpp -o $(OBJDIRN)Leave.o

$(OBJDIRN)JoinAccept.o: $(SRCDIR)JoinAccept.hpp $(SRCDIR)JoinAccept.cpp $(OBJDIRN)NetworkMessage.o
	$(CC) $(CFLAGS) -c $(SRCDIR)JoinAccept.cpp -o $(OBJDIRN)JoinAccept.o

$(OBJDIRN)JoinRefuse.o: $(SRCDIR)JoinRefuse.hpp $(SRCDIR)JoinRefuse.cpp $(OBJDIRN)NetworkMessage.o
	$(CC) $(CFLAGS) -c $(SRCDIR)JoinRefuse.cpp -o $(OBJDIRN)JoinRefuse.o

$(OBJDIRN)PlayerJoined.o: $(SRCDIR)PlayerJoined.hpp $(SRCDIR)PlayerJoined.cpp $(OBJDIRN)NetworkMessage.o
	$(CC) $(CFLAGS) -c $(SRCDIR)PlayerJoined.cpp -o $(OBJDIRN)PlayerJoined.o

$(OBJDIRN)PlayerLeft.o: $(SRCDIR)PlayerLeft.hpp $(SRCDIR)PlayerLeft.cpp $(OBJDIRN)NetworkMessage.o
	$(CC) $(CFLAGS) -c $(SRCDIR)PlayerLeft.cpp -o $(OBJDIRN)PlayerLeft.o

$(OBJDIRN)GameStart.o: $(SRCDIR)GameStart.hpp $(SRCDIR)GameStart.cpp $(OBJDIRN)NetworkMessage.o
	$(CC) $(CFLAGS) -c $(SRCDIR)GameStart.cpp -o $(OBJDIRN)GameStart.o

$(OBJDIRN)GameEnd.o: $(SRCDIR)GameEnd.hpp $(SRCDIR)GameEnd.cpp $(OBJDIRN)NetworkMessage.o
	$(CC) $(CFLAGS) -c $(SRCDIR)GameEnd.cpp -o $(OBJDIRN)GameEnd.o

$(OBJDIRN)PlayerInput.o: $(SRCDIR)PlayerInput.hpp $(SRCDIR)PlayerInput.cpp $(OBJDIRN)NetworkMessage.o
	$(CC) $(CFLAGS) -c $(SRCDIR)PlayerInput.cpp -o $(OBJDIRN)PlayerInput.o

$(OBJDIRN)PlayerKilled.o: $(SRCDIR)PlayerKilled.hpp $(SRCDIR)PlayerKilled.cpp $(OBJDIRN)NetworkMessage.o
	$(CC) $(CFLAGS) -c $(SRCDIR)PlayerKilled.cpp -o $(OBJDIRN)PlayerKilled.o

clean:
	rm -rf $(OBJDIRN)
