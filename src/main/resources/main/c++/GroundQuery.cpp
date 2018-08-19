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

/**
*@author Grégory Van den Borre
*/

#include "../includes/GroundQuery.hpp"

yz::GroundQuery::GroundQuery(
  yz::RayProvider* p,
  Ogre::RaySceneQuery* q,
  yz::Node* d) : provider(p), query(q), dummyGround(d) {
    LOG_FUNCTION
}


Ogre::Vector3 yz::GroundQuery::throwRayPos(const Ogre::Real x, const Ogre::Real y) {
    LOG_FUNCTION
    if(this->dummyGround != NULL) {
        Ogre::Vector3 v = this->provider->getPosition();
        this->dummyGround->show();
        this->dummyGround->setPosition(v.x, -1, v.z);
    }
    const Ogre::Ray ray = this->provider->getRay(x, y);
    this->query->clearResults();
    this->query->setQueryMask(Ogre::SceneManager::WORLD_GEOMETRY_TYPE_MASK);
    this->query->setSortByDistance(true, 1);
    this->query->setRay(ray);
    Ogre::RaySceneQueryResult& results = query->execute();
    Ogre::RaySceneQueryResult::iterator itr = results.begin();
    for (; itr != results.end(); ++itr) {
        return ray.getPoint(itr->distance);
    }
    return Ogre::Vector3::ZERO;
}


