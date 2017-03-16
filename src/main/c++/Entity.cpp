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

/**
*@author Grégory Van den Borre
*/

#include "../includes/Entity.hpp"

YZ::Entity::Entity(Ogre::Entity* e) : entity(e) {
    LOG_FUNCTION
}

void YZ::Entity::setCustomParameters(const int index, const Ogre::Real p1,
			const Ogre::Real p2, const Ogre::Real p3, const Ogre::Real p4) {
    LOG_FUNCTION
	this->entity->getSubEntity(0)->setCustomParameter(index, Ogre::Vector4(p1, p2, p3, p4));
}

void YZ::Entity::setRenderQueueGroup(const int group) {
    LOG_FUNCTION
    this->entity->setRenderQueueGroup(group);
}

void YZ::Entity::setQueryFlags(const int mask) {
    LOG_FUNCTION
    this->entity->setQueryFlags(mask);
}

void YZ::Entity::setCastShadows(const bool cast) {
    LOG_FUNCTION
    this->entity->setCastShadows(cast);
}

Ogre::SceneNode* YZ::Entity::getParentSceneNode() const {
    LOG_FUNCTION
    return this->entity->getParentSceneNode();
}

void YZ::Entity::setMaterial(YZ::Material* material) {
    LOG_FUNCTION
    this->entity->setMaterialName(material->getName());
}

void YZ::Entity::setRenderingDistance(const int distance) {
    LOG_FUNCTION
    this->entity->setRenderingDistance(distance);
}
