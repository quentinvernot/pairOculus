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

#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <boost/random.hpp>

#include "Player.hpp"

/**
 * The Map's data
 * Generate the map randomly and store it
 */
class Map {
	public:
		/// The type a cell can be
		enum PrintType {
			EMPTY = 0,			//! An empty cell
			BREAKABLE = 1,		//! A cell with a breakable block
			UNBREAKABLE = 2		//! A cell with an unbreakable block
		};

		/// Constructor
		Map(unsigned int height, unsigned int width, time_t seed = time(0));
		/// Default destructor
		virtual ~Map();

		/** generate the map
		 * \return the map to send it to the clients
		 */
		PrintType** generateMap();
		/** Asks if a cell is breakable
		 * \param the coordonees of the cell
		 * \return true if a block is breakable here
		 */
		bool isBreakable(unsigned int i, unsigned int j);
		/** Asks if a cell is unbreakable
		 * \param the coordonees of the cell
		 * \return true if a block is unbreakable here
		 */
		bool isUnbreakable(unsigned int i, unsigned int j);
		/** set in Player the start position
		 * \param The player witch we are asking the starting position
		 */
		void setStartingPosition(int pos, Player *player);
		/** Access mMap
		 * \return The current value of mMap[i][j]
		 */
		PrintType getCellType(int i, int j) { return mMap[i][j]; }
		/** Access mWidth
		 * \return The current value of mWidth
		 */
		unsigned int getWidth() { return mWidth; }
		/** Access mHeight
		 * \return The current value of mHeight
		 */
		unsigned int getHeight() { return mHeight; }
		/** Access mSeed
		 * \return The current value of mSeed
		 */
		time_t getSeed();

	protected:
		// Methods
		/// Print the map in the console for debug
		void printMap();
		/** Set mWidth
		 * \param val New value to set
		 */
		void setWidth(int val) { (val%2 == 1) ? mWidth = val : mWidth = val+1; }
		/** Set mHeight
		 * \param val New value to set
		 */
		void setHeight(int val) { (val%2 == 1) ? mHeight = val : mHeight = val+1; }

		// Attributes
		/// The map in
		PrintType** mMap;
		/// The map width
		unsigned int mWidth;
		/// The map height
		unsigned int mHeight;
		/// The cell's scale
		double mScale;
		/// The seed of the map
		time_t mSeed;

	private:
};

#endif // MAP_H
