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