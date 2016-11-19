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

#ifndef YZ_POINT_LIGHT_H
#define YZ_POINT_LIGHT_H

#include "stdafx.h"
#include <Ogre.h>
#include "AbstractLight.hpp"

namespace YZ {

/**
* @author Grégory Van den Borre
*/
    class PointLight : public AbstractLight {

    public:
        PointLight(Ogre::Light* light, Ogre::SceneManager* manager) : AbstractLight(light, manager){LOG_FUNCTION }

        inline void setAttenuation(const Ogre::Real range, const Ogre::Real constant, const Ogre::Real linear, const Ogre::Real quadratic) {
            LOG_FUNCTION
            this->light->setAttenuation(range, constant, linear, quadratic);
        }

        static inline YZ::PointLight* get(const POINTER pointer) {
            LOG_FUNCTION
            return reinterpret_cast<YZ::PointLight*>(pointer);
        }

    };
}

#endif

