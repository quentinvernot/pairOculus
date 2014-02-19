#ifndef FLOORPANEL_H
#define FLOORPANEL_H

#include <OgreManualObject.h>

class FloorPanel {
	public:
		/** Default constructor */
//		FloorPanel();
		/** Standard constructor */
		FloorPanel(Ogre::ManualObject *man, Ogre::Real sx, Ogre::Real sz);
		/** Default destructor */
		virtual ~FloorPanel();
		/** */
		void generateFloor();
		/** Access manualFloor
		 * \return The current value of manualFloor
		 */
		Ogre::ManualObject* GetManualFloor() { return manualFloor; }
	protected:
		// Attributes
		int sizeX;
		int sizeZ;
		Ogre::ManualObject *manualFloor;
	private:
};
#endif // FLOORPANEL_H