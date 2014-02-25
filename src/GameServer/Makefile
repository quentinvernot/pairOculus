CC=g++
CFLAGS=-Wall -g -pthread
SRCDIR=
OBJDIR=../../obj/
OBJDIRS=../../obj/GameServer/
OBJDIRN=../../obj/NetworkMessage/
LIBDIR=../lib/

LIBBOOST=-lboost_date_time -lboost_system -lboost_thread

all: $(OBJDIRS) $(OBJDIRS)Instance.o
re: clean all

$(OBJDIRS):
	mkdir -p $(OBJDIRS)

$(OBJDIRS)Instance.o: $(SRCDIR)Instance.hpp $(SRCDIR)Instance.cpp $(OBJDIRS)Session.o $(OBJDIRS)SessionList.o
	$(CC) $(CFLAGS) -c $(SRCDIR)Instance.cpp -o $(OBJDIRS)Instance.o

$(OBJDIRS)Session.o: $(SRCDIR)Session.hpp $(SRCDIR)Session.cpp $(OBJDIRN)*.o $(OBJDIR)NetworkIO.o
	$(CC) $(CFLAGS) -c $(SRCDIR)Session.cpp -o $(OBJDIRS)Session.o

$(OBJDIRS)SessionList.o: $(SRCDIR)SessionList.hpp $(SRCDIR)SessionList.cpp $(OBJDIRS)Session.o
	$(CC) $(CFLAGS) -c $(SRCDIR)SessionList.cpp -o $(OBJDIRS)SessionList.o

clean:
	rm -rf $(OBJDIRS)
