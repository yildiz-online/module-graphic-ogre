mkdir src/main/scripts/ogre/build
cd src/main/scripts/ogre/build

cmake . -DCMAKE_BUILD_TYPE="Release" -DFREETYPE_FT2BUILD_INCLUDE_DIR="/home/moussa/dev/prj/module-graphic-ogre/src/main/scripts/ogre/Dependencies/include/freetype" -DCMAKE_PREFIX_PATH="/home/moussa/dev/prj/module-graphic-ogre/src/main/scripts/ogre/Dependencies/Release" -DOGRE_INSTALL_DOCS=FALSE -DOGRE_BUILD_SAMPLES=FALSE -DOGRE_INSTALL_SAMPLES=FALSE -DOGRE_BUILD_PLUGIN_OCTREE=FALSE -DOGRE_BUILD_PLUGIN_BSP=FALSE -DOGRE_BUILD_COMPONENT_PAGING=FALSE -DOGRE_BUILD_COMPONENT_PROPERTY=FALSE -DOGRE_BUILD_PLUGIN_PCZ=FALSE -DOGRE_BUILD_COMPONENT_TERRAIN=FALSE -DOGRE_BUILD_COMPONENT_VOLUME=FALSE -DOGRE_BUILD_RENDERSYSTEM_D3D9=FALSE -DOGRE_BUILD_RENDERSYSTEM_D3D11=FALSE -DCMAKE_INSTALL_PREFIX="release" -DBUILD_SAMPLES=FALSE -DCMAKE_TOOLCHAIN_FILE=mingw-toolchain.cmake

make install
make clean

rm -R *

cp /home/moussa/dev/prj/module-graphic-ogre/src/main/scripts/ogre/release/win64/bin/Release/OgreMain.dll /home/moussa/dev/prj/module-graphic-ogre/target/classes/win64/libOgreMain.dll
cp /home/moussa/dev/prj/module-graphic-ogre/src/main/scripts/ogre/release/win64/bin/Release/OgreOverlay.dll /home/moussa/dev/prj/module-graphic-ogre/target/classes/win64/libOgreOverlay.dll
cp /home/moussa/dev/prj/module-graphic-ogre/src/main/scripts/ogre/release/win64/bin/Release/OgreRTShaderSystem.dll /home/moussa/dev/prj/module-graphic-ogre/target/classes/win64/libOgreRTShaderSystem.dll
cp /home/moussa/dev/prj/module-graphic-ogre/src/main/scripts/ogre/release/win64/bin/Release/Plugin_ParticleFX.dll /home/moussa/dev/prj/module-graphic-ogre/target/classes/win64/ParticleFX.dll
cp /home/moussa/dev/prj/module-graphic-ogre/src/main/scripts/ogre/release/win64/bin/Release/RenderSystem_GL.dll /home/moussa/dev/prj/module-graphic-ogre/target/classes/win64/RenderSystem_GL.dll







