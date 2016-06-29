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

#include "../includes/PhysFS++.h"

#include <OgreException.h>
#include "../includes/stdafx.h"

namespace PhysFS {
void init(const char* argv0, bool symLinks) {
    LOG_FUNCTION
    if (!PHYSFS_init(argv0))
        throw Exception(PHYSFS_getLastError());

    PHYSFS_permitSymbolicLinks(symLinks);
}

void deinit() {
    LOG_FUNCTION
    if (!PHYSFS_deinit())
        throw Exception(PHYSFS_getLastError());
}

bool isInit() {
    LOG_FUNCTION
    return PHYSFS_isInit() != 0;
}

StringVector supportedArchiveTypes() {
    LOG_FUNCTION
    const PHYSFS_ArchiveInfo** lst = PHYSFS_supportedArchiveTypes();
    StringVector list;
    for (; *lst != 0; ++lst)
        list.push_back((*lst)->extension);
    return list;
    // lst is static data, don't free
}

StringVector getCdRomDirs() {
    LOG_FUNCTION
    StringVector list;
    char** lst = PHYSFS_getCdRomDirs();
    for (char** l = lst; *l != 0; ++l)
        list.push_back(*l);
    PHYSFS_freeList(lst);
    return list;
}

void addToSearchPath(const std::string& location, bool append) {
    LOG_FUNCTION
    if (!PHYSFS_mount(location.c_str(), NULL, append)) {
        throw Exception(PHYSFS_getLastError());
    }
}

void removeFromSearchPath(const std::string& location) {
    LOG_FUNCTION
    if (!PHYSFS_unmount(location.c_str())) {
        throw Exception(PHYSFS_getLastError());
    }
}

void mount(
    const std::string& location,
    const std::string& mountPoint,
    bool append) {
    LOG_FUNCTION
    if (!PHYSFS_mount(location.c_str(), mountPoint.c_str(), append))
        throw Exception(PHYSFS_getLastError());
}

std::string getMountPoint(const std::string& location) {
    LOG_FUNCTION
    std::string mount = PHYSFS_getMountPoint(location.c_str());
    if (mount.empty())
        throw Exception(PHYSFS_getLastError());
    return mount;
}

StringVector getSearchPath() {
    LOG_FUNCTION
    char** locList = PHYSFS_getSearchPath();
    if (locList == 0)
        throw Exception(PHYSFS_getLastError());

    StringVector list;
    for (char** l = locList; *l != 0; ++l)
        list.push_back(*l);
    PHYSFS_freeList(locList);
    return list;
}

const std::string& getUserDir() {
    LOG_FUNCTION
    // since this won't likely change during one execution, we cache the result
    static const std::string userDir = PHYSFS_getUserDir();
    return userDir;
}

const std::string& getBaseDir() {
    LOG_FUNCTION
    // cache the result
    static const std::string baseDir = PHYSFS_getBaseDir();
    return baseDir;
}

std::string getWriteDir() {
    LOG_FUNCTION
    return PHYSFS_getWriteDir();
}

void setWriteDir(const std::string& dir) {
    LOG_FUNCTION
    if (!PHYSFS_setWriteDir(dir.c_str()))
        throw Exception(PHYSFS_getLastError());
}

void setSaneConfig(
    const std::string& organisation,
    const std::string& appName,
    const std::string& archiveExt,
    bool includeCdDrives,
    bool archivesFirst) {
    LOG_FUNCTION
    if (!PHYSFS_setSaneConfig(organisation.c_str(), appName.c_str(),
            archiveExt.c_str(), includeCdDrives, archivesFirst)) {
        throw Exception(PHYSFS_getLastError());
    }
}

bool exists(const std::string& path) {
    LOG_FUNCTION
    return PHYSFS_getRealDir(path.c_str()) != NULL;
}

bool isDirectory(const std::string& path) {
    LOG_FUNCTION
    PHYSFS_Stat statbuf;
    PHYSFS_stat(path.c_str(), &statbuf);
    return statbuf.filetype == PHYSFS_FILETYPE_DIRECTORY;
}

bool isSymbolicLink(const std::string& path) {
    LOG_FUNCTION
    PHYSFS_Stat statbuf;
    PHYSFS_stat(path.c_str(), &statbuf);
    return statbuf.filetype == PHYSFS_FILETYPE_SYMLINK;
}

int64 getLastModTime(const std::string& file) {
    LOG_FUNCTION
    PHYSFS_Stat statbuf;
    PHYSFS_stat(file.c_str(), &statbuf);
    return statbuf.modtime;
}

void mkdir(const std::string& dir) {
    LOG_FUNCTION
    if (!PHYSFS_mkdir(dir.c_str()))
        throw Exception(PHYSFS_getLastError());
}

void remove(const std::string& path) {
    LOG_FUNCTION
    if (!PHYSFS_delete(path.c_str()))
        throw Exception(PHYSFS_getLastError());
}

std::string getRealDir(const std::string& file) {
    LOG_FUNCTION
    std::string dir = PHYSFS_getRealDir(file.c_str());
    if (dir.empty())
        throw Exception("Package::getRealDir: File not found");
    return dir;
}

StringVector enumerateFiles(const std::string& dir) {
    LOG_FUNCTION
    StringVector list;
    char** lst = PHYSFS_enumerateFiles(dir.c_str());
    for (char** l = lst; *l != 0; ++l) {
        list.push_back(*l);
    }
    PHYSFS_freeList(lst);
    return list;
}

StringVector getFileListing(const std::string& dir) {
    LOG_FUNCTION
    StringVector tmpList = enumerateFiles(dir);
    // now filter the list to only keep files
    StringVector list;
    for (StringVector::iterator it = tmpList.begin(); it != tmpList.end();
            ++it) {
        if (!isDirectory(*it))
            list.push_back(*it);
    }
    return list;
}

StringVector getDirListing(const std::string& dir) {
    LOG_FUNCTION
    StringVector tmpList = enumerateFiles(dir);
    // now filter the list to only keep dirs
    StringVector list;
    for (StringVector::iterator it = tmpList.begin(); it != tmpList.end();
            ++it) {
        if (isDirectory(*it))
            list.push_back(*it);
    }
    return list;
}

FileDevice::FileDevice(const std::string& path, OpenMode om) {
    LOG_FUNCTION
    switch (om) {
    case OM_READ:
        file = PHYSFS_openRead(path.c_str());
        break;
    case OM_WRITE:
        file = PHYSFS_openWrite(path.c_str());
        break;
    case OM_APPEND:
        file = PHYSFS_openAppend(path.c_str());
        break;
    }

    if (file == 0)
        throw Exception(PHYSFS_getLastError());
}

void FileDevice::close() {
    LOG_FUNCTION
    PHYSFS_close(file);
}

std::streamsize FileDevice::read(char* s, std::streamsize n) {
    LOG_FUNCTION
    PHYSFS_sint64 ret = PHYSFS_read(file, s, 1, PHYSFS_uint32(n));
    if (ret == -1)
        throw Exception(PHYSFS_getLastError());
    return std::streamsize(ret);
}

std::streamsize FileDevice::write(const char* s, std::streamsize n) {
    LOG_FUNCTION
    PHYSFS_sint64 ret = PHYSFS_write(file, s, sizeof(char), (PHYSFS_uint32) n);
    if (ret == -1)
        throw Exception(PHYSFS_getLastError());
    return std::streamsize(ret);
}

std::streampos FileDevice::seek(
    std::streamoff off,
    std::ios_base::seekdir way) {
    LOG_FUNCTION
    PHYSFS_sint64 pos(off);
    if (way == std::ios_base::cur) {
        PHYSFS_sint64 cur = PHYSFS_tell(file);
        if (cur == -1)
            throw Exception(PHYSFS_getLastError());
        pos = cur + off;
    } else if (way == std::ios_base::end) {
        PHYSFS_sint64 end = PHYSFS_fileLength(file);
        if (end == -1)
            throw Exception(PHYSFS_getLastError());
        pos = end + off;
    }

    if (!PHYSFS_seek(file, (PHYSFS_uint64) pos))
        throw Exception(PHYSFS_getLastError());

    return std::streampos(pos);
}

bool FileDevice::flush() {
    LOG_FUNCTION
    if (!PHYSFS_flush(file))
        throw Exception(PHYSFS_getLastError());
    return true;
}
}
