mkdir src/main/scripts/ogredeps/build
cd src/main/scripts/ogredeps/build

cmake . -DCMAKE_BUILD_TYPE="Release" -DOGREDEPS_BUILD_RAPIDJSON=FALSE -DOGREDEPS_BUILD_SDL2=FALSE -DOGREDEPS_BUILD_ZZIPLIB=FALSE -DOGREDEPS_BUILD_AMD_QBS=FALSE -DOGREDEPS_BUILD_NVIDIA_NVAPI=FALSE -DCMAKE_INSTALL_PREFIX="Dependencies/" -DCMAKE_TOOLCHAIN_FILE=mingw-toolchain.cmake

make install
make clean

rm -R *
