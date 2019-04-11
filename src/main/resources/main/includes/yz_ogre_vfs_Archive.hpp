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

#include <OgreArchive.h>
#include <OgreString.h>
#include <yz_physfs_File.hpp>

namespace yz {

namespace ogre {

namespace vfs {

/**
* Ogre Archive implementation for a VFS.
*@author Grégory Van den Borre
*/
class Archive: public Ogre::Archive {

public:

    Archive(yz::physfs::Wrapper* vfs, const Ogre::String& name, const Ogre::String& type) : Ogre::Archive(name, type), vfs(vfs) {
        LOG_FUNCTION
    }

    /** PhysFS is case sensitive in general */
    bool isCaseSensitive() const {
        LOG_FUNCTION
        return true;
    }

    /**
     * Loading is handled by the VFS.
     */
    void load() {
        LOG_FUNCTION
    }

    /**
     * Unloading is handled by the VFS.
     */
    void unload() {
        LOG_FUNCTION
    }

    inline time_t getModifiedTime(const Ogre::String& file) const {
        LOG_FUNCTION
        return this->vfs->getLastModTime(file);
    }

    Ogre::DataStreamPtr open(const Ogre::String& filename, bool append) const;

    Ogre::StringVectorPtr list(bool recursive = true, bool dirs = false) const;

    Ogre::FileInfoListPtr listFileInfo(bool recursive = true, bool dirs = false) const;

    Ogre::StringVectorPtr find(const Ogre::String& pattern, bool recursive = true, bool dirs = false) const;

    bool exists(const Ogre::String& filename) const;

    Ogre::FileInfoListPtr findFileInfo(const Ogre::String& pattern, bool recursive = true, bool dirs = false) const;

private:

    void listInfoRecursive(const Ogre::String& base, bool recursive, bool dirs, Ogre::FileInfoListPtr fileInfoList) const;

    void listRecursive(const Ogre::String& base, bool recursive, bool dirs, Ogre::StringVectorPtr fileList) const;

    yz::physfs::Wrapper* vfs;
};
}}}
