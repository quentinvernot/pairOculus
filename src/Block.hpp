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

#ifndef BLOCK_H
#define BLOCK_H

#include <OgreManualObject.h>

using namespace Ogre;
/**	Abstract representation of the Block.
 *	Store the position, the size and the representation.
 */
class Block {
	public:
		/// The kind of type a block can be
		enum PrintType {
			EMPTY,		//! Create an empty Block
			POINT,		//! White point on angles
			WIREFRAME,	//! Whites lines
			SOLID,		//! Faces
			COMPLETE	//! The faces and the lines
		};

		/// Constructor
		Block(Ogre::ManualObject *man, PrintType print, Real px, Real py, Real pz, Real sx = 100, Real sy = 100, Real sz = 100);
		/// Default destructor
		virtual ~Block();

		/// Schould show the caracteristical points of the block
		virtual void createBlockPoint() = 0;
		/// Should show the skeleton of the block
		virtual void createBlockWireframe() = 0;
		/// Should show the solid block
		virtual void createBlockSolid() = 0;

		/** Access positionX
		 * \return The current value of positionX
		 */
		int GetpositionX() { return positionX; }
		/** Access positionY
		 * \return The current value of positionY
		 */
		int GetpositionY() { return positionY; }
		/** Access positionZ
		 * \return The current value of positionZ
		 */
		int GetpositionZ() { return positionZ; }
		/** Access sizeX
		 * \return The current value of sizeX
		 */
		int GetsizeX() { return sizeX; }
		/** Access sizeY
		 * \return The current value of sizeY
		 */
		int GetsizeY() { return sizeY; }
		/** Access sizeZ
		 * \return The current value of sizeZ
		 */
		int GetsizeZ() { return sizeZ; }
		/** Access manualBlock
		 * \return The current value of manualBlock
		 */
		Ogre::ManualObject* GetManualBlock() { return manualBlock; }
	protected:
		// Attributes
		PrintType print;
		/// The position on X axis
		Real positionX;
		/// The position on Y axis
		Real positionY;
		/// The position on Z axis
		Real positionZ;
		/// The size of the block on the X axis
		Real sizeX;
		/// The size of the block on the Y axis
		Real sizeY;
		/// The size of the block on the Z axis
		Real sizeZ;
		/// The representation of the block
		Ogre::ManualObject *manualBlock;
	private:
};

#endif // BLOCK_H
