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

/**
*@author Grégory Van den Borre
*/

#ifndef STDAFX_H
#define STDAFX_H

#ifdef DEBUG
#define LOG_FUNCTION std::cout<<__PRETTY_FUNCTION__<<std::endl;
#else
#define LOG_FUNCTION
#endif

#include <jni.h>
#define POINTER jlong
#define INVALID_POINTER -1L

#include "Id.hpp"
#include <Ogre.h>
#include <Overlay/OgreTextAreaOverlayElement.h>
#include <Overlay/OgreOverlayElement.h>
#include <Overlay/OgreOverlayContainer.h>

#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlaySystem.h>

#include <Overlay/OgreFontManager.h>
#include <Overlay/OgreFont.h>

#include <OgreBillboardParticleRenderer.h>
#include <OgreArchive.h>
#include <OgreGpuProgramParams.h>
#include <OgreHighLevelGpuProgramManager.h>


//#include "Hydrax.h"

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <exception>
#include <iterator>
#include <cassert>
#include <cmath>
#include <cstdlib>

#endif
