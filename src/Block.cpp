#include "Block.hpp"

Block::Block(Ogre::ManualObject *man, PrintType print, Real px, Real py, Real pz, Real sx, Real sy, Real sz) :
	print (print),
	positionX (px),
	positionY (py),
	positionZ (pz),
	sizeX (sx),
	sizeY (sy),
	sizeZ (sz),
	manualBlock (man) {
	//ctor
}

Block::~Block() {
	//dtor
}