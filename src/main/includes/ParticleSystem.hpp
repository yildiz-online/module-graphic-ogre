//        This file is part of the Yildiz-Online project, licenced under the MIT License
//        (MIT)
//
//        Copyright (c) 2016 Grégory Van den Borre
//
//        More infos available: http://yildiz.bitbucket.org
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
//        of this software and associated documentation files (the "Software"), to deal
//        in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
//        furnished to do so, subject to the following conditions:
//
//        The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
//        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//        SOFTWARE.

#ifndef YZ_PARTICLE_SYSTEM_H
#define YZ_PARTICLE_SYSTEM_H

#define PARTICLESYSTEM YZ::ParticleSystem

#include "stdafx.h"
#include "Node.hpp"
#include "ParticleEmitter.hpp"
#include "ParticleColorAffector.hpp"
#include "ParticleForceAffector.hpp"
#include "ParticleScaleAffector.hpp"
#include "AbstractMovable.hpp"
#include "Material.hpp"

namespace YZ {

/**
 * Wrap an Ogre::ParticleSystem the attached YZ::Node.
 * @author Grégory Van den Borre
 */
class ParticleSystem: public AbstractMovable {

public:
	ParticleSystem(Ogre::ParticleSystem* wrappedSystem) {
	    LOG_FUNCTION
		this->system = wrappedSystem;
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

	inline YZ::ParticleEmitter* createEmitter() {
	    LOG_FUNCTION
		return new YZ::ParticleEmitter(this->system->addEmitter("Point"));
	}

	inline YZ::ParticleColorAffector* createColorAffector() {
	    LOG_FUNCTION
		return new YZ::ParticleColorAffector(
				this->system->addAffector("ColourFader"));
	}

	inline YZ::ParticleScaleAffector* createScaleAffector() {
	    LOG_FUNCTION
		return new YZ::ParticleScaleAffector(
				this->system->addAffector("Scaler"));
	}

	inline YZ::ParticleForceAffector* createForceAffector() {
	    LOG_FUNCTION
		return new YZ::ParticleForceAffector(
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

	inline void setMaterial(YZ::Material* material) {
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

    static inline YZ::ParticleSystem* get(const POINTER pointer) {
        LOG_FUNCTION
        return reinterpret_cast<YZ::ParticleSystem*>(pointer);
    }

private:
	Ogre::ParticleSystem* system;
};
}

#endif
