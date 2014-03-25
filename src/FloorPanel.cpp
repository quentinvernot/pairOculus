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

#include "FloorPanel.hpp"

FloorPanel::FloorPanel(Ogre::ManualObject *man, Ogre::Real sx, Ogre::Real sz) :
	sizeX (sx),
	sizeZ (sz),
	manualFloor (man) {
	generateFloor();
}

FloorPanel::~FloorPanel() {
	//dtor
}

void FloorPanel::generateFloor() {
	manualFloor->begin("", Ogre::RenderOperation::OT_TRIANGLE_LIST);

	// define vertex position of index 0..4
	manualFloor->position(0, 0, 0);			// 0	(left, down)
	manualFloor->position(sizeX, 0, 0);		// 1	(right, down)
	manualFloor->position(sizeX, 0, sizeZ);	// 2	(right, up)
	manualFloor->position(0, 0, sizeZ);		// 3	(left, up)

	// define usage of vertices by refering to the indexes
	manualFloor->index(0);
	manualFloor->index(2);
	manualFloor->index(1);

	manualFloor->index(0);
	manualFloor->index(3);
	manualFloor->index(2);

	manualFloor->end();
}
