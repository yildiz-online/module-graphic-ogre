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

#include "../includes/DynamicLine.hpp"

using namespace Ogre;
enum { POSITION_BINDING, TEXCOORD_BINDING };


DynamicLines::DynamicLines(yz::Node* node, Ogre::RenderOperation::OperationType opType) : node(node){
    LOG_FUNCTION
    initialize(opType,false);
    mDirty = true;
    this->node->addManualMovable(this);
    this->addPoint(0, 0, 0);
    this->addPoint(0, 0, 0);
    this->update();
}

DynamicLines::~DynamicLines() {LOG_FUNCTION}

void DynamicLines::setOperationType(Ogre::RenderOperation::OperationType opType) {
    LOG_FUNCTION
    mRenderOp.operationType = opType;
}

RenderOperation::OperationType DynamicLines::getOperationType() const {
    LOG_FUNCTION
    return mRenderOp.operationType;
}

void DynamicLines::addPoint(const Ogre::Vector3 &p) {
    LOG_FUNCTION
    mPoints.push_back(p);
    mDirty = true;
}

void DynamicLines::addPoint(Ogre::Real x, Ogre::Real y, Ogre::Real z) {
    LOG_FUNCTION
    mPoints.push_back(Vector3(x,y,z));
    mDirty = true;
}

const Vector3& DynamicLines::getPoint(unsigned short index) const {
    LOG_FUNCTION
    assert(index < mPoints.size() && "Point index is out of bounds!!");
    return mPoints[index];
}

unsigned short DynamicLines::getNumPoints() const {
    LOG_FUNCTION
    return static_cast<unsigned short>(mPoints.size());
}

void DynamicLines::setPoint(unsigned short index, const Ogre::Vector3 &value) {
    LOG_FUNCTION
    assert(index < mPoints.size() && "Point index is out of bounds!!");
    mPoints[index] = value;
    mDirty = true;
}

void DynamicLines::setPoint(unsigned short index, Ogre::Real x, Ogre::Real y, Ogre::Real z) {
    LOG_FUNCTION
    assert(index < mPoints.size() && "Point index is out of bounds!!");
    mPoints[index].x = x;
    mPoints[index].y = y;
    mPoints[index].z = z;

    mDirty = true;
}

void DynamicLines::clear() {
    LOG_FUNCTION
    mPoints.clear();
    mDirty = true;
}

void DynamicLines::update() {
    LOG_FUNCTION
    if (mDirty) {
        fillHardwareBuffers();
        this->node->needUpdate();
    }
}

void DynamicLines::createVertexDeclaration() {
    LOG_FUNCTION
    VertexDeclaration *decl = mRenderOp.vertexData->vertexDeclaration;
    decl->addElement(POSITION_BINDING, 0, VET_FLOAT3, VES_POSITION);
}

void DynamicLines::fillHardwareBuffers() {
    LOG_FUNCTION
    int size = mPoints.size();
    prepareHardwareBuffers(size,0);
    if (!size) {
        mBox.setExtents(Ogre::Vector3::ZERO, Ogre::Vector3::ZERO);
        mDirty=false;
        return;
    }
    Ogre::Vector3 vaabMin = mPoints[0];
    Ogre::Vector3 vaabMax = mPoints[0];
    HardwareVertexBufferSharedPtr vbuf = mRenderOp.vertexData->vertexBufferBinding->getBuffer(0);
    Real *prPos = static_cast<Real*>(vbuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));

        for(int i = 0; i < size; i++) {
            *prPos++ = mPoints[i].x;
            *prPos++ = mPoints[i].y;
            *prPos++ = mPoints[i].z;
            if(mPoints[i].x < vaabMin.x) {
                vaabMin.x = mPoints[i].x;
            }
            if(mPoints[i].y < vaabMin.y) {
                vaabMin.y = mPoints[i].y;
            }
            if(mPoints[i].z < vaabMin.z) {
                vaabMin.z = mPoints[i].z;
            }
            if(mPoints[i].x > vaabMax.x) {
                vaabMax.x = mPoints[i].x;
            }
            if(mPoints[i].y > vaabMax.y) {
                vaabMax.y = mPoints[i].y;
            }
            if(mPoints[i].z > vaabMax.z) {
                vaabMax.z = mPoints[i].z;
            }
        }

    vbuf->unlock();
    mBox.setExtents(vaabMin, vaabMax);
    mDirty = false;
}
