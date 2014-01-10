#include "Cube.h"

Cube::Cube(Ogre::ManualObject *man, PrintType print, bool des, Real px, Real py, Real pz, Real sx, Real sy, Real sz)
	:
	Block (man, print, des, px, py, pz, sx, sy, sz)
{
	switch (print) {
		case EMPTY:
			break;
		case POINT:
			createBlockPoint ();
			break;
		case WIREFRAME:
			createBlockWireframe();
			break;
		case SOLID:
			createBlockSolid();
			break;
		case COMPLET:
			createBlockWireframe();
			createBlockSolid();
			break;
		default:
			std::cerr << "WARNING unimplemented option for Cube creation." << std::endl;	//!TODO create a log message for that
	}
}

Cube::~Cube()
{
	//dtor
}

void Cube::createBlockPoint()
{
	manualBlock->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_POINT_LIST);

	// define vertex position of index 0..7
	manualBlock->position(positionX, positionY, positionZ);								// 0	(left, bottom, front)
	manualBlock->position(positionX + sizeX, positionY, positionZ);						// 1	(right, bottom, front)
	manualBlock->position(positionX + sizeX, positionY + sizeY, positionZ);				// 2	(right, top, front)
	manualBlock->position(positionX, positionY + sizeY, positionZ);						// 3	(left, top, front)
	manualBlock->position(positionX, positionY, positionZ + sizeZ);						// 4	(left, bottom, back)
	manualBlock->position(positionX + sizeX, positionY, positionZ + sizeZ);				// 5	(right, bottom, back)
	manualBlock->position(positionX, positionY + sizeY, positionZ + sizeZ);				// 6	(left, top, back)
	manualBlock->position(positionX + sizeX, positionY + sizeY, positionZ + sizeZ);		// 7	(right, top, back)

	// define usage of vertices by refering to the indexes
	manualBlock->index(0);
	manualBlock->index(1);
	manualBlock->index(2);
	manualBlock->index(3);
	manualBlock->index(4);
	manualBlock->index(5);
	manualBlock->index(6);
	manualBlock->index(7);

	manualBlock->end();
}

void Cube::createBlockWireframe()
{
	manualBlock->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);

	// define vertex position of index 0..7
	manualBlock->position(positionX, positionY, positionZ);								// 0	(left, bottom, front)
	manualBlock->position(positionX + sizeX, positionY, positionZ);						// 1	(right, bottom, front)
	manualBlock->position(positionX + sizeX, positionY + sizeY, positionZ);				// 2	(right, top, front)
	manualBlock->position(positionX, positionY + sizeY, positionZ);						// 3	(left, top, front)
	manualBlock->position(positionX, positionY, positionZ + sizeZ);						// 4	(left, bottom, back)
	manualBlock->position(positionX + sizeX, positionY, positionZ + sizeZ);				// 5	(right, bottom, back)
	manualBlock->position(positionX, positionY + sizeY, positionZ + sizeZ);				// 6	(left, top, back)
	manualBlock->position(positionX + sizeX, positionY + sizeY, positionZ + sizeZ);		// 7	(right, top, back)

	// define usage of vertices by refering to the indexes
	manualBlock->index(0);
	manualBlock->index(1);
	manualBlock->index(5);
	manualBlock->index(7);
	manualBlock->index(6);
	manualBlock->index(4);
	manualBlock->index(0);
	manualBlock->index(3);
	manualBlock->index(2);
	manualBlock->index(1);
	manualBlock->index(2);
	manualBlock->index(7);
	manualBlock->index(5);
	manualBlock->index(4);
	manualBlock->index(6);
	manualBlock->index(3);

	manualBlock->end();
}

void Cube::createBlockSolid ()
{
	manualBlock->begin("", Ogre::RenderOperation::OT_TRIANGLE_LIST);

	// define vertex position of index 0..7
	manualBlock->position(positionX, positionY, positionZ);								// 0	(left, bottom, front)
	manualBlock->position(positionX + sizeX, positionY, positionZ);						// 1	(right, bottom, front)
	manualBlock->position(positionX + sizeX, positionY + sizeY, positionZ);				// 2	(right, top, front)
	manualBlock->position(positionX, positionY + sizeY, positionZ);						// 3	(left, top, front)
	manualBlock->position(positionX, positionY, positionZ + sizeZ);						// 4	(left, bottom, back)
	manualBlock->position(positionX + sizeX, positionY, positionZ + sizeZ);				// 5	(right, bottom, back)
	manualBlock->position(positionX, positionY + sizeY, positionZ + sizeZ);				// 6	(left, top, back)
	manualBlock->position(positionX + sizeX, positionY + sizeY, positionZ + sizeZ);		// 7	(right, top, back)

	// define usage of vertices by refering to the indexes
	// Front
	manualBlock->index(0);
	manualBlock->index(2);
	manualBlock->index(1);

	manualBlock->index(0);
	manualBlock->index(3);
	manualBlock->index(2);

	// Back
	manualBlock->index(4);
	manualBlock->index(5);
	manualBlock->index(7);

	manualBlock->index(4);
	manualBlock->index(7);
	manualBlock->index(6);

	// Bottom
	manualBlock->index(0);
	manualBlock->index(1);
	manualBlock->index(5);

	manualBlock->index(0);
	manualBlock->index(5);
	manualBlock->index(4);

	// Top
	manualBlock->index(3);
	manualBlock->index(7);
	manualBlock->index(2);

	manualBlock->index(3);
	manualBlock->index(6);
	manualBlock->index(7);

	// Left
	manualBlock->index(0);
	manualBlock->index(6);
	manualBlock->index(3);

	manualBlock->index(0);
	manualBlock->index(4);
	manualBlock->index(6);

	// Right
	manualBlock->index(1);
	manualBlock->index(7);
	manualBlock->index(5);

	manualBlock->index(1);
	manualBlock->index(2);
	manualBlock->index(7);

	manualBlock->end();
}
