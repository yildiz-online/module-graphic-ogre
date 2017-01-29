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

#ifndef YZE_ABSTRACT_LIGHT_H
#define YZE_ABSTRACT_LIGHT_H

#include "stdafx.h"
#include <OgreLight.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

namespace YZ {

/**
 * Base class for lights.
 * @author Grégory Van den Borre
 */
class AbstractLight {
public:
    AbstractLight(Ogre::Light* ogreLight, Ogre::SceneManager* manager) :
            light(ogreLight), creator(manager) {}

    virtual ~AbstractLight(void) {
        LOG_FUNCTION
        if (this->light->isAttached()) {
            Ogre::SceneNode* node = this->light->getParentSceneNode();
            node->detachObject(this->light);
        }
        this->creator->destroyLight(this->light);
        this->light = NULL;
    }

    inline void setPosition(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z) {
        LOG_FUNCTION
        this->light->setPosition(x, y, z);
    }

    inline void setPosition(const Ogre::Vector3& v) {
        LOG_FUNCTION
        this->light->setPosition(v);
    }

    inline void setColor(const Ogre::ColourValue& v) {
        LOG_FUNCTION
        this->light->setDiffuseColour(v);
    }

    inline void setColor(const Ogre::Real r, const Ogre::Real g, const Ogre::Real b) {
        LOG_FUNCTION
        this->light->setDiffuseColour(r, g, b);
    }

    inline void setDebug(void) {
        LOG_FUNCTION
        this->light->setDebugDisplayEnabled(true);
    }

    /**
     * Set the light active or not.
     * @param active <code>true</code> to make the light active.
     */
    inline void setActive(const bool active) {
        LOG_FUNCTION
        this->light->setVisible(active);
    }

    inline Ogre::Light* getWrappedLight(void) const {
        LOG_FUNCTION
        return this->light;
    }

private:

    Ogre::SceneManager* creator;

protected:
    Ogre::Light* light;
};

}
#endif
