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

/**
*@author Grégory Van den Borre
*/

#include "../includes/Lensflare.hpp"

yz::LensFlare::LensFlare(yz::Node* node, yz::BillboardSet* light, yz::BillboardSet* streak, yz::BillboardSet* halo, yz::BillboardSet* burst, Ogre::RaySceneQuery* query, Ogre::Real x, Ogre::Real y, Ogre::Real z) :
node(node), lightFlareSet(light), streakSet(streak), haloSet(halo), burstSet(burst), query(query) {
    LOG_FUNCTION
	this->node->setPosition(x, y, z);

    this->lightFlareSet->hide();
    this->streakSet->hide();
    this->haloSet->hide();
    this->burstSet->hide();

    yz::Billboard* lightFlare = this->lightFlareSet->createBillboard();
    lightFlare->setDimensions(512, 512);

    yz::Billboard* streak1 = this->streakSet->createBillboard();
    streak1->setDimensions(512, 512);

    yz::Billboard* halo1 = this->haloSet->createBillboard();
    halo1->setDimensions(250, 250);
    yz::Billboard* halo2 = this->haloSet->createBillboard();
    halo2->setDimensions(500, 500);
    yz::Billboard* halo3 = this->haloSet->createBillboard();
    halo3->setDimensions(125, 125);

    yz::Billboard* burst1 = this->burstSet->createBillboard();
    burst1->setDimensions(125, 125);
    yz::Billboard* burst2 = this->burstSet->createBillboard();
    burst2->setDimensions(250, 250);
    yz::Billboard* burst3 = this->burstSet->createBillboard();
    burst3->setDimensions(125, 125);

    this->node->attachObject(this->streakSet);
    this->node->attachObject(this->lightFlareSet);
    this->node->attachObject(this->haloSet);
    this->node->attachObject(this->burstSet);
}

void yz::LensFlare::cameraUpdated(const Ogre::Camera* camera) {
    LOG_FUNCTION
    Ogre::Vector3 camPosition = camera->getParentSceneNode()->getPosition();
    Ogre::Vector3 camDirection = camera->getParentSceneNode()->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;

    this->query->setRay(Ogre::Ray(camPosition, this->node->getPosition()));
    Ogre::RaySceneQueryResult result = this->query->execute();
    if(result.size() > 0) {
        this->streakSet->hide();
        this->burstSet->hide();
        this->haloSet->hide();
        this->lightFlareSet->hide();
    } else {
        this->streakSet->show();
        this->burstSet->show();
        this->haloSet->show();
        this->lightFlareSet->show();
        Ogre::Real lightDistance = this->node->getPosition().distance(camPosition);

		Ogre::Real dX = camDirection.x;
		Ogre::Real dY = camDirection.y;
		Ogre::Real dZ = camDirection.z;

        dX *= lightDistance;
        dY *= lightDistance;
        dZ *= lightDistance;

        dX -= this->node->getPosition().x;
        dY -= this->node->getPosition().y;
        dZ -= this->node->getPosition().z;

        Ogre::Real multiply1[] = {0.500f,  0.125f, -0.250f};
        Ogre::Real multiply2[] = {0.333f, -0.500f, -0.180f};

        for(int i = 0; i < 3; i++) {
            haloSet->getBillboard(i)->setPosition(
                dX * multiply1[i],
                dY * multiply1[i],
                dZ * multiply1[i]);
            burstSet->getBillboard(i)->setPosition(
                dX * multiply2[i],
                dY * multiply2[i],
                dZ * multiply2[i]);
        }
    }
}
