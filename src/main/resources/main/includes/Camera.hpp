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

#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include <Ogre.h>
#include "stdafx.h"
#include "AbstractCameraListener.hpp"
#include "HelperLogics.hpp"
#include "Node.hpp"
#include "AbstractMovable.hpp"


namespace yz {

/**
*@author Grégory Van den Borre
*/
class Camera : public AbstractMovable {

public:

    Camera(Ogre::Camera* cam, Ogre::RaySceneQuery* query, Ogre::PlaneBoundedVolumeListSceneQuery* planeQuery, Ogre::SceneNode* node);

    Ogre::Vector3 getPoint(const Ogre::Vector3& pos, const Ogre::Real x, const Ogre::Real y);

    Ogre::Ray getRay(const Ogre::Real x, const Ogre::Real y);

    inline void setAspectRatio(const Ogre::Real ratio) {
        LOG_FUNCTION
        this->camera->setAspectRatio(ratio);

    }

    inline void setNearClipDistance(const Ogre::Real dist) {
        LOG_FUNCTION
        this->camera->setNearClipDistance(dist);
    }

    inline void setFarClipDistance(const Ogre::Real dist) {
        LOG_FUNCTION
        this->camera->setFarClipDistance(dist);
    }

    inline void addListener(yz::AbstractCameraListener* l) {
        LOG_FUNCTION
        this->listenerList.push_back(l);
    }

    inline void enableRenderingDistance() {
        LOG_FUNCTION
        this->camera->setUseRenderingDistance(true);
    }

    /**
     * Remove a listener from the list and call its destructor.
     * @param l Listener to remove.
     */
    inline void removeListener(yz::AbstractCameraListener* l) {
        LOG_FUNCTION
        this->listenerList.erase(std::remove(this->listenerList.begin(), this->listenerList.end(), l));
        delete l;
    }

    std::string getName() const {
        LOG_FUNCTION
        return this->camera->getName();
    }

    Ogre::Vector3 rotate(const Ogre::Real x, const Ogre::Real y);

    inline Ogre::Vector3 move(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z) {
        LOG_FUNCTION
        this->node->translate(Ogre::Vector3(x, y, z), Ogre::Node::TS_LOCAL);
        this->updateListeners();
        return this->node->getPosition();
    }

    Ogre::Vector3 setPositionAxis(const Ogre::Real x, const Ogre::Real y, const int axis);

    inline bool isVisible(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z) {
        LOG_FUNCTION
        return this->camera->isVisible(Ogre::Vector3(x, y, z));
    }

    inline void setPosition(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z) {
        LOG_FUNCTION
        this->node->setPosition(x, y, z);
        this->updateListeners();
    }

    inline Ogre::Vector3 lookAt(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z) {
        LOG_FUNCTION
        this->node->lookAt(Ogre::Vector3(x, y, z), Ogre::Node::TS_WORLD);
        this->updateListeners();
        return this->node->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
    }

    inline void setDirection(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z) {
        LOG_FUNCTION
        this->node->setDirection(x, y, z);
        this->updateListeners();
    }

    inline void forceListenersUpdate() {
        LOG_FUNCTION
        this->updateListeners();
    }

    void updateListeners();

    inline Ogre::Vector3 getDirection() const {
        LOG_FUNCTION
        return this->node->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
    }

    inline Ogre::Vector3 getPosition() const {
        LOG_FUNCTION
        return this->node->getPosition();
    }

    inline Ogre::Camera* getCamera() const{
        LOG_FUNCTION
        return this->camera;
    }

    inline void track(yz::Node* node) {
        LOG_FUNCTION
        this->node->setAutoTracking(true, node->getWrappedNode());
    }

    inline void stopTrack() {
        LOG_FUNCTION
        this->node->setAutoTracking(false);
    }

    inline void detachFromParent() {
        LOG_FUNCTION
        this->camera->detachFromParent();
    }

    Ogre::MovableObject* getMovableObject() {
        LOG_FUNCTION
        return this->camera;
    }

    yz::Id* throwRay(const Ogre::Real x, const Ogre::Real y, const bool poly);

    Ogre::Vector3 throwRayPos(const Ogre::Real x, const Ogre::Real y);

    std::vector<yz::Id*> throwPlaneRay(Ogre::Real x1, Ogre::Real x2, Ogre::Real y1, Ogre::Real y2);

    inline static yz::Camera* get(const POINTER pointer) {
        LOG_FUNCTION
        return reinterpret_cast<yz::Camera*>(pointer);
    }

private:

    static yz::Id* ID_WORLD;

    std::vector<yz::AbstractCameraListener*> listenerList;

    Ogre::Camera* camera;

    Ogre::RaySceneQuery* query;

    Ogre::PlaneBoundedVolumeListSceneQuery* planeQuery;

    Ogre::SceneNode* node;
};

}

#endif
