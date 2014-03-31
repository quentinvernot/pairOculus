# Howto
This is a tutorial on how to install the various dependencies needed to work on this project.

## Tools
Before starting, you will need to install the following tools :  
* build-essential (or the windows equivalent with at least a compiler and make)
* git (You are probably reading this on github anyway...)
* CMake
* Doxygen
  
This tutorial assumes that you know how to use these tools.

## Dependencies
As mentioned in the README, you will need the following libraries to build the project :
* Boost 1.52 or better
* OGRE 3D 1.8.1
* Bullet 2.82
* OgreBullet, can be found here : https://bitbucket.org/alexeyknyshev/ogrebullet
* LibOVR (from the Oculus Rift's SDK) 0.2.5c
  
We'll go through them one by one.

### Boost
#### Windows 7
* Download the last version from the [boost website](http://www.boost.org/).
* Unpack it.
* With the console, move to the directory where you unpacked boost and compile/install it using `b2`. Don't forget to indicate the proper toolset. If you are using mingwg, you will need to type `b2 toolset=gcc`. The complete list of toolsets can be found [here](http://www.boost.org/doc/libs/1_47_0/more/getting_started/windows.html#identify-your-toolset).

Note that on Windows, LibOVR is currently (2014-03-27) only suppports vc++. A thread exists on the [Oculus forum](https://developer.oculusvr.com/forums/viewtopic.php?t=2282) if you want to build it with mingw. Otherwise, use the msvc toolset.

#### Ubuntu/Mint
Install with `sudo apt-get install libboost-all-dev`.

### OGRE
An actual tutorial can be found [here](http://www.ogre3d.org/tikiwiki/Installing+the+Ogre+SDK).
#### Windows 7
* Download OGRE 1.8.1 from the [OGRE website](http://www.ogre3d.org/download/sdk).
* Run the installer.
* Set the OGRE_HOME environement variable with `setx OGRE_HOME "<path-to-OgreSDK-here>"`

#### Ubuntu/Mint
* Download OGRE 1.8.1 from the [OGRE website](http://www.ogre3d.org/download/sdk).
* Use CMake to generate the makefile.
* Run `make && sudo make install`.

### Bullet
#### Windows 7
* Download Bullet 2.82 from the [Bullet download page](http://code.google.com/p/bullet/downloads/list).
* Unpack it.
* Use CMake to generate the makefile.
* Run `make`.
* Set the BULLET_ROOT environement variable with `setx BULLET_ROOT "<path-to-BulletBuild-here>"`

#### Ubuntu/Mint
* Download Bullet 2.82 from the [Bullet download page](http://code.google.com/p/bullet/downloads/list).
* Unpack it.
* Use CMake to generate the makefile.
* Run `make && sudo make install`.

### OgreBullet
A tutorial can be found [here](http://www.ogre3d.org/addonforums/viewtopic.php?f=12&t=29784).
* Clone the [OgreBullet repository](https://bitbucket.org/alexeyknyshev/ogrebullet) with `git clone https://bitbucket.org/alexeyknyshev/ogrebullet`.
* Use CMake to generate the makefile.
* Run `make && sudo make install`.

### LibOVR
#### Windows 7
* Sign in/up in the [OculusVR website](https://developer.oculusvr.com/).
* Download version 0.2.5c from the download page.

#### Ubuntu/Mint
* Sign in/up in the [OculusVR website](https://developer.oculusvr.com/).
* Download version 0.2.5c from the download page.
* Set the LIBOVR_DIR environement variable with `setx LIBOVR_DIR "<path-to-LibOVR-here>"`

### The project itself
* Clone the project from gihub.
* Use CMake to generate the makefile.
* Run `make`.
