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

#ifndef _NATIVE_MOVABLE_COMPONENT_H_
#define _NATIVE_MOVABLE_COMPONENT_H_

namespace yz {

/**
 * Interface for movable component shared between engines.
 * @author Van den Borre Grégory.
 */
class NativeMovableComponent {

public:

    NativeMovableComponent() {}

    /**
     * Change the object position.
     * @param x New X position value.
     * @param y New Y position value.
     * @param z New Z position value.
     */
    virtual void setPosition(const float x, const float y, const float z) = 0;

    virtual void setDirection(const float x, const float y, const float z) = 0;

    virtual void setOrientation(const float x, const float y, const float z, const float w) = 0;

    virtual void addMovableComponent(NativeMovableComponent* c) = 0;

    virtual void removeMovableComponent(NativeMovableComponent* c) = 0;

};

}
#endif
