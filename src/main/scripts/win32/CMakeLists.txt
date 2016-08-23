cmake_minimum_required (VERSION 2.8.6)
project (yildiz_native_ogre)
 
set(CMAKE_CXX_FLAGS "-O2")

set(CMAKE_SHARED_LINKER_FLAGS "-Xlinker --add-stdcall-alias")

include_directories("boost1.58")
include_directories("ogre/include/OGRE")
include_directories("physfs/include")
include_directories("java/include")
include_directories("java/include/win32")

set(CMAKE_SHARED_LINKER_FLAGS "-Xlinker --add-stdcall-alias")
 
file(
        GLOB_RECURSE
        source_files
        ${CMAKE_SOURCE_DIR}/../../c++/*.cpp
        ${CMAKE_SOURCE_DIR}/../../c++/*.c
        ${CMAKE_SOURCE_DIR}/../../includes/*.hpp
        ${CMAKE_SOURCE_DIR}/../../includes/*.h
)
    
add_library(yildizogre SHARED ${source_files})
target_link_libraries(yildizogre ${CMAKE_SOURCE_DIR}/ogre/lib/libOgreMain.dll.a)
target_link_libraries(yildizogre ${CMAKE_SOURCE_DIR}/ogre/lib/libOgreOverlay.dll.a)
target_link_libraries(yildizogre ${CMAKE_SOURCE_DIR}/physfs/lib/libphysfs.dll.a)
