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

#ifndef OGRE_NODE_LISTENERS_H
#define OGRE_NODE_LISTENERS_H

#include "stdafx.h"
#include "AbstractNodeListener.hpp"
#include <OgreNode.h>

namespace yz {

/**
*@author Grégory Van den Borre
*/
    class NodeListeners : public Ogre::Node::Listener {

    public:

        /**
        * Remove all elements from the listener list and call their destructor.
        */
        virtual ~NodeListeners(void) {
            LOG_FUNCTION
            this->listeners.clear();
        }

        virtual void nodeUpdated(const Ogre::Node* node) {
            LOG_FUNCTION
            for(unsigned int i=0; i < listeners.size(); i++) {
                listeners[i]->update(node);
            }
        }

        inline void addListener(yz::AbstractNodeListener* listener){
            LOG_FUNCTION
            this->listeners.push_back(listener);
        }

    private:
        std::vector<yz::AbstractNodeListener*> listeners;
    };

}

#endif
