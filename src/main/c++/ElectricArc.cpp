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

#include "../includes/ElectricArc.hpp"

YZ::ElectricArc::ElectricArc(
    YZ::Node* startNode,
    YZ::Node* endNode,
    YZ::Node* baseNode,
    const std::string& name,
    const Ogre::Real width) {
    LOG_FUNCTION
    this->start = startNode;
    this->end = endNode;
    this->startPosition = this->start->getPosition();
    this->endPosition = this->end->getPosition();

    const Ogre::Vector3 distance = this->endPosition - this->startPosition;

    this->chain = new YZ::BillboardChain(name);

    this->base = baseNode;
    this->base->attachObject(this->chain);

    Ogre::Vector3 elementPosition = this->startPosition;
    Ogre::Real elementWidth = width;
    Ogre::Real texcoord = 0;
    Ogre::Vector3 step = distance / (MAX_STEP - 1);
    for (int i = 0; i < MAX_STEP; ++i) {
        this->chain->addElement(elementPosition, elementWidth);
        elementPosition += step;
        elementWidth += width * 0.16f;
    }
    Ogre::Root::getSingleton().addFrameListener(this);
    this->ceil = 10;
    this->light == NULL;
    this->hasLight = false;
}

void YZ::ElectricArc::addLight(YZ::PointLight* light) {
    LOG_FUNCTION
    if (!this->hasLight) {
        this->light = light;
        this->hasLight = true;
    }
}

YZ::ElectricArc::~ElectricArc(void) {
    LOG_FUNCTION
}

bool YZ::ElectricArc::frameStarted(const Ogre::FrameEvent& evt) {
    LOG_FUNCTION
    bool rd = rand() % 2 == 0;
    if(this->hasLight) {
        this->light->setActive(rd);
    }
    this->startPosition = this->start->getPosition();
    this->endPosition = this->end->getPosition();

    const Ogre::Vector3 distance = this->endPosition - this->startPosition;

    // update position and jitter
    Ogre::Vector3 elementPosition = this->startPosition;
    Ogre::Vector3 step = distance / (MAX_STEP - 1);
    for (int i = 0; i < MAX_STEP; ++i) {
        Ogre::BillboardChain::Element element = this->chain->getChainElement(i);

        Ogre::Vector3 randomVector(0, 0, 0);
        if ((i != 0) && (i != MAX_STEP - 1)) {
        	Ogre::Real x = (static_cast<Ogre::Real>(rand()) / RAND_MAX) * this->ceil;
        	Ogre::Real y = (static_cast<Ogre::Real>(rand()) / RAND_MAX) * this->ceil;
        	Ogre::Real z = (static_cast<Ogre::Real>(rand()) / RAND_MAX) * this->ceil;
            if (rd) {
                x = -x;
                y = -y;
                z = -z;
            }
            randomVector = Ogre::Vector3(x, y, z);
        }
        element.position = step.normalisedCopy().crossProduct(randomVector)
                + elementPosition;
        this->chain->updateChainElement(i, element);
        elementPosition += step;
    }
    return true;
}
