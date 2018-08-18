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
#include "RayProvider.hpp"
#include "HelperLogics.hpp"
#include "Node.hpp"
#include "AbstractMovable.hpp"


namespace yz {

/**
*@author Grégory Van den Borre
*/
class Camera : public AbstractMovable, public RayProvider {

public:

    Camera(Ogre::Camera* cam);

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

    inline bool isVisible(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z) {
        LOG_FUNCTION
        return this->camera->isVisible(Ogre::Vector3(x, y, z));
    }

    inline void forceListenersUpdate() {
        LOG_FUNCTION
        this->updateListeners();
    }

    void updateListeners();

    inline Ogre::Camera* getCamera() const{
        LOG_FUNCTION
        return this->camera;
    }

    Ogre::Vector3 getPosition() const {
        LOG_FUNCTION
        return this->camera->getParentSceneNode()->getPosition();
    }

    inline void detachFromParent() {
        LOG_FUNCTION
        this->camera->detachFromParent();
    }

    Ogre::MovableObject* getMovableObject() {
        LOG_FUNCTION
        return this->camera;
    }

    inline static yz::Camera* get(const POINTER pointer) {
        LOG_FUNCTION
        return reinterpret_cast<yz::Camera*>(pointer);
    }

private:

    static yz::Id* ID_WORLD;

    std::vector<yz::AbstractCameraListener*> listenerList;

    Ogre::Camera* camera;

};

}

#endif
