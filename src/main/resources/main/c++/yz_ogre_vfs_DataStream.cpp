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

#include "../includes/yz_ogre_vfs_DataStream.hpp"

yz::ogre::vfs::DataStream::DataStream(const yz::physfs::File* file) {
    LOG_FUNCTION
    vfsFile = file;
    mSize = (size_t) this->vfsFile->getSize();
}

yz::ogre::vfs::DataStream::DataStream(const Ogre::String& name, const yz::physfs::File* file) : Ogre::DataStream(name) {
    LOG_FUNCTION
    vfsFile = file;
    mSize = (size_t) this->vfsFile->getSize();
}

yz::ogre::vfs::DataStream::~DataStream() {
    LOG_FUNCTION
    close();
}

size_t yz::ogre::vfs::DataStream::read(void* buf, size_t count) {
    LOG_FUNCTION
    return this->vfsFile->readBytes(buf, count);
}

void yz::ogre::vfs::DataStream::seek(size_t pos) {
    LOG_FUNCTION
    this->vfsFile->seek(pos);
}

size_t yz::ogre::vfs::DataStream::tell() const {
    LOG_FUNCTION
    return (size_t) this->vfsFile->tell(file);
}

void yz::ogre::vfs::DataStream::skip(long count) {
    LOG_FUNCTION
    size_t pos = this->tell() + count;
    this->seek(pos);
}

bool yz::ogre::vfs::DataStream::eof() const {
    LOG_FUNCTION
    return this->vfsFile->isEof();
}

void yz::ogre::vfs::DataStream::close() {
    LOG_FUNCTION
    this->vfsFile->close();
}
