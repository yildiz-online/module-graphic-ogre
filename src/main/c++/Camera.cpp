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

#include "../includes/Camera.hpp"

yz::Id* yz::Camera::ID_WORLD(new yz::Id(0));

yz::Camera::Camera(
  Ogre::Camera* cam,
  Ogre::RaySceneQuery* q,
  Ogre::PlaneBoundedVolumeListSceneQuery* pq,
  Ogre::SceneNode* n) : camera(cam), query(q), planeQuery(pq), node(n) {
    LOG_FUNCTION
    n->attachObject(cam);
}

Ogre::Ray yz::Camera::getRay(const Ogre::Real x, const Ogre::Real y) {
    LOG_FUNCTION
    return this->camera->getCameraToViewportRay(x, y);
}

Ogre::Vector3 yz::Camera::rotate(const Ogre::Real x, const Ogre::Real y) {
    LOG_FUNCTION
    //FIXME limits related to game? check
    this->node->yaw(Ogre::Radian(x));
    const Ogre::Real pitch = this->node->getOrientation().getPitch().valueDegrees();
    if((pitch < 50 && y < 0) || (pitch > -50 && y > 0)) {
        this->node->pitch(Ogre::Radian(y));
    }
    this->updateListeners();
    return this->getDirection();
}

std::vector<yz::Id*> yz::Camera::throwPlaneRay(
    Ogre::Real x1,
    Ogre::Real x2,
    Ogre::Real y1,
    Ogre::Real y2) {
    LOG_FUNCTION
    this->planeQuery->clearResults();
    std::vector<yz::Id*> result;

    Ogre::Ray topLeft = this->getRay(x1, y1);
    Ogre::Ray topRight = this->getRay(x2, y1);
    Ogre::Ray bottomLeft = this->getRay(x1, y2);
    Ogre::Ray bottomRight = this->getRay(x2, y2);

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

Ogre::Vector3 yz::Camera::throwRayPos(const Ogre::Real x, const Ogre::Real y) {
    LOG_FUNCTION
    const Ogre::Ray ray = this->getRay(x, y);
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

yz::Id* yz::Camera::throwRay(
    const Ogre::Real x,
    const Ogre::Real y,
    const bool poly) {
    LOG_FUNCTION
    const Ogre::Ray ray = this->getRay(x, y);
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

void yz::Camera::updateListeners() {
    LOG_FUNCTION
    for(unsigned int i = 0; i < listenerList.size(); i++) {
        listenerList[i]->cameraUpdated(this->camera);
    }
}

Ogre::Vector3 yz::Camera::setPositionAxis(const Ogre::Real x, const Ogre::Real y, const int axis) {
    LOG_FUNCTION
    Ogre::Vector3 pos = this->node->getPosition();

    Ogre::Real resultX = 0;
    Ogre::Real resultY = 0;
    Ogre::Real resultZ = 0;
    switch (axis) {
    case 0:
        resultX = x;
        resultY = y;
        resultZ = pos.z;
        break;
    case 1:
        //in this axis the y value is the second, so mapped to Z
        resultX = x;
        resultY = pos.y;
        resultZ = y;
        break;
    case 2:
        resultX = pos.x;
        resultY = y;
        resultZ = x;
        break;
    default:
        //EXCEPTION
        break;
    }
    this->node->setPosition(resultX, resultY, resultZ);
    this->updateListeners();
    return this->node->getPosition();
}

Ogre::Vector3 yz::Camera::getPoint(
    const Ogre::Vector3& pos,
    const Ogre::Real x,
    const Ogre::Real y) {
    LOG_FUNCTION
    Ogre::Vector3 camPos = this->node->getPosition();
    Ogre::Real distance = pos.distance(camPos);
    Ogre::Ray ray = this->getRay(x, y);
    Ogre::Vector3 result = ray.getPoint(distance);
    return result;
}

