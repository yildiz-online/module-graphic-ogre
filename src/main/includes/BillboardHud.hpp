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

#ifndef BILLBOARDHUD_H
#define BILLBOARDHUD_H

#include "stdafx.h"

namespace YZ {

/**
*@author Grégory Van den Borre
*/
class BillboardHud {
public:
    BillboardHud(YZ::BillboardSet* parent, const Ogre::Vector3& offset) {
        LOG_FUNCTION
        this->billboard = new YZ::Billboard(parent->createBillboard());
        this->parent = parent;
        this->offset = offset;
        this->visible = true;
    }

    /**
     * Remove the billboard from the parent set.
     */
    virtual ~BillboardHud(void) {
        LOG_FUNCTION
        this->visible = false;
        this->parent->removeBillboard(this->billboard);
        this->billboard == NULL;
    }

    inline void hide(void) {
        LOG_FUNCTION
        if(this->visible) {
            this->visible = false;
            this->parent->removeBillboard(this->billboard);
        }
    }

    inline void show(void) {
        LOG_FUNCTION
        if(!this->visible) {
            this->billboard = this->parent->createBillboard();
            this->visible = true;
        }
    }

    inline void setPosition(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z) {
        LOG_FUNCTION
        if(this->visible) {
            this->billboard->setPosition(x + offset.x, y + offset.y, z + offset.z);
        }
    }

private :
    YZ::Billboard* billboard;
    YZ::BillboardSet* parent;
    Ogre::Vector3 offset;
    bool visible;
};

}
#endif
