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

#ifndef YZ_MATERIAL_EFFECT_H
#define YZ_MATERIAL_EFFECT_H

#include "stdafx.h"

namespace yz {

/**
 * Abstract class for a material effect, a class extending this one is supposed to implement the execute method to cotain the effect logic to apply to the material.
 * @author Grégory Van den Borre
 */
class MaterialEffect: public Ogre::FrameListener {

public:

    /**
     * Full constructor.
     * @param time Total time to execute the effect.
     * @param material Effect will be applied on this material, as every object using this material will be affected, a copy may be preferable to use.
     */
    MaterialEffect(const float time, yz::Material* material) {
        LOG_FUNCTION
        this->maxTime = time;
        this->elapsedTime = 0.0f;
        this->material = material;
    }

    inline bool frameStarted(const Ogre::FrameEvent& evt) {
        LOG_FUNCTION
        this->elapsedTime += evt.timeSinceLastFrame;
        this->execute(this->material, this->elapsedTime);
        return this->elapsedTime < this->maxTime;
    }

    inline bool frameRenderingQueued(const Ogre::FrameEvent&) {
        LOG_FUNCTION
        return true;
    }

    inline bool frameEnded(const Ogre::FrameEvent&) {
        LOG_FUNCTION
        return true;
    }

protected:

    /**
     * Abstract method to execute the materialeffect
     */
    virtual void execute(yz::Material* material, const float elapsedTime) = 0;

private:
    float elapsedTime;
    float maxTime;

    /**
     * Material to apply the effect.
     */
    yz::Material* material;
};

class MaterialEffectFadeOut: public MaterialEffect {

public:
    MaterialEffectFadeOut(yz::Material* material, const float time) :
            MaterialEffect(time, material) {
        LOG_FUNCTION
        this->current = 1.0f;
    }

protected:

    void execute(yz::Material* material, const float timeElapsed) {
        LOG_FUNCTION
        //float current = this->elapsedTime / this->maxTime;
        this->current -= 0.001f;
        //this->material->setDiffuse(1,1,1, current);
    }

private:
    float current;
};
}


#endif
