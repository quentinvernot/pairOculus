cmake_minimum_required(VERSION 2.8)

project(pairOculus)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

# Find Ogre
find_package(OGRE REQUIRED)

if(NOT "${OGRE_VERSION_NAME}" STREQUAL "Byatis")
	message(SEND_ERROR "You need Ogre 1.8.1 Byatis to build this.")
endif()

# Find OIS
find_package(OIS REQUIRED)

if(NOT OIS_FOUND)
	message(SEND_ERROR "Failed to find OIS.")
endif()

# Find Bullet
find_package(Bullet REQUIRED)

if(NOT BULLET_FOUND)
	message(SEND_ERROR "Failed to find Bullet.")
endif()

# Find OgreBullet
find_package(OgreBullet REQUIRED)

if(NOT OGREBULLET_FOUND)
	message(SEND_ERROR "Failed to find OgreBullet.")
endif()

# Find LibOVR
find_package(LibOVR REQUIRED)

if(NOT LIBOVR_FOUND)
	message(SEND_ERROR "Failed to find LibOVR.")
endif()

# Find Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
# Components that need linking (NB does not include header-only components like bind)
find_package(Boost COMPONENTS date_time system thread QUIET)

if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find Boost.")
endif()

IF(UNIX)
	IF(CMAKE_COMPILER_IS_GNUCC)
		ADD_DEFINITIONS(-Wall -g -pthread)
	ENDIF(CMAKE_COMPILER_IS_GNUCC)
ENDIF(UNIX)

set(
	HDRS
	./src/NetworkMessage/JoinRefuse.hpp
	./src/NetworkMessage/GameEnd.hpp
	./src/NetworkMessage/JoinAccept.hpp
	./src/NetworkMessage/Leave.hpp
	./src/NetworkMessage/PlayerInput.hpp
	./src/NetworkMessage/Join.hpp
	./src/NetworkMessage/PlayerKilled.hpp
	./src/NetworkMessage/NetworkMessage.hpp
	./src/NetworkMessage/PlayerLeft.hpp
	./src/NetworkMessage/NetworkMessageFactory.hpp
	./src/NetworkMessage/PlayerJoined.hpp
	./src/NetworkMessage/GameStart.hpp
	./src/LocalMap.hpp
	./src/LocalPlayer.hpp
	./src/PlayerList.hpp
	./src/NetworkIO.hpp
	./src/PlayerAnimation.hpp
	./src/Input.hpp
	./src/RemotePlayer.hpp
	./src/GameClient/Listener.hpp
	./src/GameClient/Connector.hpp
	./src/BombManager.hpp
	./src/SimpleCamera.hpp
	./src/Pyramid.hpp
	./src/ExplosionListener.hpp
	./src/Bomb.hpp
	./src/ExplosionManager.hpp
	./src/SensorFusionDevice.hpp
	./src/PlayerEventListener.hpp
	./src/OgrePlayerList.hpp
	./src/Game.hpp
	./src/Block.hpp
	./src/Map.hpp
	./src/CameraManager.hpp
	./src/GameWindow.hpp
	./src/Explosion.hpp
	./src/OculusCamera.hpp
	./src/OgrePlayer.hpp
	./src/Cube.hpp
	./src/FloorPanel.hpp
	./src/SensorFusionListener.hpp
	./src/BlockFactory.hpp
	./src/Player.hpp

)

set(
	SRCS
	./src/SimpleCamera.cpp
	./src/PlayerList.cpp
	./src/NetworkMessage/GameStart.cpp
	./src/NetworkMessage/JoinAccept.cpp
	./src/NetworkMessage/PlayerJoined.cpp
	./src/NetworkMessage/PlayerLeft.cpp
	./src/NetworkMessage/NetworkMessageFactory.cpp
	./src/NetworkMessage/NetworkMessage.cpp
	./src/NetworkMessage/PlayerInput.cpp
	./src/NetworkMessage/JoinRefuse.cpp
	./src/NetworkMessage/Leave.cpp
	./src/NetworkMessage/Join.cpp
	./src/NetworkMessage/GameEnd.cpp
	./src/NetworkMessage/PlayerKilled.cpp
	./src/Explosion.cpp
	./src/Game.cpp
	./src/NetworkIO.cpp
	./src/OculusCamera.cpp
	./src/LocalMap.cpp
	./src/BombManager.cpp
	./src/GameClient/Connector.cpp
	./src/GameClient/Listener.cpp
	./src/RemotePlayer.cpp
	./src/CameraManager.cpp
	./src/Map.cpp
	./src/Player.cpp
	./src/OgrePlayer.cpp
	./src/LocalPlayer.cpp
	./src/GameWindow.cpp
	./src/Bomb.cpp
	./src/FloorPanel.cpp
	./src/Cube.cpp
	./src/SensorFusionDevice.cpp
	./src/Input.cpp
	./src/PlayerAnimation.cpp
	./src/OgrePlayerList.cpp
	./src/ExplosionManager.cpp
	./src/Block.cpp
	./src/Pyramid.cpp
	./src/BlockFactory.cpp
	./main.cpp
)

include_directories(
	${Boost_INCLUDE_DIRS}
	${OIS_INCLUDE_DIRS}
	${OGRE_INCLUDE_DIRS}
	${OGRE_SAMPLES_INCLUDEPATH}
	${BULLET_INCLUDE_DIRS}
	${OGREBULLET_INCLUDE_DIRS}
	${LIBOVR_INCLUDE_DIR}
)

add_executable(pairOculus WIN32 ${HDRS} ${SRCS})

set_target_properties(pairOculus PROPERTIES DEBUG_POSTFIX _d)

target_link_libraries(pairOculus ${Boost_LIBRARIES} ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${BULLET_LIBRARIES} ${OGREBULLET_LIBRARIES} ${LIBOVR_LIBRARIES})

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/bin)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/media)

# post-build copy for win32
if(WIN32 AND NOT MINGW)
	add_custom_command( TARGET pairOculus PRE_BUILD
	COMMAND if not exist .\\dist\\bin mkdir .\\dist\\bin )
	add_custom_command( TARGET pairOculus POST_BUILD
	COMMAND copy \"$(TargetPath)\" .\\dist\\bin )
endif(WIN32 AND NOT MINGW)

if(MINGW OR UNIX)
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/dist/bin)
endif(MINGW OR UNIX)

if(WIN32)

	install(
		TARGETS pairOculus
		RUNTIME DESTINATION bin
		CONFIGURATIONS All
	)

	install(
		DIRECTORY ${CMAKE_SOURCE_DIR}/dist/Media
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo Debug
	)

	install(
		FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
	)

	install(
		FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins_d.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources_d.cfg
		DESTINATION bin
		CONFIGURATIONS Debug
	)

	# NOTE: for the 1.7.1 sdk the OIS dll is called OIS.dll instead of libOIS.dll
	# so you'll have to change that to make it work with 1.7.1
	install(
		FILES ${OGRE_PLUGIN_DIR_REL}/OgreMain.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_Direct3D9.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_GL.dll
		${OGRE_PLUGIN_DIR_REL}/libOIS.dll
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
	)

	install(
		FILES ${OGRE_PLUGIN_DIR_DBG}/OgreMain_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_Direct3D9_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_GL_d.dll
		${OGRE_PLUGIN_DIR_DBG}/libOIS_d.dll
		DESTINATION bin
		CONFIGURATIONS Debug
	)

	# as of sdk 1.7.2 we need to copy the boost dll's as well
	# because they're not linked statically (it worked with 1.7.1 though)
	install(
		FILES ${Boost_DATE_TIME_LIBRARY_RELEASE}
		${Boost_THREAD_LIBRARY_RELEASE}
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
	)

	install(
		FILES ${Boost_DATE_TIME_LIBRARY_DEBUG}
		${Boost_THREAD_LIBRARY_DEBUG}
		DESTINATION bin
		CONFIGURATIONS Debug
	)
endif(WIN32)

if(UNIX)

	install(
		TARGETS pairOculus
		RUNTIME DESTINATION bin
		CONFIGURATIONS All
	)

	install(
		DIRECTORY ${CMAKE_SOURCE_DIR}/dist/media
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo Debug
	)

	install(
		FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo Debug
	)

endif(UNIX)
