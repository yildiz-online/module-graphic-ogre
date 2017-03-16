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

/**
*@author Grégory Van den Borre
*/

#include "../includes/BillboardChain.hpp"

std::list<yz::BillboardChain*>yz::BillboardChain::instanceList;

yz::BillboardChain::BillboardChain(const std::string& name) : AbstractMovable() {
    LOG_FUNCTION
    this->chain = new Ogre::BillboardChain(name);
    this->chain->setUseVertexColours(true);
    instanceList.push_back(this);
}

yz::BillboardChain::~BillboardChain() {
    LOG_FUNCTION
    std::list<yz::BillboardChain*>::iterator p = find(instanceList.begin(), instanceList.end(), this);
    if(p != instanceList.end()){
        instanceList.erase(p);
    }
    this->detachFromParent();
    this->chain->clearChain(0);
    delete this->chain;
}


void yz::BillboardChain::setMaterial(yz::Material* material) {
    LOG_FUNCTION
    this->chain->setMaterialName(material->getName());
}

void yz::BillboardChain::addElement(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z, const Ogre::Real width) {
    LOG_FUNCTION
    this->chain->addChainElement(0,
            Ogre::BillboardChain::Element(Ogre::Vector3(x, y, z), width, 0,
                    Ogre::ColourValue::White, Ogre::Quaternion::IDENTITY));
}

void yz::BillboardChain::addElement(Ogre::Vector3& pos, const Ogre::Real width) {
    LOG_FUNCTION
    this->chain->addChainElement(0,
            Ogre::BillboardChain::Element(pos, width, 0,
                    Ogre::ColourValue::White, Ogre::Quaternion::IDENTITY));
}

void yz::BillboardChain::setElementPosition(const int index, const Ogre::Real x, const Ogre::Real y, const Ogre::Real z) {
    LOG_FUNCTION
    Ogre::BillboardChain::Element e = chain->getChainElement(0, index);
    e.position.x = x;
    e.position.y = y;
    e.position.z = z;
    this->chain->updateChainElement(0, index, e);
}

Ogre::BillboardChain::Element yz::BillboardChain::getChainElement(const int index) {
    LOG_FUNCTION
    return this->chain->getChainElement(0,index);
}

void yz::BillboardChain::updateChainElement(const int index, Ogre::BillboardChain::Element& element) {
    LOG_FUNCTION
    this->chain->updateChainElement(0, index, element);
}
