cmake_minimum_required (VERSION 2.8.0)

if(WIN32)
    if(MINGW)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")
endif()

# Settings
option(QT5_BUILD "Build with Qt5" true)

# Libraries first

add_subdirectory (libirc/libirc/)
add_subdirectory (libirc/libircclient/)
add_subdirectory (relaybot)

# Packaging code
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Petr Bena")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "relaybot IRC bot")
SET(CPACK_PACKAGE_VENDOR "Petr Bena")
SET(CPACK_PACKAGE_VERSION_MAJOR "1")
SET(CPACK_PACKAGE_VERSION_MINOR "0")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
INCLUDE(CPack)
