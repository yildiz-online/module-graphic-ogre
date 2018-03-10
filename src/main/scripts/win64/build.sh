mkdir $PWD/build
cd build

cmake ../ -DCMAKE_BUILD_TYPE=Release -DCMAKE_COLOR_MAKEFILE=on -DLIBRARY_OUTPUT_PATH="../../../../../target/classes/win64" -DCMAKE_TOOLCHAIN_FILE=mingw-toolchain.cmake

make
r1=$?

cd ..
cp physicsfs/win64/bin/libphysfs.dll ../../../../target/classes/win64
cp ogre3d/win64/bin/OgreMain.dll ../../../../target/classes/win64
cp ogre3d/win64/bin/OgreOverlay.dll ../../../../target/classes/win64
cp ogre3d/win64/bin/Plugin_ParticleFX.dll ../../../../target/classes/win64
cp ogre3d/win64/bin/RenderSystem_GL.dll ../../../../target/classes/win64
rm -R build

return $r1


