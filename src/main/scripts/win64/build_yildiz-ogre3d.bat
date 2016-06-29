cd %~dp0
mkdir build
cd build


cmake ../ -DCMAKE_BUILD_TYPE=Release -DCMAKE_COLOR_MAKEFILE=on -DLIBRARY_OUTPUT_PATH="../../../../../target/classes/win64" -G "MinGW Makefiles"

mingw32-make


