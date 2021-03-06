##########################################################################
# build/CMakeLists-Win-msys64.txt of project Collision
# Author : lzh
# Modifier : lzh
# Description : Instruction file for CMake to generate Makefile.
##########################################################################

# Check CMake version

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8 FATAL_ERROR)

# Setup project name

PROJECT(COLLISION)

# Setup executable file name

# Due to the usage of MSYS, that in WIN32 is identical to that in UNIX.
IF (WIN32)
    SET(COLLISION_EXE_NAME collision)
ELSEIF (UNIX)
    SET(COLLISION_EXE_NAME collision)
ENDIF ()

# Setup source files list

SET(COLLISION_SRCS collision.cpp display.cpp draw.cpp update.cpp game.cpp global.cpp event.cpp)

# Generate instruction for target in Makefile

ADD_EXECUTABLE(${COLLISION_EXE_NAME} ${COLLISION_SRCS})

# Setup libraries list

IF (WIN32)
    SET(COLLISION_LIBS glfw3 glu32 opengl32 winmm gdi32 jpeg \"alut.dll\" \"openal.dll\" m)
ELSEIF (UNIX)
    SET(COLLISION_LIBS glfw GL GLU jpeg alut openal m)
ENDIF ()

# Add libraries to link for the target

TARGET_LINK_LIBRARIES (${COLLISION_EXE_NAME} ${COLLISION_LIBS})

# Add flags for the target

IF (WIN32)
    SET_TARGET_PROPERTIES(${COLLISION_EXE_NAME} PROPERTIES LINK_FLAGS -static)
ELSEIF (UNIX)

ENDIF()

# Do miscellaneous things for the target

IF (WIN32)
# In MSYS environments, freeglut is used instead of the original glut,
# which requires a specific definition to switch on usage of the static
# libraries.
    ADD_DEFINITIONS(-DFREEGLUT_STATIC -DCL_SYSTEM_WIN)
ELSEIF (UNIX)
    ADD_DEFINITIONS(-DCL_SYSTEM_UNIX)
ENDIF ()
