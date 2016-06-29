cmake_minimum_required (VERSION 2.8.6)
project (yildiz_native_ogre)
 
set(CMAKE_CXX_FLAGS "-O2")
 
set(ROOT "${CMAKE_SOURCE_DIR}/../../../../../..")
set(PRJ "${ROOT}/prj/module_graphic_ogre_native")
 
include_directories("${ROOT}/tools/java-win64/include")
include_directories("${ROOT}/tools/java-win64/include/win32")
include_directories("${CMAKE_SOURCE_DIR}/../ogre/release/win64/Release/include/OGRE")
include_directories("${CMAKE_SOURCE_DIR}/../ogre/release/win64/Release/include/OGRE/Overlay")
include_directories("${CMAKE_SOURCE_DIR}/../Dependencies/include")
include_directories("${CMAKE_SOURCE_DIR}/../PhysicsFS/release/win64/include")
    
set(LIBRARY_OUTPUT_PATH "${PRJ}/target/win64")
set(CMAKE_SHARED_LINKER_FLAGS "-Xlinker --add-stdcall-alias -Wl,--output-def,ogrell.def")
 
file(
        GLOB_RECURSE
        source_files
        ${CMAKE_SOURCE_DIR}/../../c++/*.cpp
        ${CMAKE_SOURCE_DIR}/../../c++/*.c
        ${CMAKE_SOURCE_DIR}/../../includes/*.hpp
        ${CMAKE_SOURCE_DIR}/../../includes/*.h
)
    
add_library(ogre SHARED ${source_files})
target_link_libraries(ogre ${CMAKE_SOURCE_DIR}/../ogre/release/win64/lib/Release/libOgreMain.dll.a)
target_link_libraries(ogre ${CMAKE_SOURCE_DIR}/../ogre/release/win64/lib/Release/libOgreOverlay.dll.a)
target_link_libraries(ogre ${CMAKE_SOURCE_DIR}/../physicsFS/release/win64/lib/libphysfs.a)
