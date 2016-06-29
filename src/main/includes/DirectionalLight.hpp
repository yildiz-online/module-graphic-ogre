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

#ifndef _YZ_DIRECTIONAL_LIGHT_H_
#define _YZ_DIRECTIONAL_LIGHT_H_

#include "AbstractLight.hpp"

namespace YZ {

/**
*@author Grégory Van den Borre
*/
class DirectionalLight: public AbstractLight {

public:
    DirectionalLight(Ogre::Light* light, Ogre::SceneManager* manager) :
            AbstractLight(light, manager) {
    LOG_FUNCTION
}

inline void setDirection(
    const Ogre::Real dirX,
    const Ogre::Real dirY,
    const Ogre::Real dirZ) {
    LOG_FUNCTION
    this->light->setDirection(dirX, dirY, dirZ);
}

/**
 * Convert a pointer in a native Directionallight
 */
static inline YZ::DirectionalLight* get(const POINTER pointer) {
    return reinterpret_cast<YZ::DirectionalLight*>(pointer);
}
};
}

#endif

