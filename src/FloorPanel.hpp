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

#ifndef FLOORPANEL_HPP
#define FLOORPANEL_HPP

#include <OgreManualObject.h>

/**	The graphics of the floor
 */
class FloorPanel {
	public:
		/// Standard constructor
		FloorPanel(Ogre::ManualObject *man, Ogre::Real sx, Ogre::Real sz);
		/// Default destructor
		virtual ~FloorPanel();
		/// Generate a Floor at Y = 0 of size sizeX, sizeZ
		void generateFloor();
		/** Access manualFloor
		 * \return The current value of manualFloor
		 */
		Ogre::ManualObject* GetManualFloor() { return manualFloor; }
	protected:
		// Attributes
		/// The X size of the map
		int sizeX;
		/// The Z size of the map
		int sizeZ;
		/// A ManualObject which contains the floor
		Ogre::ManualObject *manualFloor;
	private:
};
#endif // FLOORPANEL_HPP
