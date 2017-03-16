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

#ifndef BILLBOARDNODELISTENER_H
#define BILLBOARDNODELISTENER_H

#include "AbstractNodeListener.hpp"
#include "BillboardHud.hpp"

namespace yz {

/**
*@author Grégory Van den Borre
*/
class BillboardNodeListener: public AbstractNodeListener {
public:


    BillboardNodeListener(yz::BillboardHud* billboard) {
        LOG_FUNCTION
        this->billboardList.push_back(billboard);
    }

    virtual ~BillboardNodeListener() {
        LOG_FUNCTION
        this->billboardList.clear();
    }

    inline void add(yz::BillboardHud* hud) {
        LOG_FUNCTION
        this->billboardList.push_back(hud);
    }

    inline void update(const Ogre::Node* node) {
        LOG_FUNCTION
        Ogre::Vector3 pos = node->getPosition();
        for(int i = 0; i < this->billboardList.size(); ++i) {
            this->billboardList[i]->setPosition(pos.x, pos.y, pos.z);
        }
    }

private:
    std::vector <yz::BillboardHud*> billboardList;
};

}
#endif
