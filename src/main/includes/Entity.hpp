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

#ifndef ENTITY_H
#define ENTITY_H

//FIXME do no include everything
#include "stdafx.h"
#include "AbstractMovable.hpp"
#include "Material.hpp"

namespace yz {

/**
*@author Grégory Van den Borre
*/
class Entity : public AbstractMovable {

public:
    Entity(Ogre::Entity* e);

    //FIXME destructor

	void setQueryFlags(const int mask);

	void setCustomParameters(
        const int index,
        const Ogre::Real p1,
		const Ogre::Real p2,
        const Ogre::Real p3,
        const Ogre::Real p4);

	void setRenderQueueGroup(const int group);

	void setCastShadows(const bool cast);

    void setMaterial(yz::Material* material);

    //FIXME return YZ node
	Ogre::SceneNode* getParentSceneNode() const;

    void setRenderingDistance(const int distance);

    virtual Ogre::MovableObject* getMovableObject() {
        LOG_FUNCTION
        return this->entity;
    }

	inline static yz::Entity* get(const POINTER pointer) {
	    LOG_FUNCTION
	    return reinterpret_cast<yz::Entity*>(pointer);
	}

private:
	Ogre::Entity* entity;
};
}
#endif
