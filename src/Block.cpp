#include "Block.h"

Block::Block()
{
	//ctor
}

Block::Block(Ogre::ManualObject *man, PrintType print, bool des, Real px, Real py, Real pz, Real sx, Real sy, Real sz)
	:
	manualBlock (man),
	print (print),
	destructible (des),
	positionX (px),
	positionY (py),
	positionZ (pz),
	sizeX (sx),
	sizeY (sy),
	sizeZ (sz)
{
			std::cerr << "WARNING unimplemented option for Block creation." << std::endl;	//!TODO create a log message for that
	//ctor
}

Block::~Block()
{
	//dtor
}
