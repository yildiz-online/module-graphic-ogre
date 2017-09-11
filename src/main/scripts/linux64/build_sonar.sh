cmake . -DCMAKE_BUILD_TYPE=Release -DCMAKE_MODULE_PATH=/usr/share/OGRE/cmake/modules -DLIBRARY_OUTPUT_PATH="../../../../target/classes/linux64" -G "Unix Makefiles"

build-wrapper-linux-x86-64 --out-dir ../../../../target/sonar-cpp make
r1=$?

rm -R CMakeFiles
rm CMakeCache.txt
rm cmake_install.cmake
rm Makefile

return $r1
