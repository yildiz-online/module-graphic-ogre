cd src/main/scripts/physicsFS/build


cmake ../ -DCMAKE_CXX_FLAGS="-fPIC" -DPHYSFS_ARCHIVE_SLB=FALSE -DPHYSFS_ARCHIVE_QPAK=FALSE -DPHYSFS_ARCHIVE_MVL=FALSE -DPHYSFS_ARCHIVE_WAD=FALSE -DPHYSFS_ARCHIVE_GRP=FALSE -DPHYSFS_ARCHIVE_7Z=FALSE -DPHYSFS_ARCHIVE_ZIP=FALSE -DPHYSFS_BUILD_TEST=FALSE -DCMAKE_INSTALL_PREFIX="../release/linux64/" -DLIBRARY_OUTPUT_PATH="" -G "Unix Makefiles"

make install
make clean

rm -R *

mkdir /home/moussa/dev/prj/module-graphic-ogre/target/classes/linux64

cp  /home/moussa/dev/prj/module-graphic-ogre/src/main/scripts/physicsFS/release/linux64/lib/libphysfs.so.2.1.0 /home/moussa/dev/prj/module-graphic-ogre/target/classes/linux64/libphysfs.so

