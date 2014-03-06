#ifndef LOCALMAP_H
#define LOCALMAP_H

#include <OgreManualObject.h>

#include "Map.hpp"
#include "FloorPanel.hpp"
#include "BlockFactory.hpp"

class LocalMap : public Map {
	public:
		/** Default constructor */
//		LocalMap(Map* mmap, Ogre::SceneManager* sceneMgr, unsigned int scale);
		LocalMap(unsigned int height, unsigned int width, time_t seed = time(0));
		/** Default destructor */
		virtual ~LocalMap();

		void generate(Ogre::SceneManager* sceneMgr);
	private:
		//Methodes
		void viewMap();

		//Attributes
};

#endif // LOCALMAP_H
