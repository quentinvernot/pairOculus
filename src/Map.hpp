#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <boost/random.hpp>

#include "Player.hpp"

class Map {
	public:
		enum PrintType {
			EMPTY = 0,
			BREAKABLE = 1,
			UNBREAKABLE = 2
		};

		/** Server constructor */
		Map(unsigned int height, unsigned int width);
		/** Client constructor */
		Map(unsigned int height, unsigned int width, time_t seed);
		/** Default destructor */
		virtual ~Map();

		/** generate the map
		 * \return the map to send it to the clients
		 */
		PrintType** generateMap();
		/** Asks if a cell is breakable
		 * \param the coordonees of the cell
		 * \return true if a block is breakable here
		 */
		bool isBreakable(int i, int j);
		/** set in Player the start position
		 * \param The player witch we are asking the starting position
		 */
		void getStartPosition(int pos, Player player);
		/** Access mMap
		 * \return The current value of mMap
		 */
//		int** getMap() { return mMap; }
		/** Set mMap
		 * \param val New value to set
		 */
//		void setMap(int** val) { mMap = val; }
		/** Access mMap
		 * \return The current value of mMap[i][j]
		 */
		PrintType getCellType(int i, int j) { return mMap[i][j]; }
		/** Set mMap
		 * \param val New value to set in mMap[i][j]
		 */
//		void setMap(int i, int j, int val) { mMap[i][j] = val; }
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
	private:
		//Methods
		/** Print the map in the console for debug
		 */
		void printMap();
		/** Set mWidth
		 * \param val New value to set
		 */
		void setWidth(int val) { (val%2 == 1) ? mWidth = val : mWidth = val+1; }
		/** Set mHeight
		 * \param val New value to set
		 */
		void setHeight(int val) { (val%2 == 1) ? mHeight = val : mHeight = val+1; }

		//Attributes
		PrintType** mMap;
		unsigned int mWidth;
		unsigned int mHeight;
		unsigned int mScale;
		time_t mSeed;
};

#endif // MAP_H