/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 * Copyright (c) 2017 Grégory Van den Borre
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

#ifndef YZ_BILLBOARDSET_H
#define YZ_BILLBOARDSET_H

#include "Material.hpp"
#include "AbstractMovable.hpp"
#include "Billboard.hpp"
#include <OgreBillboardSet.h>
#include <OgreBillboard.h>

namespace YZ {

/**
*@author Grégory Van den Borre
*/
class BillboardSet : public AbstractMovable {

public:


    BillboardSet(Ogre::BillboardSet* set) : set(set){
        LOG_FUNCTION
        this->set->setCullIndividually(true);
        this->set->setQueryFlags(0);
    }

    ~BillboardSet() {
        delete this->set;
        this->set = NULL;
    }

    void setMaterial(const YZ::Material* material) {
        LOG_FUNCTION
        this->set->setMaterialName(material->getName());
    }

    YZ::Billboard* createBillboard() {
        LOG_FUNCTION
        return new YZ::Billboard(this->set->createBillboard(0, 0, 0, Ogre::ColourValue::White));
    }

    Ogre::Billboard* getBillboard(const int index) const {
        LOG_FUNCTION
        return this->set->getBillboard(index);
    }

    void removeBillboard(YZ::Billboard* b) {
        LOG_FUNCTION
        this->set->removeBillboard(b->getWrappedBillboard());
    }

    void show() {
        LOG_FUNCTION
        this->set->setVisible(true);
    }

    void hide() {
        LOG_FUNCTION
        this->set->setVisible(false);
    }

    void setSize(const Ogre::Real width, const Ogre::Real height) {
        LOG_FUNCTION
        this->set->setDefaultDimensions(width, height);
    }

    Ogre::MovableObject* getMovableObject() {
        LOG_FUNCTION
        return this->set;
    }

    inline static YZ::BillboardSet* get(const POINTER pointer) {
        LOG_FUNCTION
        return reinterpret_cast<YZ::BillboardSet*>(pointer);
    }


private :
    Ogre::BillboardSet* set;
};

}
#endif
