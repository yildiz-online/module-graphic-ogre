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

#ifndef YZ_MATERIAL_H
#define YZ_MATERIAL_H

#include "stdafx.h"
#include <Ogre.h>
#include <OgreMaterialManager.h>

namespace yz {

/**
*@author Grégory Van den Borre
*/
class Material {

public:

	/**
	 * Constructor.
	 * @param mat Wrapped Ogre::Material.
	 */
	Material(const std::string& name) {
	    LOG_FUNCTION
		this->material = Ogre::MaterialManager::getSingleton().create(name, "General").get();
	}

    Material(Ogre::Material* m) : material(m){
        LOG_FUNCTION
	}

	inline const std::string& getName() const {
	    LOG_FUNCTION
		return this->material->getName();
	}

	inline yz::Material* clone(const std::string& name) const {
	    LOG_FUNCTION
		return new yz::Material(this->material->clone(name).get());
	}

	inline void compile() {
	    LOG_FUNCTION
		this->material->compile();
	}

	inline void load() {
	    LOG_FUNCTION
		this->material->load();
	}

	inline void setReceiveShadows(bool receive) {
	    LOG_FUNCTION
		this->material->setReceiveShadows(receive);
	}

	inline Ogre::Technique* createTechnique() {
	    LOG_FUNCTION
		return this->material->createTechnique();
	}

	inline Ogre::Technique* getTechnique(const int index) const {
	    LOG_FUNCTION
		return this->material->getTechnique(index);
	}

	inline int getNumTechniques() const {
	    LOG_FUNCTION
		return this->material->getNumTechniques();
	}

private:

	/**
	 * Wrapped Ogre::Material.
	 */
	Ogre::Material* material;

};
}

#endif
