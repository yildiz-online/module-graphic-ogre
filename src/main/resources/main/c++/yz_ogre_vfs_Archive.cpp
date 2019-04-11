/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 * Copyright (c) 2019 Grégory Van den Borre
 *
 * More infos available: https://engine.yildiz-games.be
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without
 * limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT  HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  SOFTWARE.
 */

#include "../includes/yz_ogre_vfs_Archive.hpp"

bool yz::ogre::vfs::Archive::exists(const Ogre::String& filename) const {
    LOG_FUNCTION
    return this->vfs->exists(mName + '/' + filename);
}

Ogre::DataStreamPtr yz::ogre::vfs::Archive::open(const Ogre::String& filename, bool append) const {
    LOG_FUNCTION
    Ogre::String fullName = mName + '/' + filename;
    return Ogre::DataStreamPtr(new yz::ogre::vfs::DataStream(fullName, new yz::physfs::File(filename)));
}

void yz::ogre::vfs::Archive::listInfoRecursive(const Ogre::String& base, bool recursive, bool dirs, Ogre::FileInfoListPtr fileInfoList) const {
    LOG_FUNCTION
    Ogre::String baseDir = mName + '/' + base;
    Ogre::StringVector files = this->vfs->enumerateFiles(baseDir);

    Ogre::FileInfo fileInfo;
    fileInfo.archive = this;
    fileInfo.path = base;
    fileInfo.compressedSize = 0;

    // iterate over all files and directories in the given directory
    for (Ogre::StringVector::iterator it = files.begin(); it != files.end(); ++it) {
         fileInfo.basename = *it;
         fileInfo.filename = base + *it;
         if (this->vfs->isDirectory(*it)) {
             if (dirs) {
                 fileInfo.uncompressedSize = 0;
                 fileInfoList->push_back(fileInfo);
             }
             if (recursive) {
                 listInfoRecursive(base + *it + '/', recursive, dirs, fileInfoList);
             }
         } else {
             if (!dirs) {
                 // get file size
                 yz::physfs::File* file = new yz::physfs::File(mName + '/' + fileInfo.filename);
                 fileInfo.uncompressedSize = (size_t) file->getSize();
                 file->close();

                 fileInfoList->push_back(fileInfo);
             }
         }
     }
 }

void yz::ogre::vfs::Archive::listRecursive(const Ogre::String& base, bool recursive, bool dirs, Ogre::StringVectorPtr fileList) const {
     LOG_FUNCTION

     Ogre::String baseDir = mName + '/' + base;
     Ogre::StringVector files = this->vfs->enumerateFiles(baseDir);

     // iterate over all files and directories in the given directory
     for (Ogre::StringVector::iterator it = files.begin(); it != files.end(); ++it) {
         if (this->vfs->isDirectory(*it)) {
             if (dirs) {
                 fileList->push_back(base + *it);
             }
             if (recursive) {
                 listRecursive(base + *it + '/', recursive, dirs, fileList);
             }
         } else {
             if (!dirs) {
                 fileList->push_back(base + *it);
             }
         }
     }
 }

Ogre::FileInfoListPtr yz::ogre::vfs::Archive::listFileInfo(bool recursive, bool dirs) const {
     LOG_FUNCTION
     Ogre::FileInfoListPtr fileInfoList(new Ogre::FileInfoList());
     listInfoRecursive("", recursive, dirs, fileInfoList);
     return fileInfoList;
 }

Ogre::StringVectorPtr yz::ogre::vfs::Archive::list(bool recursive, bool dirs) const {
     LOG_FUNCTION
     Ogre::StringVectorPtr fileList(new Ogre::StringVector());
     listRecursive("", recursive, dirs, fileList);
     return fileList;
 }

Ogre::StringVectorPtr yz::ogre::vfs::Archive::find(const Ogre::String& pattern, bool recursive, bool dirs) const {
     LOG_FUNCTION
     Ogre::StringVectorPtr fileList = list(recursive, dirs);
     Ogre::StringVectorPtr ret(new Ogre::StringVector());

     for (Ogre::StringVector::iterator it = fileList->begin(); it != fileList->end(); ++it) {
         if (Ogre::StringUtil::match(*it, pattern))
             ret->push_back(*it);
     }
     return ret;
 }

Ogre::FileInfoListPtr yz::ogre::vfs::Archive::findFileInfo(const Ogre::String& pattern, bool recursive, bool dirs) const {
     LOG_FUNCTION
     Ogre::FileInfoListPtr fileList = const_cast<yz::ogre::vfs::Archive*>(this)->listFileInfo(recursive, dirs);
     Ogre::FileInfoListPtr ret(new Ogre::FileInfoList());

     for (Ogre::FileInfoList::iterator it = fileList->begin(); it != fileList->end(); ++it) {
         if (Ogre::StringUtil::match(it->filename, pattern))
             ret->push_back(*it);
     }

     return ret;
 }
