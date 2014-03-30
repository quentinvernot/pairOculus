# pairOculus
This is a student project aiming at creating a simple 3D multiplayer Bomberman using the Oculus Rift.  
This repository contains the source code, config files, media and necessary files to build the project.

## Dependencies
You will need the following libraries to build the project :
* Boost 1.52 or better
* OGRE 3D 1.8.1
* Bullet 2.82
* OgreBullet, can be found here : https://bitbucket.org/alexeyknyshev/ogrebullet
* LibOVR (from the Oculus Rift's SDK) 0.2.5c

## Building the project
This project uses CMake as a build system. Use it to configure and generate the Makefile, then build the project with make.

Note that on Windows, LibOVR currently (2014-03-27) only suppports vc++.  
A way to compile it with mingw can be found [here](https://developer.oculusvr.com/forums/viewtopic.php?t=2282).

## Documentation
You can generate the documentation with :  
`$ doxygen Doxyfile`
