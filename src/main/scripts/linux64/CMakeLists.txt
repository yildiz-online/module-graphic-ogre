cmake_minimum_required (VERSION 2.8.0)
project (yildiz_native_ogre)

set(CMAKE_CXX_FLAGS "-O2 -fPIC")

set(OGRE "${CMAKE_SOURCE_DIR}/../ogre/release/linux64")
set(OGRE_INCLUDE "${OGRE}/include")
set(PHYSFS "${CMAKE_SOURCE_DIR}/../physicsFS/release/linux64")
    
include_directories("/home/moussa/dev/tools/java-linux64/include")
include_directories("/home/moussa/dev/tools/java-linux64/include/linux")

include_directories("${OGRE_INCLUDE}/OGRE")
include_directories("${OGRE_INCLUDE}/OGRE/Overlay")
include_directories("${PHYSFS}/include")
include_directories("${CMAKE_SOURCE_DIR}/../boost-1-60-0")

file(
        GLOB_RECURSE
        source_files
        ${CMAKE_SOURCE_DIR}/../../c++/*.cpp
        ${CMAKE_SOURCE_DIR}/../../c++/*.c
        ${CMAKE_SOURCE_DIR}/../../includes/*.hpp
        ${CMAKE_SOURCE_DIR}/../../includes/*.h
)

    add_library(yildizogre SHARED ${source_files})

    target_link_libraries(yildizogre ${OGRE}/lib/libOgreMain.so)
    target_link_libraries(yildizogre ${OGRE}/lib/libOgreOverlay.so)
    target_link_libraries(yildizogre ${PHYSFS}/lib/libphysfs.so)
