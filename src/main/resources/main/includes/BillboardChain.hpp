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

#ifndef BILLBOARDCHAIN_H
#define BILLBOARDCHAIN_H

#include "AbstractMovable.hpp"
#include <OgreBillboardChain.h>
#include "Material.hpp"

namespace yz {

/**
*@author Grégory Van den Borre
*/
class BillboardChain : public AbstractMovable {
public:
    BillboardChain(const std::string& name);

    ~BillboardChain(void);

    virtual Ogre::MovableObject* getMovableObject(void) {
        LOG_FUNCTION
        return this->chain;
    }

    void setMaterial(yz::Material* material);

    void addElement(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z, const Ogre::Real width);

    void addElement(Ogre::Vector3& pos, const Ogre::Real width);

    void setElementPosition(const int index, const Ogre::Real x, const Ogre::Real y, const Ogre::Real z);

    Ogre::BillboardChain::Element getChainElement(const int index);

    void updateChainElement(const int index, Ogre::BillboardChain::Element& element);

    static inline yz::BillboardChain* get(const POINTER pointer) {
        LOG_FUNCTION
        return reinterpret_cast<yz::BillboardChain*>(pointer);
    }


private :
    static std::list<BillboardChain*> instanceList;

    Ogre::BillboardChain* chain;
};

}
#endif