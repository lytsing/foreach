cmake_minimum_required(VERSION 2.8)

PROJECT (foreach)

SET(SRC src/foreach.cpp src/subst.cpp)

SET_SOURCE_FILES_PROPERTIES (${SRCS} COMPILE_FLAGS -g )

ADD_EXECUTABLE (foreach ${SRC})

