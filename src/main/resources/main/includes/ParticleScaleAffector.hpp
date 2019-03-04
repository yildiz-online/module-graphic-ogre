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

#ifndef PARTICLE_SCALE_AFFECTOR_H
#define PARTICLE_SCALE_AFFECTOR_H

#include "stdafx.h"
#include <Ogre.h>

namespace yz {
	
	/**
	*@author Grégory Van den Borre
	*/
class ParticleScaleAffector {
public:
	ParticleScaleAffector(Ogre::ParticleAffector* affector);

	inline void setScale(const Ogre::Real width, const Ogre::Real height) {
	    LOG_FUNCTION
		this->affector->setParameter("rate",
				Ogre::StringConverter::toString(width) + " "
						+ Ogre::StringConverter::toString(height));
	}

    static inline yz::ParticleScaleAffector* get(const POINTER pointer) {
        LOG_FUNCTION
        return reinterpret_cast<yz::ParticleScaleAffector*>(pointer);
    }

private:
	Ogre::ParticleAffector* affector;
};
}
#endif
