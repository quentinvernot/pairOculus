#include "Pyramid.hpp"

Pyramid::Pyramid(Ogre::ManualObject *man, PrintType print, Real px, Real py, Real pz, Real sx, Real sy, Real sz) :
	Block (man, print, px, py, pz, sx, sy, sz) {
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
		case COMPLETE:
			createBlockWireframe();
			createBlockSolid();
			break;
		default:
			std::cerr << "WARNING unimplemented option for Pyramid creation." << std::endl;	//!TODO create a log message for that
			break;
	}
}

Pyramid::~Pyramid() {
	//dtor
}

void Pyramid::createBlockPoint() {
	manualBlock->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_POINT_LIST);

	// define vertex position of index 0..4
	manualBlock->position(positionX, positionY, positionZ);									// 0	(left, bottom, front)
	manualBlock->position(positionX + sizeX, positionY, positionZ);							// 1	(right, bottom, front)
	manualBlock->position(positionX, positionY, positionZ + sizeZ);							// 2	(left, bottom, back)
	manualBlock->position(positionX + sizeX, positionY, positionZ + sizeZ);					// 3	(right, bottom, back)
	manualBlock->position(positionX + sizeX/2, positionY + sizeY, positionZ + sizeZ/2);		// 4	(top)

	// define usage of vertices by refering to the indexes
	manualBlock->index(0);
	manualBlock->index(1);
	manualBlock->index(2);
	manualBlock->index(3);
	manualBlock->index(4);

	manualBlock->end();
}

void Pyramid::createBlockWireframe() {
	manualBlock->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);

	// define vertex position of index 0..4
	manualBlock->position(positionX, positionY, positionZ);									// 0	(left, bottom, front)
	manualBlock->position(positionX + sizeX, positionY, positionZ);							// 1	(right, bottom, front)
	manualBlock->position(positionX, positionY, positionZ + sizeZ);							// 2	(left, bottom, back)
	manualBlock->position(positionX + sizeX, positionY, positionZ + sizeZ);					// 3	(right, bottom, back)
	manualBlock->position(positionX + sizeX/2, positionY + sizeY, positionZ + sizeZ/2);		// 4	(top)

	// define usage of vertices by refering to the indexes
	manualBlock->index(0);
	manualBlock->index(4);
	manualBlock->index(1);
	manualBlock->index(3);
	manualBlock->index(4);
	manualBlock->index(2);
	manualBlock->index(0);
	manualBlock->index(1);
	manualBlock->index(3);
	manualBlock->index(2);

	manualBlock->end();
}

void Pyramid::createBlockSolid () {
	manualBlock->begin("", Ogre::RenderOperation::OT_TRIANGLE_LIST);

	// define vertex position of index 0..4
	manualBlock->position(positionX, positionY, positionZ);									// 0	(left, bottom, front)
	manualBlock->position(positionX + sizeX, positionY, positionZ);							// 1	(right, bottom, front)
	manualBlock->position(positionX, positionY, positionZ + sizeZ);							// 2	(left, bottom, back)
	manualBlock->position(positionX + sizeX, positionY, positionZ + sizeZ);					// 3	(right, bottom, back)
	manualBlock->position(positionX + sizeX/2, positionY + sizeY, positionZ + sizeZ/2);		// 4	(top)

	// define usage of vertices by refering to the indexes
	// Bottom
	manualBlock->index(0);
	manualBlock->index(1);
	manualBlock->index(3);

	manualBlock->index(0);
	manualBlock->index(3);
	manualBlock->index(2);

	// Top
	manualBlock->index(0);
	manualBlock->index(4);
	manualBlock->index(1);

	manualBlock->index(1);
	manualBlock->index(4);
	manualBlock->index(3);

	manualBlock->index(3);
	manualBlock->index(4);
	manualBlock->index(2);

	manualBlock->index(2);
	manualBlock->index(4);
	manualBlock->index(0);

	manualBlock->end();
}