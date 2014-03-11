CC=g++
CFLAGS=-Wall -g -pthread
SRCDIR=../
OBJDIR=../../obj/
OBJDIRN=../../obj/NetworkMessage/
LIBDIR=lib/

BASE=$(OBJDIRN)NetworkMessage.o
SESSION=$(OBJDIRN)Join.o $(OBJDIRN)Leave.o $(OBJDIRN)JoinAccept.o $(OBJDIRN)JoinRefuse.o $(OBJDIRN)PlayerJoined.o $(OBJDIRN)PlayerLeft.o
GAME=$(OBJDIRN)GameStart.o $(OBJDIRN)GameEnd.o $(OBJDIRN)PlayerInput.o $(OBJDIRN)PlayerKilled.o
FACTORY=$(OBJDIRN)NetworkMessageFactory.o
all: $(OBJDIRN) $(BASE) $(SESSION) $(GAME) $(FACTORY)
re: clean all

$(OBJDIRN):
	mkdir -p $(OBJDIRN)


$(OBJDIRN)NetworkMessageFactory.o: NetworkMessageFactory.hpp NetworkMessageFactory.cpp $(shell ls ./*.hpp)
	$(CC) $(CFLAGS) -c NetworkMessageFactory.cpp -o $(OBJDIRN)NetworkMessageFactory.o

$(OBJDIRN)NetworkMessage.o: NetworkMessage.hpp NetworkMessage.cpp
	$(CC) $(CFLAGS) -c NetworkMessage.cpp -o $(OBJDIRN)NetworkMessage.o

$(OBJDIRN)Join.o: Join.hpp Join.cpp NetworkMessage.hpp
	$(CC) $(CFLAGS) -c Join.cpp -o $(OBJDIRN)Join.o

$(OBJDIRN)Leave.o: Leave.hpp Leave.cpp NetworkMessage.hpp
	$(CC) $(CFLAGS) -c Leave.cpp -o $(OBJDIRN)Leave.o

$(OBJDIRN)JoinAccept.o: JoinAccept.hpp JoinAccept.cpp NetworkMessage.hpp $(SRCDIR)PlayerList.hpp $(SRCDIR)Map.hpp
	$(CC) $(CFLAGS) -c JoinAccept.cpp -o $(OBJDIRN)JoinAccept.o

$(OBJDIRN)JoinRefuse.o: JoinRefuse.hpp JoinRefuse.cpp NetworkMessage.hpp
	$(CC) $(CFLAGS) -c JoinRefuse.cpp -o $(OBJDIRN)JoinRefuse.o

$(OBJDIRN)PlayerJoined.o: PlayerJoined.hpp PlayerJoined.cpp NetworkMessage.hpp $(SRCDIR)Player.hpp
	$(CC) $(CFLAGS) -c PlayerJoined.cpp -o $(OBJDIRN)PlayerJoined.o

$(OBJDIRN)PlayerLeft.o: PlayerLeft.hpp PlayerLeft.cpp NetworkMessage.hpp
	$(CC) $(CFLAGS) -c PlayerLeft.cpp -o $(OBJDIRN)PlayerLeft.o

$(OBJDIRN)GameStart.o: GameStart.hpp GameStart.cpp NetworkMessage.hpp
	$(CC) $(CFLAGS) -c GameStart.cpp -o $(OBJDIRN)GameStart.o

$(OBJDIRN)GameEnd.o: GameEnd.hpp GameEnd.cpp NetworkMessage.hpp
	$(CC) $(CFLAGS) -c GameEnd.cpp -o $(OBJDIRN)GameEnd.o

$(OBJDIRN)PlayerInput.o: PlayerInput.hpp PlayerInput.cpp NetworkMessage.hpp $(SRCDIR)Player.hpp
	$(CC) $(CFLAGS) -c PlayerInput.cpp -o $(OBJDIRN)PlayerInput.o

$(OBJDIRN)PlayerKilled.o: PlayerKilled.hpp PlayerKilled.cpp NetworkMessage.hpp
	$(CC) $(CFLAGS) -c PlayerKilled.cpp -o $(OBJDIRN)PlayerKilled.o

clean:
	rm -rf $(OBJDIRN)
