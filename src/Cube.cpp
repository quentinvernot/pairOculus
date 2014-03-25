/*
This source file is part of pairOculus, a student project aiming at creating a
simple 3D multiplayer game for the Oculus Rift.

Repository can be found here : https://github.com/Target6/pairOculus

Copyright (c) 2013 Zykino

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "Cube.hpp"

Cube::Cube(
	Ogre::ManualObject *man,
	PrintType print,
	Real px,
	Real py,
	Real pz,
	Real sx,
	Real sy,
	Real sz
) :
	Block (man, print, px, py, pz, sx, sy, sz)
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
		case COMPLETE:
			createBlockWireframe();
			createBlockSolid();
			break;
		default:
			std::cerr << "WARNING unimplemented option for Cube creation." << std::endl;	//!TODO create a log message for that
			break;
	}

}

Cube::~Cube() {
}

void Cube::createBlockPoint(){

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

void Cube::createBlockWireframe(){

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

void Cube::createBlockSolid (){

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
