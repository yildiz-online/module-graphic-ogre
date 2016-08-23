//        This file is part of the Yildiz-Online project, licenced under the MIT License
//        (MIT)
//
//        Copyright (c) 2016 Grégory Van den Borre
//
//        More infos available: http://yildiz.bitbucket.org
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
//        of this software and associated documentation files (the "Software"), to deal
//        in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
//        furnished to do so, subject to the following conditions:
//
//        The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
//        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//        SOFTWARE.

/**
*@author Grégory Van den Borre
*/

#include "../includes/PhysFSOgre.h"
#include "../includes/PhysFS++.h"

#include "../includes/stdafx.h"
#include <OgreArchiveFactory.h>
#include <OgreArchive.h>
#include <OgreArchiveManager.h>
#include <OgreDataStream.h>
#include <OgreString.h>
#include "OgreStableHeaders.h"

namespace PhysFS {
/** Datastream implementation for Ogre */
class DataStream: public Ogre::DataStream {
public:
    DataStream(const Ogre::String& filename);
    DataStream(const Ogre::String& name, const Ogre::String& filename);
    ~DataStream();

    size_t read(void* buf, size_t count);
    void skip(long count);
    void seek(size_t pos);
    size_t tell() const;
    bool eof() const;
    void close();

private:
    PHYSFS_File* file;
};

DataStream::DataStream(const Ogre::String& filename) {
    LOG_FUNCTION
    file = PHYSFS_openRead(filename.c_str());
    if (!file)
        throw Exception(PHYSFS_getLastError());
    mSize = (size_t) PHYSFS_fileLength(file);
}

DataStream::DataStream(const Ogre::String& name, const Ogre::String& filename) :
        Ogre::DataStream(name) {
    LOG_FUNCTION
    file = PHYSFS_openRead(filename.c_str());
    if (!file)
        throw Exception(PHYSFS_getLastError());
    mSize = (size_t) PHYSFS_fileLength(file);
}

DataStream::~DataStream() {
    LOG_FUNCTION
    close();
}

size_t DataStream::read(void* buf, size_t count) {
    LOG_FUNCTION
    int64 read = PHYSFS_read(file, buf, 1, (PHYSFS_uint32) count);
    if (read == -1) {
        throw Exception(PHYSFS_getLastError());
    }
    return size_t(read);
}

void DataStream::seek(size_t pos) {
    LOG_FUNCTION
    if (!PHYSFS_seek(file, pos))
        throw Exception(PHYSFS_getLastError());
}

size_t DataStream::tell() const {
    LOG_FUNCTION
    return (size_t) PHYSFS_tell(file);
}

void DataStream::skip(long count) {
    LOG_FUNCTION
    size_t pos = tell() + count;
    seek(pos);
}

bool DataStream::eof() const {
    LOG_FUNCTION
    return PHYSFS_eof(file) != 0;
}

void DataStream::close() {
    LOG_FUNCTION
    if (file) {
        PHYSFS_close(file);
        file = 0;
    }
}

/** Archive implementation for Ogre */
class Archive: public Ogre::Archive {
public:
    Archive(const Ogre::String& name, const Ogre::String& type) :
            Ogre::Archive(name, type) {
        LOG_FUNCTION
    }

    /** PhysFS is case sensitive in general */
    bool isCaseSensitive() const {
        LOG_FUNCTION
        return true;
    }

    /** Nothing to load */
    void load() {
        LOG_FUNCTION
    }
    /** Nothing to unload */
    void unload() {
        LOG_FUNCTION
    }

    inline time_t getModifiedTime(const Ogre::String& file) {
        LOG_FUNCTION
        return PHYSFS_getLastModTime(file.c_str());
    }

    Ogre::DataStreamPtr open(const Ogre::String& filename, bool append) const;

    Ogre::StringVectorPtr list(bool recursive = true, bool dirs = false);
    Ogre::FileInfoListPtr listFileInfo(
        bool recursive = true,
        bool dirs = false);

    Ogre::StringVectorPtr find(const Ogre::String& pattern, bool recursive =
            true, bool dirs = false);

    bool exists(const Ogre::String& filename);

    Ogre::FileInfoListPtr findFileInfo(
        const Ogre::String& pattern,
        bool recursive = true,
        bool dirs = false) const;

private:
    void listInfoRecursive(
        const Ogre::String& base,
        bool recursive,
        bool dirs,
        Ogre::FileInfoListPtr fileInfoList);
    void listRecursive(
        const Ogre::String& base,
        bool recursive,
        bool dirs,
        Ogre::StringVectorPtr fileList);
};

bool Archive::exists(const Ogre::String& filename) {
    LOG_FUNCTION
    return PhysFS::exists(mName + '/' + filename);
}

Ogre::DataStreamPtr Archive::open(
    const Ogre::String& filename,
    bool append) const {
    LOG_FUNCTION
    Ogre::String fullName = mName + '/' + filename;
    return Ogre::DataStreamPtr(new DataStream(filename, fullName));
}

void Archive::listInfoRecursive(
    const Ogre::String& base,
    bool recursive,
    bool dirs,
    Ogre::FileInfoListPtr fileInfoList) {
    LOG_FUNCTION

    Ogre::String baseDir = mName + '/' + base;
    StringVector files = enumerateFiles(baseDir);

    Ogre::FileInfo fileInfo;
    fileInfo.archive = this;
    fileInfo.path = base;
    fileInfo.compressedSize = 0;

    // iterate over all files and directories in the given directory
    for (StringVector::iterator it = files.begin(); it != files.end(); ++it) {
        fileInfo.basename = *it;
        fileInfo.filename = base + *it;
        if (isDirectory(*it)) {
            if (dirs) {
                fileInfo.uncompressedSize = 0;
                fileInfoList->push_back(fileInfo);
            }
            if (recursive)
                listInfoRecursive(base + *it + '/', recursive, dirs,
                        fileInfoList);
        } else {
            if (!dirs) {
                // get file size
                PHYSFS_File* file = PHYSFS_openRead(
                        (mName + '/' + fileInfo.filename).c_str());
                fileInfo.uncompressedSize = (size_t) PHYSFS_fileLength(file);
                PHYSFS_close(file);

                fileInfoList->push_back(fileInfo);
            }
        }
    }
}

void Archive::listRecursive(
    const Ogre::String& base,
    bool recursive,
    bool dirs,
    Ogre::StringVectorPtr fileList) {
    LOG_FUNCTION

    Ogre::String baseDir = mName + '/' + base;
    StringVector files = enumerateFiles(baseDir);

    // iterate over all files and directories in the given directory
    for (StringVector::iterator it = files.begin(); it != files.end(); ++it) {
        if (isDirectory(*it)) {
            if (dirs)
                fileList->push_back(base + *it);
            if (recursive)
                listRecursive(base + *it + '/', recursive, dirs, fileList);
        } else {
            if (!dirs)
                fileList->push_back(base + *it);
        }
    }
}

Ogre::FileInfoListPtr Archive::listFileInfo(bool recursive, bool dirs) {
    LOG_FUNCTION
    Ogre::FileInfoListPtr fileInfoList(new Ogre::FileInfoList());
    listInfoRecursive("", recursive, dirs, fileInfoList);
    return fileInfoList;
}

Ogre::StringVectorPtr Archive::list(bool recursive, bool dirs) {
    LOG_FUNCTION
    Ogre::StringVectorPtr fileList(new Ogre::StringVector());
    listRecursive("", recursive, dirs, fileList);
    return fileList;
}

Ogre::StringVectorPtr Archive::find(
    const Ogre::String& pattern,
    bool recursive,
    bool dirs) {
    LOG_FUNCTION
    Ogre::StringVectorPtr fileList = list(recursive, dirs);
    Ogre::StringVectorPtr ret(new Ogre::StringVector());

    for (Ogre::StringVector::iterator it = fileList->begin();
            it != fileList->end(); ++it) {
        if (Ogre::StringUtil::match(*it, pattern))
            ret->push_back(*it);
    }

    return ret;
}

Ogre::FileInfoListPtr Archive::findFileInfo(
    const Ogre::String& pattern,
    bool recursive,
    bool dirs) const {
    LOG_FUNCTION
    Ogre::FileInfoListPtr fileList = const_cast<Archive*>(this)->listFileInfo(
            recursive, dirs);
    Ogre::FileInfoListPtr ret(new Ogre::FileInfoList());

    for (Ogre::FileInfoList::iterator it = fileList->begin();
            it != fileList->end(); ++it) {
        if (Ogre::StringUtil::match(it->filename, pattern))
            ret->push_back(*it);
    }

    return ret;
}

/** ArchiveFactory for PhysFS */
class ArchiveFactory: public Ogre::ArchiveFactory {
public:
    /** ArchiveFactory typename: "Package" */
    const Ogre::String& getType() const {
        LOG_FUNCTION
        static const Ogre::String type = "Package";
        return type;
    }

    Ogre::Archive* createInstance(const Ogre::String& name, bool readOnly) {
        LOG_FUNCTION
        return new Archive(name, getType());
    }

    void destroyInstance(Ogre::Archive* instance) {
        LOG_FUNCTION
        delete instance;
    }

    static ArchiveFactory* getInstance() {
        LOG_FUNCTION
        static ArchiveFactory instance;
        return &instance;
    }

private:
    ArchiveFactory() {
        LOG_FUNCTION
    }
    ArchiveFactory(const ArchiveFactory& o);
    ArchiveFactory& operator=(const ArchiveFactory& o);
};

void registerPhysFSToOgre() {
    LOG_FUNCTION
    Ogre::ArchiveManager::getSingleton().addArchiveFactory(
            ArchiveFactory::getInstance());
}

}
