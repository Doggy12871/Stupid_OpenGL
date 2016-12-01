CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8 FATAL_ERROR)
PROJECT(COLLISION)

SET(COLLISION_SRCS main.cpp display.cpp draw.cpp update.cpp game.cpp)

IF (WIN32)
    SET(COLLISION_EXE_NAME collision)
ELSEIF (UNIX)
    SET(COLLISION_EXE_NAME collision)
ENDIF ()

ADD_EXECUTABLE(${COLLISION_EXE_NAME} ${COLLISION_SRCS})

IF (WIN32)
    SET(COLLISION_LIBS freeglut_static glu32 opengl32 winmm gdi32)
ELSEIF (UNIX)
    MESSAGE(FATAL_ERROR "Unix detected, please tell lzh the arguments you're using.")
ENDIF ()

TARGET_LINK_LIBRARIES (${COLLISION_EXE_NAME} ${COLLISION_LIBS})

IF (WIN32)
    SET(COLLISION_FLAGS -static)
ELSEIF (UNIX)
    SET(COLLISION_FLAGS -static)
ENDIF ()

SET_TARGET_PROPERTIES(${COLLISION_EXE_NAME} PROPERTIES COMPILE_FLAGS ${COLLISION_FLAGS})

IF (WIN32)
    ADD_DEFINITIONS(-DFREEGLUT_STATIC)
ELSEIF (UNIX)
    
ENDIF ()