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

#ifndef LENSFLARE_H
#define LENSFLARE_H

#include "Node.hpp"
#include "AbstractCameraListener.hpp"
#include "BillboardSet.hpp"

namespace YZ {

/**
*@author Grégory Van den Borre
*/
class LensFlare: public YZ::AbstractCameraListener {

public:

	LensFlare(YZ::Node* node, YZ::BillboardSet* light, YZ::BillboardSet* streak,
			YZ::BillboardSet* halo, YZ::BillboardSet* burst,
			Ogre::RaySceneQuery* query, Ogre::Real x, Ogre::Real y,
			Ogre::Real z);

	virtual ~LensFlare() {
		/*LOG_FUNCTION
		 Ogre::SceneManager* sm = this->node->getSceneManager();
		 this->lightFlareSet->detachFromParent();
		 this->streakSet->detachFromParent();
		 this->haloSet->detachFromParent();
		 this->burstSet->detachFromParent();
		 sm->destroyBillboardSet(this->lightFlareSet);
		 sm->destroyBillboardSet(this->streakSet);
		 sm->destroyBillboardSet(this->haloSet);
		 sm->destroyBillboardSet(this->burstSet);
		 sm->destroyQuery(this->query);
		 this->node->destroy();*/
	}

	void cameraUpdated(const Ogre::Camera* camera);

	inline void setPosition(const Ogre::Real x, const Ogre::Real y,
			const Ogre::Real z) {
	    LOG_FUNCTION
		this->node->setPosition(x, y, z);
	}

	inline std::string getName(void) const {
	    LOG_FUNCTION
		return "LensFlare";
	}

	inline void setLightSize(const Ogre::Real width, const Ogre::Real height) {
	    LOG_FUNCTION
		this->lightFlareSet->setSize(width, height);
		this->lightFlareSet->getBillboard(0)->resetDimensions();
	}

	inline void setStreakSize(const Ogre::Real width, const Ogre::Real height) {
	    LOG_FUNCTION
		this->streakSet->setSize(width, height);
		this->streakSet->getBillboard(0)->resetDimensions();
	}

    static inline YZ::LensFlare* get(const POINTER pointer) {
        LOG_FUNCTION
        return reinterpret_cast<YZ::LensFlare*>(pointer);
    }

private:

	YZ::Node* node;

	Ogre::RaySceneQuery* query;

	YZ::BillboardSet* lightFlareSet;

	YZ::BillboardSet* streakSet;

	YZ::BillboardSet* haloSet;

	YZ::BillboardSet* burstSet;
};
}

#endif
