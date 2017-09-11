cmake . -DCMAKE_BUILD_TYPE=Release -DLIBRARY_OUTPUT_PATH="../../../../target/classes/win32" -DCMAKE_TOOLCHAIN_FILE=mingw-toolchain.cmake

make
r1=$?

rm -R CMakeFiles
rm Makefile
rm cmake_install.cmake
rm CMakeCache.txt

cp ogre/bin/OgreMain.dll ../../../../target/classes/win32/OgreMain.dll
cp ogre/bin/OgreOverlay.dll ../../../../target/classes/win32/OgreOverlay.dll
cp ogre/bin/OgreRTShaderSystem.dll ../../../../target/classes/win32/OgreRTShaderSystem.dll
cp ogre/bin/Plugin_ParticleFX.dll ../../../../target/classes/win32/Plugin_ParticleFX.dll
cp ogre/bin/RenderSystem_GL.dll ../../../../target/classes/win32/RenderSystem_GL.dll
cp physfs/bin/libphysfs.dll ../../../../target/classes/win32/libphysfs.dll
cp libstdc++-6.dll ../../../../target/classes/win32/libstdc++-6.dll
cp libgcc_s_sjlj-1.dll ../../../../target/classes/win32/libgcc_s_sjlj-1.dll

rm $r1


