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

#include <OgreArchiveManager.h>
#include <OgreArchiveFactory.h>
#include <OgreArchive.h>
#include <OgreString.h>
#include <yz_physfs_Wrapper.hpp>
#include "yz_ogre_vfs_Archive.hpp"

namespace yz {

namespace ogre {

namespace vfs {

class ArchiveFactory: public Ogre::ArchiveFactory {
public:

    ArchiveFactory(const yz::physfs::Wrapper* vfs): vfs(vfs) {
        LOG_FUNCTION
    }

    const Ogre::String& getType() const {
        LOG_FUNCTION
        static const Ogre::String type = "Package";
        return type;
    }

    Ogre::Archive* createInstance(const Ogre::String& name, bool readOnly) {
        LOG_FUNCTION
        return new yz::ogre::vfs::Archive(this->vfs, name, getType());
    }

    void destroyInstance(Ogre::Archive* instance) {
        LOG_FUNCTION
        delete instance;
    }

private:

    ArchiveFactory(const ArchiveFactory& o);

    ArchiveFactory& operator=(const ArchiveFactory& o);

    yz::physfs::Wrapper* vfs;
};

void registerPhysFSToOgre(const yz::physfs::Wrapper* vfs) {
    LOG_FUNCTION
    Ogre::ArchiveManager::getSingleton().addArchiveFactory(new ArchiveFactory(vfs));
}

}}}
