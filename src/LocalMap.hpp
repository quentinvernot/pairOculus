#ifndef LOCALMAP_H
#define LOCALMAP_H

#include <OgreManualObject.h>

#include "Map.hpp"
#include "FloorPanel.hpp"
#include "BlockFactory.hpp"

class LocalMap {//: public Map {
	public:
		/** Default constructor */
		LocalMap(Map* mmap, Ogre::SceneManager* sceneMgr, unsigned int scale);
		/** Default destructor */
		virtual ~LocalMap();

	private:
		//Methodes
		void viewMap();

		//Attributes
		Map* mmap;
};

#endif // LOCALMAP_H
