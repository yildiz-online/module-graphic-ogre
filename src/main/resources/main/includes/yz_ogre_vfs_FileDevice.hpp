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

namespace yz {

namespace ogre {

namespace vfs {

class FileDevice {

public:
    typedef char char_type;

    struct category : boost::iostreams::seekable, boost::iostreams::device_tag, boost::iostreams::closable_tag, boost::iostreams::flushable_tag {};

    FileDevice(const std::string& path) {
        this->file = new yz::physfs::File(path);
    }

    FileDevice(const yz::physfs::File* file) {
        this->file = file;
    }

    void close() {
        this->file->close();
    }

    bool flush() {
        this->file->flush();
        return true;
    }

    std::streamsize read(char* s, std::streamsize n) {
        return std::streamsize(this->file->readBytes(n));
    }

    std::streamsize write(const char* s, std::streamsize n) {
        return std::streamsize(0);
    }

    std::streampos seek(std::streamoff off, std::ios_base::seekdir way);

  private:
      yz::physfs::File* file;
  };
  /**
   * FileStream is a standard C++ stream.
   * At construction or when calling FileStream::open, use these parameters:
   * @param path  The file to open
   * @param om    The mode to open the file in (read/write/append)
   */
  typedef boost::iostreams::stream<FileDevice> FileStream;

}}}