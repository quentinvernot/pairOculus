CC=g++
CFLAGS=-Wall -g -pthread
OBJDIR=../obj/
LIBDIR=../lib/

BOOST=-I/usr/include/boost
OGRE=`pkg-config --cflags OGRE`
OIS=-I/usr/include/OIS
BULLET=`pkg-config --cflags bullet` -I/usr/local/include/OgreBullet/Dynamics  -I/usr/local/include/OgreBullet/Collisions

GAME=$(OBJDIR)Game.o $(OBJDIR)GameWindow.o $(OBJDIR)Input.o 
PLAYER=$(OBJDIR)Player.o $(OBJDIR)PlayerList.o $(OBJDIR)LocalPlayer.o $(OBJDIR)LocalPlayerList.o $(OBJDIR)PlayerAnimation.o
CAMERA=$(OBJDIR)CameraManager.o $(OBJDIR)SimpleCamera.o $(OBJDIR)OculusCamera.o
BOMB=$(OBJDIR)Bomb.o $(OBJDIR)BombManager.o
BLOCK=$(OBJDIR)Block.o $(OBJDIR)Cube.o $(OBJDIR)Pyramid.o $(OBJDIR)FloorPanel.o $(OBJDIR)BlockFactory.o
MAP=$(OBJDIR)Map.o $(OBJDIR)LocalMap.o
NETWORK=$(OBJDIR)NetworkMessage $(OBJDIR)NetworkIO.o $(OBJDIR)GameServer $(OBJDIR)GameClient

ALL=$(OBJDIR) $(GAME) $(PLAYER) $(CAMERA) $(BOMB) $(BLOCK) $(MAP) $(NETWORK)

all: $(ALL)
re: clean all

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)Game.o: Game.hpp Game.cpp $(shell ls *.hpp) $(shell ls NetworkMessage/*.hpp) $(shell ls GameClient/*.hpp)
	$(CC) $(OGRE) $(OIS)  $(BULLET) $(CFLAGS) -c Game.cpp -o $(OBJDIR)Game.o

$(OBJDIR)GameWindow.o: GameWindow.hpp GameWindow.cpp CameraManager.hpp
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c GameWindow.cpp -o $(OBJDIR)GameWindow.o

$(OBJDIR)Input.o: Input.hpp Input.cpp
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c Input.cpp -o $(OBJDIR)Input.o

$(OBJDIR)Player.o: Player.hpp Player.cpp
	$(CC) $(CFLAGS) -c Player.cpp -o $(OBJDIR)Player.o

$(OBJDIR)PlayerList.o: PlayerList.hpp PlayerList.cpp Player.hpp
	$(CC) $(CFLAGS) -c PlayerList.cpp -o $(OBJDIR)PlayerList.o

$(OBJDIR)LocalPlayer.o: LocalPlayer.hpp LocalPlayer.cpp Player.hpp CameraManager.hpp SimpleCamera.hpp OculusCamera.hpp PlayerAnimation.hpp Bomb.hpp BombManager.hpp $(ls NetworkMessage/.*hpp)
	$(CC) $(OGRE) $(OIS) $(BULLET) $(CFLAGS) -c LocalPlayer.cpp -o $(OBJDIR)LocalPlayer.o

$(OBJDIR)LocalPlayerList.o: LocalPlayerList.hpp LocalPlayerList.cpp LocalPlayer.hpp
	$(CC) $(OGRE) $(OIS) $(BULLET) $(CFLAGS) -c LocalPlayerList.cpp -o $(OBJDIR)LocalPlayerList.o

$(OBJDIR)PlayerAnimation.o: PlayerAnimation.hpp PlayerAnimation.cpp
	$(CC) $(OGRE) $(CFLAGS) -c PlayerAnimation.cpp -o $(OBJDIR)PlayerAnimation.o

$(OBJDIR)CameraManager.o: CameraManager.hpp CameraManager.cpp SimpleCamera.hpp OculusCamera.hpp
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c CameraManager.cpp -o $(OBJDIR)CameraManager.o

$(OBJDIR)SimpleCamera.o: SimpleCamera.hpp SimpleCamera.cpp
	$(CC) $(OGRE) $(CFLAGS) -c SimpleCamera.cpp -o $(OBJDIR)SimpleCamera.o

$(OBJDIR)OculusCamera.o: OculusCamera.hpp OculusCamera.cpp
	$(CC) $(OGRE) $(CFLAGS) -c OculusCamera.cpp -o $(OBJDIR)OculusCamera.o

$(OBJDIR)Bomb.o: Bomb.hpp Bomb.cpp
	$(CC) $(OGRE) $(OIS) $(BULLET) $(CFLAGS) -c Bomb.cpp -o $(OBJDIR)Bomb.o

$(OBJDIR)BombManager.o: BombManager.hpp BombManager.cpp Bomb.hpp LocalMap.hpp Block.hpp Cube.hpp Pyramid.hpp FloorPanel.hpp BlockFactory.hpp Player.hpp Map.hpp
	$(CC) $(OGRE) $(OIS) $(BULLET) $(CFLAGS) -c BombManager.cpp -o $(OBJDIR)BombManager.o

$(OBJDIR)Block.o: Block.hpp Block.cpp
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c Block.cpp -o $(OBJDIR)Block.o

$(OBJDIR)Cube.o: Cube.hpp Cube.cpp Block.hpp
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c Cube.cpp -o $(OBJDIR)Cube.o

$(OBJDIR)Pyramid.o: Pyramid.hpp Pyramid.cpp Block.hpp
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c Pyramid.cpp -o $(OBJDIR)Pyramid.o

$(OBJDIR)FloorPanel.o: FloorPanel.hpp FloorPanel.cpp
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c FloorPanel.cpp -o $(OBJDIR)FloorPanel.o

$(OBJDIR)BlockFactory.o: BlockFactory.hpp BlockFactory.cpp Cube.hpp Pyramid.hpp
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c BlockFactory.cpp -o $(OBJDIR)BlockFactory.o

$(OBJDIR)Map.o: Map.hpp Map.cpp Player.hpp
	$(CC) $(OIS) $(CFLAGS) -c Map.cpp -o $(OBJDIR)Map.o

$(OBJDIR)LocalMap.o: LocalMap.hpp LocalMap.cpp Block.hpp Cube.hpp Pyramid.hpp FloorPanel.hpp BlockFactory.hpp Player.hpp Map.hpp
	$(CC) $(OGRE) $(OIS) $(BULLET) $(CFLAGS) -c LocalMap.cpp -o $(OBJDIR)LocalMap.o

$(OBJDIR)NetworkMessage: .FORCE
	cd NetworkMessage/ && make

$(OBJDIR)NetworkIO.o: NetworkIO.hpp NetworkIO.cpp $(shell ls NetworkMessage/*.hpp)
	$(CC) $(OGRE) $(OIS) $(CFLAGS) -c NetworkIO.cpp -o $(OBJDIR)NetworkIO.o

$(OBJDIR)GameServer: .FORCE
	cd GameServer/ && make

$(OBJDIR)GameClient: .FORCE
	cd GameClient/ && make

clean:
	cd NetworkMessage/ && make clean
	cd GameServer/ && make clean
	cd GameClient/ && make clean
	rm -rf $(OBJDIR)

.FORCE:
