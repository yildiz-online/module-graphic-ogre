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

#ifndef ELECTRIC_ARC_H
#define ELECTRIC_ARC_H

#define ELECTRICARC YZ::ElectricArc

#include "Node.hpp"
#include "PointLight.hpp"
#include "BillboardChain.hpp"
#include "Material.hpp"

namespace YZ {

/**
*@author Grégory Van den Borre
*/
class ElectricArc : public Ogre::FrameListener {
public:

    /**
     * Full constructor.
     * @param startNode Node for arc origin.
     * @param endNode Node for arc end.
     */
	ElectricArc(YZ::Node* startNode, YZ::Node* endNode, YZ::Node* baseNode, const std::string& name, const Ogre::Real width);

	~ElectricArc(void);

	inline void setMaterial(YZ::Material* material) {
	    LOG_FUNCTION
        this->chain->setMaterial(material);
    }


	inline bool frameRenderingQueued(const Ogre::FrameEvent& evt) {
	    LOG_FUNCTION
		return true;
	}

	inline bool frameEnded(const Ogre::FrameEvent& evt) {
	    LOG_FUNCTION
		return true;
	}

	inline void setCeil(const int ceil) {
	    LOG_FUNCTION
	    this->ceil = ceil;
	}

	void addLight(YZ::PointLight* light);

    bool frameStarted(const Ogre::FrameEvent& evt);

    static inline YZ::ElectricArc* get(const POINTER pointer) {
        LOG_FUNCTION
        return reinterpret_cast<YZ::ElectricArc*>(pointer);
    }

	private:
		static const int MAX_STEP = 20;
		YZ::BillboardChain* chain;
		YZ::Node* start;
		YZ::Node* end;
		YZ::Node* base;
		Ogre::Vector3 startPosition;
		Ogre::Vector3 endPosition;
		YZ::PointLight* light;
		bool hasLight;
		int ceil;
};
}

#endif

