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

#ifndef PHYSFS_OGRE_H
#define PHYSFS_OGRE_H

/**
*@author Grégory Van den Borre
*/
namespace PhysFS
{
  /**
   * Register the PhysFS system to Ogre's archive manager.
   * This allows you to use the PhysFS system for your resources, just
   * pass "PhysFS" as the location type when adding PhysFS locations
   * to Ogre's resource group manager.
   *
   * Note that this function instantiates a singleton inheriting from
   * Ogre::ArchiveFactory. The singleton will live until the application
   * is shut down. By then, you should have destroyed the Ogre system.
   * Also note that, naturally, you must have PhysFS initialised in order
   * to successfully access any resources with it.
   * I suggest that you initialise PhysFS before Ogre and shut it down after
   * Ogre. This way, you should be fine. Call this function only after
   * Ogre has been initialised!
   */
  void registerPhysFSToOgre();
}

#endif
