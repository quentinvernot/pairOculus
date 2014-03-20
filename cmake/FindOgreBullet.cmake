# - Find OgreBullet
# Find the native OgreBullet includes and library
#
#   OGREBULLET_FOUND       - True if OgreBullet found.
#   OGREBULLET_INCLUDE_DIR - where to find includes
#   OGREBULLET_LIBRARIES   - List of libraries when using OgreBullet.
#

if(OGREBULLET_INCLUDE_DIR)
    # Already in cache, be silent
    set(OGREBULLET_FIND_QUIETLY TRUE)
endif(OGREBULLET_INCLUDE_DIR)

find_path(
	OGREBULLET_INCLUDE_DIR "Dynamics/OgreBulletDynamicsRigidBody.h"
	PATH_SUFFIXES "OgreBullet"
)

find_library(OGREBULLET_COL_LIB "OgreBulletCollisions")
find_library(OGREBULLET_DYN_LIB "OgreBulletDynamics")

set(OGREBULLET_INCLUDE_DIRS "${OGREBULLET_INCLUDE_DIR}/Collisions" "${OGREBULLET_INCLUDE_DIR}/Dynamics")
set(OGREBULLET_LIBRARIES OgreBulletCollisions OgreBulletDynamics)

# handle the QUIETLY and REQUIRED arguments and set OGREBULLET_FOUND to TRUE if
# all listed variables are TRUE
include("FindPackageHandleStandardArgs")
find_package_handle_standard_args("OgreBullet" DEFAULT_MSG OGREBULLET_INCLUDE_DIR OGREBULLET_LIBRARIES)

mark_as_advanced(OGREBULLET_INCLUDE_DIR OGREBULLET_COL_LIB OGREBULLET_DYN_LIB)

