cmake . -DCMAKE_BUILD_TYPE=Release -DCMAKE_MODULE_PATH=/usr/share/OGRE/cmake/modules -DLIBRARY_OUTPUT_PATH="../../../../target/classes/linux64" -G "Unix Makefiles"

make
r1=$?

rm -R CMakeFiles
rm CMakeCache.txt
rm cmake_install.cmake
rm Makefile

return $r1
