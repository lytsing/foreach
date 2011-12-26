cmake_minimum_required(VERSION 2.8)

PROJECT (foreach)

SET(SRC src/foreach.cpp src/subst.cpp)

SET_SOURCE_FILES_PROPERTIES (${SRCS} COMPILE_FLAGS -g )

#ADD_DEFINITIONS(-g -O2 -fsigned-char -freg-struct-return -Wall -W -Wshadow -Wstrict-prototypes -Wpointer-arith -Wcast-qual -Winline -Werror)
ADD_DEFINITIONS(-g -O2 -Wall)

ADD_EXECUTABLE (foreach ${SRC})

# Installation of the program
INSTALL(TARGETS foreach
        DESTINATION "bin"
        PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

