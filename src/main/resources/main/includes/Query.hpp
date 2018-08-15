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

#ifndef QUERY_H
#define QUERY_H

#include <vector>
#include <Ogre.h>
#include "stdafx.h"
#include "HelperLogics.hpp"
#include "Node.hpp"
#include "RayProvider.hpp"

namespace yz {

/**
*@author Grégory Van den Borre
*/
class Query {

public:

    Query(yz::RayProvider* provider, Ogre::RaySceneQuery* query, Ogre::PlaneBoundedVolumeListSceneQuery* planeQuery);

    Ogre::Vector3 getPoint(const Ogre::Vector3& pos, const Ogre::Real x, const Ogre::Real y);

    yz::Id* throwRay(const Ogre::Real x, const Ogre::Real y, const bool poly);

    Ogre::Vector3 throwRayPos(const Ogre::Real x, const Ogre::Real y);

    std::vector<yz::Id*> throwPlaneRay(Ogre::Real x1, Ogre::Real x2, Ogre::Real y1, Ogre::Real y2);

    inline static yz::Query* get(const POINTER pointer) {
        LOG_FUNCTION
        return reinterpret_cast<yz::Query*>(pointer);
    }

private:

    static yz::Id* ID_WORLD;

    yz::RayProvider* provider;

    Ogre::RaySceneQuery* query;

    Ogre::PlaneBoundedVolumeListSceneQuery* planeQuery;

};

}

#endif
