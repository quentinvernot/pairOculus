# Locate Bullet.
#
# This script defines:
#   BULLET_FOUND, set to 1 if found
#   BULLET_LIBRARIES
#   BULLET_INCLUDE_DIR
#   BULLET_*_LIBRARY, one for each library (for example, "BULLET_BulletCollision_LIBRARY").
#   BULLET_*_LIBRARY_debug, one for each library.
#   BULLET_EXTRAS_INCLUDE_DIR - Directory containing the bullet "Extras" headers
#   BULLET_DEMOS_INCLUDE_DIR - Directory containing the Demos/OpenGL headers
#
# This script will look in standard locations for installed Bullet. However, if you
# install Bullet into a non-standard location, you can use the BULLET_ROOT
# variable (in environment or CMake) to specify the location.
#
# You can also use Bullet out of a source tree by specifying BULLET_SOURCE_DIR
# and BULLET_BUILD_DIR (in environment or CMake).

message(STATUS "Looking for Bullet...")

#set(BULLET_ROOT "" CACHE PATH "Bullet install dir, parent of both header files and binaries.")
#set(BULLET_BUILD_DIR "" CACHE PATH "Parent directory of Bullet binary file directories such as src/BulletCollision.")
#set(BULLET_SOURCE_DIR "" CACHE PATH "Parent directory of Bullet header file directories such as src or include.")

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        set(OSX TRUE)
        set(HINT_PATHS /usr/local/include/bullet)
else()
        set(HINT_PATHS
                ${BULLET_ROOT}
                $ENV{BULLET_ROOT}
                ${BULLET_SOURCE_DIR}
                $ENV{BULLET_SOURCE_DIR}
                /usr/include/bullet
                /usr/local/include/bullet)
endif()

#unset(BULLET_INCLUDE_DIR CACHE)
#mark_as_advanced(BULLET_INCLUDE_DIR)

find_path(BULLET_INCLUDE_DIR btBulletCollisionCommon.h
          PATHS ${HINT_PATHS})

find_path(BULLET_INCLUDE_COLLISION_DIR BulletCollision/btBulletCollisionCommon.h
          PATHS ${HINT_PATHS})

if(BULLET_INCLUDE_COLLISION_DIR)
        set(BULLET_INCLUDE_COLLISION_DIR ${BULLET_INCLUDE_COLLISION_DIR}/BulletCollision)
endif()

find_path(BULLET_INCLUDE_DYNAMICS_DIR BulletDynamics/btBulletDynamicsCommon.h
          PATHS ${HINT_PATHS})

if(BULLET_INCLUDE_DYNAMICS_DIR)
        set(BULLET_INCLUDE_DYNAMICS_DIR ${BULLET_INCLUDE_DYNAMICS_DIR}/BulletDynamics)
endif()

find_path(BULLET_INCLUDE_CONVEXDECOMPOSITION_DIR ConvexDecomposition/ConvexDecomposition.h
          PATHS ${HINT_PATHS})

if(BULLET_INCLUDE_CONVEXDECOMPOSITION_DIR)
        set(BULLET_INCLUDE_CONVEXDECOMPOSITION_DIR ${BULLET_INCLUDE_CONVEXDECOMPOSITION_DIR}/ConvexDecomposition)
endif()

find_path(BULLET_INCLUDE_SOFTBODY_DIR BulletSoftBody/btSoftBody.h
          PATHS ${HINT_PATHS})

if(BULLET_INCLUDE_SOFTBODY_DIR)
        set(BULLET_INCLUDE_SOFTBODY_DIR ${BULLET_INCLUDE_SOFTBODY_DIR}/BulletSoftBody)
endif()

find_path(BULLET_INCLUDE_LINEARMATH_DIR LinearMath/btScalar.h
          PATHS ${HINT_PATHS})

if(BULLET_INCLUDE_LINEARMATH_DIR)
        set(BULLET_INCLUDE_LINEARMATH_DIR ${BULLET_INCLUDE_LINEARMATH_DIR}/LinearMath)
endif()

mark_as_advanced(BULLET_INCLUDE_COLLISION_DIR
                 BULLET_INCLUDE_DYNAMICS_DIR
                 BULLET_INCLUDE_CONVEXDECOMPOSITION_DIR
                 BULLET_INCLUDE_SOFTBODY_DIR
                 BULLET_INCLUDE_LINEARMATH_DIR)

#else(OSX)
#        find_path(BULLET_INCLUDE_COLLISION_DIR BulletCollision/btBulletCollisionCommon.h
#                  PATHS ${HINT_PATHS})

#        if(BULLET_INCLUDE_COLLISION_DIR)
#                 set(BULLET_INCLUDE_DIR "${BULLET_INCLUDE_COLLISION_DIR}/../")
#                 mark_as_advanced(BULLET_INCLUDE_COLLISION_DIR)
#        endif()

#        find_path(BULLET_INCLUDE_DYNAMICS_DIR BulletDynamics/btBulletDynamicsCommon.h
#                  PATHS ${HINT_PATHS})
#        mark_as_advanced(BULLET_INCLUDE_DYNAMICS_DIR)

#        find_path(BULLET_INCLUDE_CONVEXDECOMPOSITION_DIR ConvexDecomposition/ConvexDecomposition.h)
#        mark_as_advanced(BULLET_INCLUDE_CONVEXDECOMPOSITION_DIR)

#        find_path(BULLET_INCLUDE_SOFTBODY_DIR BulletSoftBody/btSoftBody.h)
#        mark_as_advanced(BULLET_INCLUDE_SOFTBODY_DIR)
#endif(OSX)

set(BULLET_INCLUDE_DIRS
        ${BULLET_INCLUDE_DIR}
        ${BULLET_INCLUDE_COLLISION_DIR}
        ${BULLET_INCLUDE_DYNAMICS_DIR}
        ${BULLET_INCLUDE_CONVEXDECOMPOSITION_DIR}
        ${BULLET_INCLUDE_SOFTBODY_DIR}
        ${BULLET_INCLUDE_LINEARMATH_DIR})

message(STATUS "BULLET_INCLUDE_DIRS: ${BULLET_INCLUDE_DIRS}")

find_library(BULLET_COLLISION_LIBRARY BulletCollision)
mark_as_advanced(BULLET_COLLISION_LIBRARY)

find_library(BULLET_DYNAMICS_LIBRARY BulletDynamics)
mark_as_advanced(BULLET_DYNAMICS_LIBRARY)

find_library(BULLET_CONVEXDECOMPOSITION_LIBRARY ConvexDecomposition)
mark_as_advanced(BULLET_CONVEXDECOMPOSITION_LIBRARY)

find_library(BULLET_SOFTBODY_LIBRARY BulletSoftBody)
mark_as_advanced(BULLET_SOFTBODY_LIBRARY)

find_library(BULLET_LINEARMATH_LIBRARY LinearMath)
mark_as_advanced(BULLET_LINEARMATH_LIBRARY)

if(BULLET_INCLUDE_DIR AND NOT OSX)
        set(BULLET_EXTRAS_INCLUDE_DIRS ${BULLET_INCLUDE_DIR}/../Extras)
        set(BULLET_DEMOS_INCLUDE_DIRS ${BULLET_INCLUDE_DIR}/../Demos/OpenGL)
endif()

set(BULLET_LIBRARIES
        ${BULLET_COLLISION_LIBRARY}
        ${BULLET_DYNAMICS_LIBRARY}
        ${BULLET_CONVEXDECOMPOSITION_LIBRARY}
        ${BULLET_SOFTBODY_LIBRARY}
	${BULLET_LINEARMATH_LIBRARY})

macro(FIND_BULLET_LIBRARY_DIRNAME LIBNAME DIRNAME)
	message(STATUS "Looking for ${LIBNAME}...")
	unset(BULLET_${LIBNAME}_LIBRARY CACHE)
	unset(BULLET_${LIBNAME}_LIBRARY_debug CACHE)
	mark_as_advanced(BULLET_${LIBNAME}_LIBRARY)
	mark_as_advanced(BULLET_${LIBNAME}_LIBRARY_debug)
	find_library(BULLET_${LIBNAME}_LIBRARY
		NAMES ${LIBNAME}
		PATHS ${BULLET_ROOT}
			$ENV{BULLET_ROOT}
			${BULLET_BUILD_DIR}
			$ENV{BULLET_BUILD_DIR}
			"C:/Program Files/BULLET_PHYSICS"
		PATH_SUFFIXES
			./src/${DIRNAME}
			./Extras/${DIRNAME}
			./Demos/${DIRNAME}
			./src/${DIRNAME}/Release
			./Extras/${DIRNAME}/Release
			./Demos/${DIRNAME}/Release
			./libs/${DIRNAME}
			./libs
			./lib
			./lib/Release) # v2.76, new location for build tree libs on Windows

	find_library(BULLET_${LIBNAME}_LIBRARY_debug
		NAMES ${LIBNAME}
		PATHS ${BULLET_ROOT}
			$ENV{BULLET_ROOT}
			${BULLET_BUILD_DIR}
			$ENV{BULLET_BUILD_DIR}
			"C:/Program Files/BULLET_PHYSICS"
		PATH_SUFFIXES
			./src/${DIRNAME}
			./Extras/${DIRNAME}
			./Demos/${DIRNAME}
			./src/${DIRNAME}/Debug
			./Extras/${DIRNAME}/Debug
			./Demos/${DIRNAME}/Debug
			./libs/${DIRNAME}
			./libs
			./lib
			./lib/Debug) # v2.76, new location for build tree libs on Windows

#    message(STATUS ${BULLET_${LIBNAME}_LIBRARY} ${BULLET_${LIBNAME}_LIBRARY_debug})
#    message(SEND_ERROR ${LIBNAME})

	if(BULLET_${LIBNAME}_LIBRARY)
		set(BULLET_LIBRARIES ${BULLET_LIBRARIES}
			"optimized" ${BULLET_${LIBNAME}_LIBRARY})
		message(STATUS "Found Bullet${LIBNAME}: ${BULLET_${LIBNAME}_LIBRARY}")
	else(BULLET_${LIBNAME}_LIBRARY)
		message(STATUS "Bullet${LIBNAME} not found!")
	endif(BULLET_${LIBNAME}_LIBRARY)

	if(BULLET_${LIBNAME}_LIBRARY_debug)
		set(BULLET_LIBRARIES ${BULLET_LIBRARIES}
			"debug" ${BULLET_${LIBNAME}_LIBRARY_debug})
		message(STATUS "Found Bullet${LIBNAME} (debug): ${BULLET_${LIBNAME}_LIBRARY_debug}")
	else(BULLET_${LIBNAME}_LIBRARY_debug)
		message(STATUS "Bullet${LIBNAME} (debug) not found!")
	endif(BULLET_${LIBNAME}_LIBRARY_debug)

endmacro(FIND_BULLET_LIBRARY_DIRNAME LIBNAME)

macro(FIND_BULLET_LIBRARY LIBNAME)
	find_bullet_library_dirname(${LIBNAME} ${LIBNAME})
endmacro(FIND_BULLET_LIBRARY LIBNAME)

#find_bullet_library(BulletDynamics)
#find_bullet_library(BulletSoftBody)
#find_bullet_library(BulletCollision)
#find_bullet_library(BulletMultiThreaded)
#find_bullet_library(LinearMath)
#find_bullet_library_dirname(OpenGLSupport OpenGL)
#find_bullet_library(ConvexDecomposition)

# Pre-2.76
#find_bullet_library_dirname(XML LibXML)
#find_bullet_library_dirname(ColladaDom COLLADA_DOM)
#find_bullet_library(BulletColladaConverter)

# Hide BULLET_LIBRARY in the GUI, since most users can just ignore it
#mark_as_advanced(BULLET_LIBRARIES)
#mark_as_advanced(BULLET_LIBRARIES_debug)

set(BULLET_FOUND FALSE)
if(BULLET_INCLUDE_DIR AND BULLET_LIBRARIES)
	set(BULLET_FOUND TRUE)
endif(BULLET_INCLUDE_DIR AND BULLET_LIBRARIES)

# in v2.76, ColladaConverter was removed.
#if(BULLET_BulletColladaConverter_LIBRARY OR BULLET_BulletColladaConverter_LIBRARY_debug)
#	set(BULLET_COLLADACONVERTER_FOUND)
#endif(BULLET_BulletColladaConverter_LIBRARY OR BULLET_BulletColladaConverter_LIBRARY_debug)
