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

#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H

#define PARTICLEEMITTER yz::ParticleEmitter

#include "stdafx.h"

namespace yz {
	
	/**
	*@author Grégory Van den Borre
	*/
class ParticleEmitter {
public:
	ParticleEmitter(Ogre::ParticleEmitter* emitter);

	inline void setMinSpeed(const Ogre::Real speed) {
	    LOG_FUNCTION
		this->emitter->setMinParticleVelocity(speed);
		this->minSpeed = speed;
	}

	inline void setMaxSpeed(const Ogre::Real speed) {
	    LOG_FUNCTION
		this->emitter->setMaxParticleVelocity(speed);
		this->maxSpeed = speed;
	}

	inline void setStartColor(const Ogre::Real r, const Ogre::Real g,
			const Ogre::Real b, const Ogre::Real a) {
	    LOG_FUNCTION
		this->emitter->setColourRangeStart(Ogre::ColourValue(r, g, b, a));
	}

	inline void setEndColor(const Ogre::Real r, const Ogre::Real g,
			const Ogre::Real b, const Ogre::Real a) {
	    LOG_FUNCTION
		this->emitter->setColourRangeEnd(Ogre::ColourValue(r, g, b, a));
	}

	inline void setAngle(const Ogre::Real angle) {
	    LOG_FUNCTION
		this->emitter->setAngle(Ogre::Radian(Ogre::Degree(angle)));
	}

	inline void setRate(const Ogre::Real rate) {
	    LOG_FUNCTION
		this->emitter->setEmissionRate(rate);
	}

	inline void setLifeTime(const Ogre::Real lifeTime) {
	    LOG_FUNCTION
		this->emitter->setTimeToLive(lifeTime);
	}

	inline void setDuration(const Ogre::Real duration) {
	    LOG_FUNCTION
		this->emitter->setDuration(duration);
	}

	inline void setRepeatDelay(const Ogre::Real delay) {
	    LOG_FUNCTION
		this->emitter->setRepeatDelay(delay);
	}

	inline void setDirection(const Ogre::Real x, const Ogre::Real y,
			const Ogre::Real z) {
	    LOG_FUNCTION
		this->emitter->setDirection(Ogre::Vector3(x, y, z));
	}

	inline void pause() {
	    LOG_FUNCTION
		this->emitter->setParticleVelocity(0);
	}

	inline void restart() {
	    LOG_FUNCTION
		this->emitter->setParticleVelocity(this->minSpeed, this->maxSpeed);
	}

private:
	Ogre::ParticleEmitter* emitter;
	Ogre::Real minSpeed;
	Ogre::Real maxSpeed;
};
}
#endif
