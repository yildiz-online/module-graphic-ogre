cd src/main/scripts/ogre/build

cmake ../ -DFREETYPE_INCLUDE_DIR="/home/moussa/dev/prj/module-graphic-ogre/src/main/scripts/ogre/ogredeps/src/freetype/include" -DOGREDEPS_BUILD_OIS=FALSE -DOGREDEPS_BUILD_ZZIPLIB=FALSE -DOGREDEPS_BUILD_AMD_QBS=FALSE -DOGREDEPS_BUILD_NVIDIA_NVAPI=FALSE -DOGRE_BUILD_PLUGIN_CG=FALSE -DCMAKE_CXX_FLAGS="-fPIC" -DCMAKE_BUILD_TYPE="Release" -DOGRE_INSTALL_DOCS=FALSE -DOGRE_BUILD_TOOLS=FALSE -DOGRE_INSTALL_SAMPLES=FALSE -DOGRE_BUILD_PLUGIN_OCTREE=FALSE -DOGRE_BUILD_PLUGIN_BSP=FALSE -DOGRE_BUILD_COMPONENT_PAGING=FALSE -DOGRE_BUILD_COMPONENT_PROPERTY=FALSE -DOGRE_BUILD_PLUGIN_PCZ=FALSE -DOGRE_BUILD_COMPONENT_TERRAIN=FALSE -DOGRE_BUILD_COMPONENT_VOLUME=FALSE -DOGRE_BUILD_RENDERSYSTEM_D3D9=FALSE -DOGRE_BUILD_RENDERSYSTEM_D3D11=FALSE -DCMAKE_INSTALL_PREFIX="../release/linux64/" -DBUILD_SAMPLES=FALSE -G "Unix Makefiles"

make install
make clean

rm -R *

cp /home/moussa/dev/prj/module-graphic-ogre/src/main/scripts/ogre/release/linux64/lib/libOgreMain.so.1.9.0 /home/moussa/dev/prj/module-graphic-ogre/target/classes/linux64/libOgreMain.so
cp /home/moussa/dev/prj/module-graphic-ogre/src/main/scripts/ogre/release/linux64/lib/libOgreOverlay.so.1.9.0 /home/moussa/dev/prj/module-graphic-ogre/target/classes/linux64/libOgreOverlay.so
cp /home/moussa/dev/prj/module-graphic-ogre/src/main/scripts/ogre/release/linux64/lib/libOgreRTShaderSystem.so.1.9.0 /home/moussa/dev/prj/module-graphic-ogre/target/classes/linux64/libOgreRTShaderSystem.so
cp /home/moussa/dev/prj/module-graphic-ogre/src/main/scripts/ogre/release/linux64/lib/OGRE/Plugin_ParticleFX.so.1.9.0 /home/moussa/dev/prj/module-graphic-ogre/target/classes/linux64/Plugin_ParticleFX.so
cp /home/moussa/dev/prj/module-graphic-ogre/src/main/scripts/ogre/release/linux64/lib/OGRE/RenderSystem_GL.so.1.9.0 /home/moussa/dev/prj/module-graphic-ogre/target/classes/linux64/RenderSystem_GL.so

