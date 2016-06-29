mkdir src/main/scripts/physicsFS/build
cd src/main/scripts/physicsFS/build


cmake ../ -DPHYSFS_ARCHIVE_SLB=FALSE -DPHYSFS_ARCHIVE_QPAK=FALSE -DPHYSFS_ARCHIVE_MVL=FALSE -DPHYSFS_ARCHIVE_WAD=FALSE -DPHYSFS_ARCHIVE_GRP=FALSE -DPHYSFS_ARCHIVE_7Z=FALSE -DPHYSFS_ARCHIVE_ZIP=FALSE -DPHYSFS_BUILD_TEST=FALSE -DCMAKE_INSTALL_PREFIX="../release/win64/" -DLIBRARY_OUTPUT_PATH="" -DCMAKE_TOOLCHAIN_FILE=../../mingw-toolchain.cmake

make install
make clean

rm -R *
mkdir /home/moussa/dev/prj/module-graphic-ogre/target/classes/win64

cp  /home/moussa/dev/prj/module-graphic-ogre/src/main/scripts/physicsFS/release/win64/bin/libphysfs.dll /home/moussa/dev/prj/module-graphic-ogre/target/classes/win64/libphysfs.dll
