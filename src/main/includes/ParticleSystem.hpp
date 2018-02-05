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

#ifndef YZ_PARTICLE_SYSTEM_H
#define YZ_PARTICLE_SYSTEM_H

#define PARTICLESYSTEM yz::ParticleSystem

#include "stdafx.h"
#include "Node.hpp"
#include "ParticleEmitter.hpp"
#include "ParticleColorAffector.hpp"
#include "ParticleForceAffector.hpp"
#include "ParticleScaleAffector.hpp"
#include "AbstractMovable.hpp"
#include "Material.hpp"

namespace yz {

/**
 * Wrap an Ogre::ParticleSystem the attached yz::Node.
 * @author Grégory Van den Borre
 */
class ParticleSystem: public AbstractMovable {

public:
	ParticleSystem(Ogre::ParticleSystem* wrappedSystem) : system(wrappedSystem) {
	    LOG_FUNCTION
	}

	inline void keepInLocalSpace(bool keep) {
	    LOG_FUNCTION
		this->system->setKeepParticlesInLocalSpace(keep);
	}

	inline void setParticleOrientation(const Ogre::BillboardType& billboardType) {
	    LOG_FUNCTION
		Ogre::BillboardParticleRenderer* billboardRender =
				static_cast<Ogre::BillboardParticleRenderer*>(this->system->getRenderer());
			billboardRender->setBillboardType(billboardType);
	}

	inline void setParticleBillboardOrigin(
			const Ogre::BillboardOrigin& origin) {
	    LOG_FUNCTION
		Ogre::BillboardParticleRenderer* billboardRender =
				static_cast<Ogre::BillboardParticleRenderer*>(this->system->getRenderer());
		billboardRender->setBillboardOrigin(origin);
	}

	inline yz::ParticleEmitter* createEmitter() {
	    LOG_FUNCTION
		return new yz::ParticleEmitter(this->system->addEmitter("Point"));
	}

	inline yz::ParticleColorAffector* createColorAffector() {
	    LOG_FUNCTION
		return new yz::ParticleColorAffector(
				this->system->addAffector("ColourFader"));
	}

	inline yz::ParticleScaleAffector* createScaleAffector() {
	    LOG_FUNCTION
		return new yz::ParticleScaleAffector(
				this->system->addAffector("Scaler"));
	}

	inline yz::ParticleForceAffector* createForceAffector() {
	    LOG_FUNCTION
		return new yz::ParticleForceAffector(
				this->system->addAffector("LinearForce"));
	}

	inline void show() {
	    LOG_FUNCTION
		this->system->setVisible(true);
	}

	inline void hide() {
	    LOG_FUNCTION
		this->system->setVisible(false);
	}

	inline void setParticleQuota(const int quota) {
	    LOG_FUNCTION
		this->system->setParticleQuota(quota);
	}

	inline void setMaterial(yz::Material* material) {
	    LOG_FUNCTION
		this->system->setMaterialName(material->getName());
	}

	inline void setDefaultDimensions(const Ogre::Real width,
			const Ogre::Real height) {
	    LOG_FUNCTION
		this->system->setDefaultDimensions(width, height);
	}

	inline const Ogre::Real getVelocity() const {
	    LOG_FUNCTION
		return this->system->getEmitter(0)->getParticleVelocity();
	}

	inline void setTimeToLive(const Ogre::Real time) {
	    LOG_FUNCTION
		this->system->getEmitter(0)->setTimeToLive(time);
	}

	Ogre::MovableObject* getMovableObject() {
	    LOG_FUNCTION
		return this->system;
	}

    static inline yz::ParticleSystem* get(const POINTER pointer) {
        LOG_FUNCTION
        return reinterpret_cast<yz::ParticleSystem*>(pointer);
    }

private:
	Ogre::ParticleSystem* system;
};
}

#endif
