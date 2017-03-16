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

#ifndef GUI_ICON_H
#define GUI_ICON_H

#define GUIICON yz::GuiIcon

#include "stdafx.h"
#include "GuiContainer.hpp"
#include "Material.hpp"

namespace yz {

/**
 * Wrap an Ogre::OverlayElement.
 * @author Grégory Van Den Borre
 */
class GuiIcon {

public:

	/**
	 * Full constructor.
	 * @param parent Container holding this element.
	 * @param name Icon name, must be unique.
	 * @param material Element material name.
	 * @param witdh Icon witdh.
	 * @param height Icon height.
	 */
	GuiIcon(yz::GuiContainer* parent, const std::string& name,
			const yz::Material* material, const Ogre::Real width,
			const Ogre::Real height);

	/**
	 * Destructor.
	 */
	virtual ~GuiIcon();

	/**
	 * Remove this element from its parent.
	 */
	inline void detachFromParent() {
	    LOG_FUNCTION
		Ogre::OverlayContainer* c = this->icon->getParent();
		c->removeChild(this->icon->getName());
	}

	/**
	 * Set the element visible.
	 */
	inline void show() {
	    LOG_FUNCTION
		this->icon->show();
	}

	/**
	 * Set the element invisible.
	 */
	inline void hide() {
	    LOG_FUNCTION
		this->icon->hide();
	}

	/**
	 * Set the new position for the element.
	 * @param left Left position from the container border, in pixel.
	 * @param top Top position from the container border, in pixel.
	 */
	inline void setPosition(const Ogre::Real left, const Ogre::Real top) {
	    LOG_FUNCTION
		this->icon->setPosition(left, top);
	}

	/**
	 * @return the wrapped element.
	 */
	inline Ogre::OverlayElement* getIcon() {
	    LOG_FUNCTION
		return this->icon;
	}

	/**
	 * @return The left position from the container border, in pixels.
	 */
	inline Ogre::Real getLeft() const {
	    LOG_FUNCTION
		return this->icon->getLeft();
	}

	/**
	 * @return The top position from the container border, in pixels.
	 */
	inline Ogre::Real getTop() const {
	    LOG_FUNCTION
		return this->icon->getTop();
	}

	/**
	 * @return The element width in pixel.
	 */
	inline Ogre::Real getWidth() const {
	    LOG_FUNCTION
		return this->icon->getWidth();
	}

	/**
	 * @return The element height, in pixel.
	 */
	inline Ogre::Real getHeight() const {
	    LOG_FUNCTION
		return this->icon->getHeight();
	}

	/**
	 * Set the element top position, from the parent container.
	 * @parameter top Top position, in pixel.
	 */
	inline void setTop(const Ogre::Real top) {
	    LOG_FUNCTION
		this->icon->setTop(top);
	}

	/**
	 * Set the element left position, from the parent container.
	 * @parameter left Left position, in pixel.
	 */
	inline void setLeft(const Ogre::Real left) {
	    LOG_FUNCTION
		this->icon->setLeft(left);
	}

	/**
	 * Set the element background material.
	 * @param material Material.
	 */
	inline void setMaterial(const yz::Material* material) {
	    LOG_FUNCTION
		this->icon->setMaterialName(material->getName());
	}

	/**
	 * Modifiy the element size.
	 * @param width New element width.
	 * @param height New element height.
	 */
	inline void setSize(const Ogre::Real width, const Ogre::Real height) {
	    LOG_FUNCTION
		this->icon->setDimensions(width, height);
	}

	inline int getZ() {
	    LOG_FUNCTION
		return this->icon->getZOrder();
	}

	inline std::string getParent() {
	    LOG_FUNCTION
		return this->icon->getParent()->getName();
	}

    inline static yz::GuiIcon* get(const POINTER pointer) {
        LOG_FUNCTION
        return reinterpret_cast<yz::GuiIcon*>(pointer);
    }

private:

	/**
	 * Wrapped overlay element.
	 */
	Ogre::OverlayElement* icon;
};
}

#endif
