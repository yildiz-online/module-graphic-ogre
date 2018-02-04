cmake . \
-DCMAKE_BUILD_TYPE=Release \
-DPHYSFS_INCLUDE_DIR="physicsfs/linux64/include" \
-DPHYSFS_LIBRARY="physicsfs/linux64/lib/libphysfs.so" \
-DLIBRARY_OUTPUT_PATH="../../../../target/classes/linux64" \
-G "Unix Makefiles"

make
r1=$?

rm -R CMakeFiles
rm -R ogre3d
rm -R boost
rm -R physicsfs
rm CMakeCache.txt
rm cmake_install.cmake
rm Makefile

return $r1
