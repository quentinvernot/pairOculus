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

#ifndef BLOCKFACTORY_HPP
#define BLOCKFACTORY_HPP

#include <sstream>

#include <OgreSceneManager.h>
#include <OgreLogManager.h>
#include <OgreManualObject.h>

#include "Map.hpp"
#include "Cube.hpp"
#include "Pyramid.hpp"

/**	A factory for Block
 */
class BlockFactory {

	public:
		/// Constructor
		BlockFactory(Ogre::SceneManager* sceneMgr);
		/// Destructor
		virtual ~BlockFactory();

		/// Create a Block at a particular position
		Ogre::ManualObject* createBlock(
			Map::PrintType cellType,
			unsigned int i,
			unsigned int j,
			double scale
		);

	private:
		/// Game's SceneManager
		Ogre::SceneManager* mSceneMgr;

};

#endif // BLOCKFACTORY_HPP
