cmake_minimum_required (VERSION 2.8.0)
project (yildiz_native_ogre)

set(CMAKE_CXX_FLAGS "-O2 -fPIC -std=gnu++11")

find_package(Boost REQUIRED)
find_package(OGRE REQUIRED)
find_package(PhysFS REQUIRED)
find_package(Java REQUIRED)
find_package(JNI REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OGRE_INCLUDE_DIRS})
include_directories(${PhysFS_INCLUDE_DIRS})
include_directories(${JNI_INCLUDE_DIRS})
include_directories(${JNI_INCLUDE_DIRS}/linux)

file(
        GLOB_RECURSE
        source_files
        ${CMAKE_SOURCE_DIR}/../../c++/*.cpp
        ${CMAKE_SOURCE_DIR}/../../c++/*.c
        ${CMAKE_SOURCE_DIR}/../../includes/*.hpp
        ${CMAKE_SOURCE_DIR}/../../includes/*.h
)

add_library(yildizogre SHARED ${source_files})

target_link_libraries(yildizogre ${OGRE_LIBRARIES})
target_link_libraries(yildizogre ${PHYSFS_LIBRARY})
