cd %~dp0..\ogre
mkdir build
cd build

cmake ../ -DCMAKE_BUILD_TYPE="Release" -DFREETYPE_FT2BUILD_INCLUDE_DIR="../Dependencies/include/freetype" -DCMAKE_PREFIX_PATH="../Dependencies/Release" -DOGRE_INSTALL_DOCS=FALSE -DOGRE_INSTALL_SAMPLES=FALSE -DOGRE_BUILD_PLUGIN_OCTREE=FALSE -DOGRE_BUILD_PLUGIN_BSP=FALSE -DOGRE_BUILD_COMPONENT_PAGING=FALSE -DOGRE_BUILD_COMPONENT_PROPERTY=FALSE -DOGRE_BUILD_PLUGIN_PCZ=FALSE -DOGRE_BUILD_COMPONENT_TERRAIN=FALSE -DOGRE_BUILD_COMPONENT_VOLUME=FALSE -DOGRE_BUILD_RENDERSYSTEM_D3D9=FALSE -DOGRE_BUILD_RENDERSYSTEM_D3D11=FALSE -DCMAKE_INSTALL_PREFIX="../release/win64/" -DBUILD_SAMPLES=FALSE -G "MinGW Makefiles"

mingw32-make install
mingw32-make clean
