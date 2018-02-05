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

#ifndef DYNAMIC_LINES_H
#define DYNAMIC_LINES_H

#include <Ogre.h>
#include "DynamicRenderable.hpp"
#include "stdafx.h"
#include "Node.hpp"
#include "Material.hpp"

/**
*@author Grégory Van den Borre
*/
class DynamicLines : public DynamicRenderable {
    typedef Ogre::Quaternion Quaternion;
    typedef Ogre::Camera Camera;
public:
    DynamicLines(yz::Node* node, Ogre::RenderOperation::OperationType opType=Ogre::RenderOperation::OT_LINE_STRIP);

    virtual ~DynamicLines();

    void addPoint(const Ogre::Vector3 &point);

    void addPoint(Ogre::Real x, Ogre::Real y, Ogre::Real z);

    void setPoint(unsigned short index, const Ogre::Vector3 &value);

    void setPoint(unsigned short index, Ogre::Real x, Ogre::Real y, Ogre::Real z);

    const Ogre::Vector3& getPoint(unsigned short index) const;

    unsigned short getNumPoints() const;

    void clear();

    void update();

    void setOperationType(Ogre::RenderOperation::OperationType opType);

    Ogre::RenderOperation::OperationType getOperationType() const;

    inline void show() {
        LOG_FUNCTION
        this->node->show();
    }

    inline void hide() {
        LOG_FUNCTION
        this->node->hide();
    }

    void setMaterial(yz::Material* material) {
        LOG_FUNCTION
      //  this->setMaterialName(material->getName());
    }

    static inline DynamicLines* get(const POINTER pointer) {
        LOG_FUNCTION
        return reinterpret_cast<DynamicLines*>(pointer);
    }


protected:

    virtual void createVertexDeclaration();

    virtual void fillHardwareBuffers();

private:

    std::vector<Ogre::Vector3> mPoints;

    bool mDirty;

    yz::Node* node;

};

#endif
