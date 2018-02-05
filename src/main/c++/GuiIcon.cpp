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

#include "../includes/GuiIcon.hpp"

yz::GuiIcon::GuiIcon(yz::GuiContainer* parent, const std::string& name, const yz::Material* material, const Ogre::Real width, const Ogre::Real height) {
    LOG_FUNCTION
    this->icon = Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", name);
    parent->addChild(this->icon);
	this->icon->setMetricsMode(Ogre::GMM_PIXELS);
    this->icon->setMaterialName(material->getName());
    this->icon->setDimensions(width, height);
    this->icon->hide();
}

yz::GuiIcon::~GuiIcon() {
    LOG_FUNCTION
    Ogre::OverlayContainer* c = this->icon->getParent();
    c->removeChild(this->icon->getName());
    Ogre::OverlayManager::getSingleton().destroyOverlayElement(this->icon);
}
