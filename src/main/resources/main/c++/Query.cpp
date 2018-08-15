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

#include "../includes/Query.hpp"

yz::Id* yz::Query::ID_WORLD(new yz::Id(0));

yz::Query::Query(
  yz::RayProvider* p,
  Ogre::RaySceneQuery* q,
  Ogre::PlaneBoundedVolumeListSceneQuery* pq) : provider(p), query(q), planeQuery(pq) {
    LOG_FUNCTION
}

std::vector<yz::Id*> yz::Query::throwPlaneRay(
    Ogre::Real x1,
    Ogre::Real x2,
    Ogre::Real y1,
    Ogre::Real y2) {
    LOG_FUNCTION
    this->planeQuery->clearResults();
    std::vector<yz::Id*> result;

    Ogre::Ray topLeft = this->provider->getRay(x1, y1);
    Ogre::Ray topRight = this->provider->getRay(x2, y1);
    Ogre::Ray bottomLeft = this->provider->getRay(x1, y2);
    Ogre::Ray bottomRight = this->provider->getRay(x2, y2);

    Ogre::PlaneBoundedVolume vol;

    Ogre::Vector3 ori = topLeft.getOrigin();
    Ogre::Vector3 tlp = topLeft.getPoint(100);
    Ogre::Vector3 btp = bottomLeft.getPoint(100);
    Ogre::Vector3 trp = topRight.getPoint(100);
    Ogre::Vector3 brp = bottomRight.getPoint(100);

    vol.planes.push_back(
            Ogre::Plane(topLeft.getPoint(3), topRight.getPoint(3),
                    bottomRight.getPoint(3)));         // front plane
    vol.planes.push_back(Ogre::Plane(ori, tlp, trp)); // top plane
    vol.planes.push_back(Ogre::Plane(ori, btp, tlp)); // left plane
    vol.planes.push_back(Ogre::Plane(ori, brp, btp)); // bottom plane
    vol.planes.push_back(Ogre::Plane(ori, trp, brp)); // right plane

    Ogre::PlaneBoundedVolumeList volList;
    volList.push_back(vol);

    this->planeQuery->setVolumes(volList);
    Ogre::SceneQueryResult queryResult = this->planeQuery->execute();

    Ogre::SceneQueryResultMovableList::iterator itr;

    for (itr = queryResult.movables.begin(); itr != queryResult.movables.end(); ++itr) {
        Ogre::SceneNode* node = (*itr)->getParentSceneNode();
        Ogre::Any any = node->getUserObjectBindings().getUserAny();
        if(any.has_value()) {
            result.push_back(Ogre::any_cast<yz::Id*>(any));
        }
    }
    return result;
}

Ogre::Vector3 yz::Query::throwRayPos(const Ogre::Real x, const Ogre::Real y) {
    LOG_FUNCTION
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

yz::Id* yz::Query::throwRay(
    const Ogre::Real x,
    const Ogre::Real y,
    const bool poly) {
    LOG_FUNCTION
    const Ogre::Ray ray = this->provider->getRay(x, y);
    this->query->clearResults();
    this->query->setQueryMask(Ogre::SceneManager::ENTITY_TYPE_MASK);
    this->query->setSortByDistance(true, 1);
    this->query->setRay(ray);
    Ogre::RaySceneQueryResult& results = query->execute();
    Ogre::RaySceneQueryResult::iterator itr = results.begin();
    //Ogre::Vector3 result;
    //Ogre::Real distance = 0.0;

    for (; itr != results.end(); ++itr) {
        if (itr->movable) {
            Ogre::SceneNode* node = itr->movable->getParentSceneNode();
            Ogre::Any any = node->getUserObjectBindings().getUserAny();
            if (any.has_value()) {
                if (!poly) {
                    return Ogre::any_cast<yz::Id*>(any);
                } else {/*else if (poly
                        && this->collisionTool->raycast(ray, result, node->getAttachedObject(0),
                                distance,
                                Ogre::SceneManager::ENTITY_TYPE_MASK)) {
                    return Ogre::any_cast<long>(node->getUserAny());*/
                    //FIXME, add collsiion tool
                    return 0;
                }
            }
        }
    }
    return yz::Camera::ID_WORLD;
}

