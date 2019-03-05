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

#include "../includes/SelectionRectangle.hpp"

yz::SelectionRectangle::SelectionRectangle(yz::Material* material, yz::Material* contentMat) {
    LOG_FUNCTION
    Ogre::OverlayManager& manager = Ogre::OverlayManager::getSingleton();
    //build container
    Ogre::Overlay* o = manager.create("selection_rectangle");
    
    o->show();
    Ogre::OverlayContainer* c = static_cast<Ogre::OverlayContainer*>(
    manager.createOverlayElement("Panel", "selectionRectangle", false));
    
    o->setZOrder(650);

    //first use it to avoid having to know the screen size to make it full screen.
    c->setMetricsMode(Ogre::GMM_RELATIVE);
    c->setDimensions(1, 1);
    c->setMetricsMode(Ogre::GMM_PIXELS);

    c->show();
    o->add2D(c);
    //TOP

    this->top = manager.createOverlayElement("Panel", "top", false);
    this->top->setMetricsMode(Ogre::GMM_PIXELS);
    this->top->setMaterialName(material->getName());

    this->top->show();
    c->addChild(top);

    //BOTTOM

    this->bottom = manager.createOverlayElement("Panel", "bottom", false);
    this->bottom->setMetricsMode(Ogre::GMM_PIXELS);
    this->bottom->setMaterialName(material->getName());

    this->bottom->show();
    c->addChild(bottom);
    //LEFT

    this->left = manager.createOverlayElement("Panel", "left", false);
    this->left->setMetricsMode(Ogre::GMM_PIXELS);
    this->left->setMaterialName(material->getName());

    this->left->show();
    c->addChild(left);

    //RIGHT
    this->right = manager.createOverlayElement("Panel", "right", false);
    this->right->setMetricsMode(Ogre::GMM_PIXELS);
    this->right->setMaterialName(material->getName());

    this->right->show();
    c->addChild(right);

    this->content = manager.createOverlayElement("Panel", "contentSelect", false);
    this->content->setMetricsMode(Ogre::GMM_PIXELS);
    this->content->setMaterialName(contentMat->getName());

    this->content->show();
    c->addChild(this->content);
}

void yz::SelectionRectangle::update(Ogre::Real x1, Ogre::Real y1, Ogre::Real x2, Ogre::Real y2) {
    LOG_FUNCTION
    if(x1 > x2) {
    	Ogre::Real temp = x1;
        x1 = x2;
        x2 = temp;
    }
    if (y1 > y2) {
    	Ogre::Real temp = y1;
        y1 = y2;
        y2 = temp;
    }

    const Ogre::Real x = x2 - x1;
    const Ogre::Real y = y2 - y1;

    this->top->setLeft(x1);
    this->top->setTop(y1);
    this->top->setWidth(x);

    this->bottom->setLeft(x1);
    this->bottom->setTop(y2);
    this->bottom->setWidth(x);

    this->left->setLeft(x1);
    this->left->setTop(y1);
    this->left->setHeight(y);

    this->right->setLeft(x2);
    this->right->setTop(y1);
    this->right->setHeight(y);

    this->content->setLeft(x1 + 1);
    this->content->setTop(y1 + 1);
    this->content->setDimensions(x - 2, y - 2);
  }

void yz::SelectionRectangle::hide() {
    LOG_FUNCTION
    this->top->setWidth(0);
    this->bottom->setWidth(0);
    this->left->setHeight(0);
    this->right->setHeight(0);
    this->content->setDimensions(0,0);
}

