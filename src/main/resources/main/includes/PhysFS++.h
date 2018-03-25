/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 * Copyright (c) 2018 Grégory Van den Borre
 *
 * More infos available: https://www.yildiz-games.be
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

#ifndef PHYSFS_PP_H
#define PHYSFS_PP_H

extern "C"
{
  #include <physfs.h>
}

#include <string>
#include <vector>
#include <stdexcept>

#include <boost/iostreams/stream.hpp>

/**
*@author Grégory Van den Borre
*/
namespace PhysFS
{
  typedef std::vector<std::string> StringVector;

  /** Exception for error cases */
  class Exception : public std::exception
  {
  public:
    Exception(const std::string& what) : s(what) { }
    const char* what() const throw() { return s.c_str(); }
    ~Exception() throw(){}

  private:
    std::string s;
  };


  /** Dir separator for this platform */
  const std::string DIR_SEP = PHYSFS_getDirSeparator();


  /**
   * Initialise the PhysFS system.
   * @param argv0     Pass in argv[0] from your program's main function here.
   * @param symLinks  Whether or not to allow PhysFS to follow symlinks.
   */
  void init(const char* argv0, bool symLinks = false);

  /** Deinitialise the PhysFS system. */
  void deinit();

  /** Returns whether PhysFS is initialised. */
  bool isInit();


  /** Retrieve a list of supported archive formats (file endings only, no description!) */
  StringVector supportedArchiveTypes();

  /** Retrieve a list of CD/DVD drive file paths */
  StringVector getCdRomDirs();


  /**
   * Add a new directory or archive to the PhysFS search path.
   * @param location  Location to add
   * @param append    Append to the end of the search list? Otherwise prepend.
   */
  void addToSearchPath(const std::string& location, bool append = true);

  /**
   * Add a new directory or archive to the PhysFS search path at the given path.
   * @param location    Location to add
   * @param mountPoint  Location where to add the new location
   * @param append      Append at the end of the search list? Otherwise prepend.
   */
  void mount(const std::string& location, const std::string& mountPoint, bool append = true);

  /**
   * Remove a directory or archive from the PhysFS search path.
   * @param location  Location to remove.
   */
  void removeFromSearchPath(const std::string& location);

  /** Retrieve the mount point of a location. */
  std::string getMountPoint(const std::string& location);

  /** Retrieve the current search path list. */
  StringVector getSearchPath();

  /** Get the current user's home directory. */
  const std::string& getUserDir();

  /** Get the applcation's base dir. */
  const std::string& getBaseDir();


  /** Get the current PhysFS write directory. */
  std::string getWriteDir();

  /** Set the PhysFS write directory. */
  void setWriteDir(const std::string& dir);


  /** Set a standard sane config (see PhysFS documentation) */
  void setSaneConfig(const std::string& organisation, const std::string& appName,
    const std::string& archiveExt = "", bool includeCdDrives = false, bool archivesFirst = false);


  /** Returns whether the given path exists in PhysFS. */
  bool exists(const std::string& path);

  /** Returns whether the given path is a directory in PhysFS. */
  bool isDirectory(const std::string& path);

  /** Returns whether the given path is a symbolic link in PhysFS. */
  bool isSymbolicLink(const std::string& path);

  typedef PHYSFS_sint64 int64;
  /** Get time of last modification. */
  int64 getLastModTime(const std::string& file);


  /** Create the given directory in the write location. */
  void mkdir(const std::string& dir);

  /** Delete a file or directory in the write location. */
  void remove(const std::string& path);

  /** Retrieve the actual location where the given file can be found. */
  std::string getRealDir(const std::string& file);

  /** Get a listing of files and directories inside the given directory. */
  StringVector enumerateFiles(const std::string& dir);

  /** Conveniece: Get a listing of files inside the given directory. */
  StringVector getFileListing(const std::string& dir);

  /** Convenience: Get a listing of subdirectories inside the given directory. */
  StringVector getDirListing(const std::string& dir);



  /** File open modes */
  enum OpenMode
  {
    OM_READ,
    OM_WRITE,
    OM_APPEND
  };

  /**
   * Helper class for implementing a PhysFS filestream.
   * This is not intended for direct use; instead, see
   * the FileStream typedef below.
   */
  class FileDevice
  {
  public:
    typedef char char_type;
    struct category : boost::iostreams::seekable, boost::iostreams::device_tag,
      boost::iostreams::closable_tag, boost::iostreams::flushable_tag {};

    FileDevice(const std::string& path, OpenMode om);
    void close();

    bool flush();

    std::streamsize read(char* s, std::streamsize n);
    std::streamsize write(const char* s, std::streamsize n);
    std::streampos seek(std::streamoff off, std::ios_base::seekdir way);

  private:
    PHYSFS_File* file;
  };

  /**
   * FileStream is a standard C++ stream.
   * At construction or when calling FileStream::open, use these parameters:
   * @param path  The file to open
   * @param om    The mode to open the file in (read/write/append)
   */
  typedef boost::iostreams::stream<FileDevice> FileStream;

}

#endif
