cmake_minimum_required (VERSION 3.0.0)

project (yildiz_native_ogre)

set(CMAKE_CXX_FLAGS "-O2 -fPIC -std=gnu++11")

find_package(PhysFS REQUIRED)
find_package(Java REQUIRED)
find_package(JNI REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/ogre3d/linux64/include/OGRE)
include_directories(${CMAKE_SOURCE_DIR}/boost/linux64/include)
include_directories(${PHYSFS_INCLUDE_DIR})
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

target_link_libraries(yildizogre ${CMAKE_SOURCE_DIR}/ogre3d/linux64/lib/libOgreMain.so)
target_link_libraries(yildizogre ${PHYSFS_LIBRARY})
