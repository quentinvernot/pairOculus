#ifndef PYRAMID_H
#define PYRAMID_H

#include "Block.h"

class Pyramid : public Block
{
	public:
		/** Default constructor */
		Pyramid();
		/** My constructor */
		Pyramid(Ogre::ManualObject *man, PrintType print, bool des, Real px, Real py, Real pz, Real sx = 100.0, Real sy = 100.0, Real sz = 100.0);
		/** Default destructor */
		virtual ~Pyramid();

		virtual void createBlockPoint();

		virtual void createBlockWireframe();

		virtual void createBlockSolid();

	protected:
	private:
};

#endif // PYRAMID_H
