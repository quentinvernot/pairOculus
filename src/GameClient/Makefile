CC=g++
CFLAGS=-Wall -g -pthread
SRCDIR=../
SRCDIRN=../NetworkMessage
OBJDIR=../../obj/
OBJDIRC=../../obj/GameClient/
OBJDIRN=../../obj/NetworkMessage/
LIBDIR=../lib/

all: $(OBJDIRC) $(OBJDIRC)Listener.o $(OBJDIRC)Connector.o
re: clean all

$(OBJDIRC):
	mkdir -p $(OBJDIRC)

DEP=$(SRCDIR)NetworkIO.hpp $(ls $(SRCDIRN).*hpp) $(SRCDIR)PlayerList.hpp $(SRCDIR)Map.hpp 

$(OBJDIRC)Listener.o: Listener.hpp Listener.cpp Connector.hpp $(DEP)
	$(CC) $(CFLAGS) -c $()Listener.cpp -o $(OBJDIRC)Listener.o

$(OBJDIRC)Connector.o: Connector.hpp Connector.cpp $(DEP)
	$(CC) $(CFLAGS) -c Connector.cpp -o $(OBJDIRC)Connector.o

clean:
	rm -rf $(OBJDIRC)
