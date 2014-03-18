CC=g++
CFLAGS=-Wall -g -pthread
SRCDIR=../
SRCDIRN=../NetworkMessage/
OBJDIR=../../obj/
OBJDIRS=../../obj/GameServer/
OBJDIRN=../../obj/NetworkMessage/
LIBDIR=../lib/

all: $(OBJDIRS) $(OBJDIRS)Instance.o $(OBJDIRS)Session.o $(OBJDIRS)SessionList.o
re: clean all

$(OBJDIRS):
	mkdir -p $(OBJDIRS)

DEP=$(SRCDIR)NetworkIO.hpp $(shell ls $(SRCDIRN)*.hpp) $(SRCDIR)Player.hpp $(SRCDIR)PlayerList.hpp $(SRCDIR)Map.hpp 

$(OBJDIRS)Instance.o: Instance.hpp Instance.cpp Session.hpp SessionList.hpp $(DEP)
	$(CC) $(CFLAGS) -c Instance.cpp -o $(OBJDIRS)Instance.o

$(OBJDIRS)Session.o: Session.hpp Session.cpp $(DEP) $(SRCDIR)NetworkIO.cpp
	$(CC) $(CFLAGS) -c Session.cpp -o $(OBJDIRS)Session.o

$(OBJDIRS)SessionList.o: SessionList.hpp SessionList.cpp Session.hpp
	$(CC) $(CFLAGS) -c SessionList.cpp -o $(OBJDIRS)SessionList.o

clean:
	rm -rf $(OBJDIRS)
