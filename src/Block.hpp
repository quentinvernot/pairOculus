#ifndef BLOCK_H
#define BLOCK_H

#include <OgreManualObject.h>

using namespace Ogre;

class Block {
	public:
		enum PrintType {
			EMPTY,		// Create an empty Block
			POINT,		// White point on angles
			WIREFRAME,	// Whites lines
			SOLID,		// Faces
			COMPLETE	// The faces and the lines
		};

		/** Default constructor */
//		Block();
		/** My constructor */
		Block(Ogre::ManualObject *man, PrintType print, Real px, Real py, Real pz, Real sx = 100, Real sy = 100, Real sz = 100);
		/** Default destructor */
		virtual ~Block();

		virtual void createBlockPoint() = 0;

		virtual void createBlockWireframe() = 0;

		virtual void createBlockSolid() = 0;

		/** Access positionX
		 * \return The current value of positionX
		 */
		int GetpositionX() { return positionX; }
		/** Set positionX
		 * \param val New value to set
		 */
//		void SetpositionX(int val) { positionX = val; }
		/** Access positionY
		 * \return The current value of positionY
		 */
		int GetpositionY() { return positionY; }
		/** Set positionY
		 * \param val New value to set
		 */
//		void SetpositionY(int val) { positionY = val; }
		/** Access positionZ
		 * \return The current value of positionZ
		 */
		int GetpositionZ() { return positionZ; }
		/** Set positionZ
		 * \param val New value to set
		 */
//		void SetpositionZ(int val) { positionZ = val; }
		/** Access sizeX
		 * \return The current value of sizeX
		 */
		int GetsizeX() { return sizeX; }
		/** Set sizeX
		 * \param val New value to set
		 */
//		void SetsizeX(int val) { sizeX = val; }
		/** Access sizeY
		 * \return The current value of sizeY
		 */
		int GetsizeY() { return sizeY; }
		/** Set sizeY
		 * \param val New value to set
		 */
//		void SetsizeY(int val) { sizeY = val; }
		/** Access sizeZ
		 * \return The current value of sizeZ
		 */
		int GetsizeZ() { return sizeZ; }
		/** Set sizeZ
		 * \param val New value to set
		 */
//		void SetsizeZ(int val) { sizeZ = val; }
		/** Access manualBlock
		 * \return The current value of manualBlock
		 */
		Ogre::ManualObject* GetManualBlock() { return manualBlock; }
		/** Set manualBlock
		 * \param val New value to set
		 */
//		void SetManualBlock(Ogre::ManualObject *val) { manualBlock = val; }
	protected:
		// Attributes
		PrintType print;
		Real positionX;
		Real positionY;
		Real positionZ;
		int sizeX;
		int sizeY;
		int sizeZ;
		Ogre::ManualObject *manualBlock;
	private:
};

#endif // BLOCK_H