cd %~dp0..\physicsFS
mkdir build
cd build



cmake ../ -DPHYSFS_ARCHIVE_SLB=FALSE -DPHYSFS_ARCHIVE_QPAK=FALSE -DPHYSFS_ARCHIVE_MVL=FALSE -DPHYSFS_ARCHIVE_WAD=FALSE -DPHYSFS_ARCHIVE_GRP=FALSE -DPHYSFS_ARCHIVE_7Z=FALSE -DPHYSFS_ARCHIVE_ZIP=FALSE -DPHYSFS_BUILD_TEST=FALSE -DCMAKE_INSTALL_PREFIX="../release/win64/" -DLIBRARY_OUTPUT_PATH="" -G "MinGW Makefiles"

mingw32-make install
mingw32-make clean

REM mkdir target/classes/win64


REM cp  src/main/scripts/physicsFS/release/win64/bin/libphysfs.dll target/classes/win64/libphysfs.dll

