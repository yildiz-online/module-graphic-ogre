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

#ifndef YZ_BILLBOARD_H
#define YZ_BILLBOARD_H

#include "stdafx.h"
#include <OgreBillboard.h>

namespace yz {

/**
*@author Grégory Van den Borre
*/
class Billboard  {
public:

    Billboard(Ogre::Billboard* billboard) : billboard(billboard) {
        LOG_FUNCTION
    }

    inline void setDimensions(const Ogre::Real width, const Ogre::Real height) {
        LOG_FUNCTION
        this->billboard->setDimensions(width, height);
    }

    inline void setPosition(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z) {
        LOG_FUNCTION
        this->billboard->setPosition(x, y , z);
    }

    inline void setColor(const Ogre::Real r, const Ogre::Real g, const Ogre::Real b, const Ogre::Real a) {
        LOG_FUNCTION
        this->billboard->setColour(Ogre::ColourValue(r, g, b, a));
    }

    inline Ogre::Billboard* getWrappedBillboard() {
        LOG_FUNCTION
        return this->billboard;
    }

private :
    Ogre::Billboard* billboard;
};

}
#endif
