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

#ifndef GUI_CONTAINER_H
#define GUI_CONTAINER_H

#include "stdafx.h"
#include "Material.hpp"
#include <Overlay/OgreOverlayContainer.h>
#include <Overlay/OgreOverlayElement.h>
#include <Overlay/OgreOverlay.h>

namespace yz {

/**
 * Wrap an Ogre::OverlayContainer.
 * @author Grégory Van Den Borre
 */
class GuiContainer {

public:

	/**
	 * Full constructor.
	 * @param name Container name, must be unique.
	 * @param material Material name to use as background.
	 * @param width Container width.
	 * @param height Container height.
	 */
	GuiContainer(const std::string& name, const yz::Material* material,
			const Ogre::Real width, const Ogre::Real height);

	GuiContainer(const std::string& name, const yz::Material* material,
			const Ogre::Real width, const Ogre::Real height, GuiContainer* parent);

	/**
	 * Destructor.
	 */
	virtual ~GuiContainer();

	/**
	 * Move the container.
	 * @param x Value to move to left.
	 * @param y Value to move to top.
	 */
	inline void move(const Ogre::Real x, const Ogre::Real y) {
	    LOG_FUNCTION
		Ogre::Real posX = this->container->getLeft() - x;
		Ogre::Real posY = this->container->getTop() - y;
		this->container->setPosition(posX, posY);
	}

	/**
	 * Set the container visible.
	 */
	inline void show() {
	    LOG_FUNCTION
		this->container->show();
	}

	/**
	 * Set the container invisible.
	 */
	inline void hide() {
	    LOG_FUNCTION
		this->container->hide();
	}

	/**
	 * Check if a position is in the container.
	 * @param x Position X value.
	 * @param y position Y value.
	 * @return true if the position is inside the container, false otherwise.
	 */
	inline bool contains(const Ogre::Real x, const Ogre::Real y) {
	    LOG_FUNCTION
		return this->container->contains(x, y);
	}

	/**
	 * Add a child element to the container.
	 * @param element Child to add.
	 */
	inline void addChild(Ogre::OverlayElement* element) {
	    LOG_FUNCTION
		this->container->addChild(element);
	}

	/**
	 * Get the element name at the given position in the container,
	 * if none found return the container name.
	 * @param x Position x value to check.
	 * @param y Position y value to check.
	 * @return The found element name, or the container name if no element is found.
	 */
	inline std::string getElementAt(const Ogre::Real x, const Ogre::Real y) const {
	    LOG_FUNCTION
		return this->overlay->findElementAt(x, y)->getName();
	}

	/**
	 * Modify the container elements size and position.
	 * @param factor The elements size and position will be multiplied by this value.
	 */
	inline void zoom(const Ogre::Real factor) {
	    LOG_FUNCTION
		this->overlay->setScale(factor, factor);
	}

	/**
	 * Modify the container size.
	 * @param width New container width.
	 * @param height New container height.
	 */
	inline void setSize(const Ogre::Real width, const Ogre::Real height) {
	    LOG_FUNCTION
		this->container->setDimensions(width, height);
	}

	/**
	 * @return The container height.
	 */
	inline Ogre::Real getHeight() const {
	    LOG_FUNCTION
		return this->container->getHeight();
	}

	/**
	 * @return The container width.
	 */
	inline Ogre::Real getWidth() const {
	    LOG_FUNCTION
		return this->container->getWidth();
	}

	/**
	 * @return The container left position, in pixel.
	 */
	inline Ogre::Real getLeft() const {
	    LOG_FUNCTION
		return this->container->getLeft();
	}

	/**
	 * @return The container top position, in pixel.
	 */
	inline Ogre::Real getTop() const {
	    LOG_FUNCTION
		return this->container->getTop();
	}

	/**
	 * Modify the depth container order.
	 * @param Depth order, a container with a higher value is rendered above the containers with lower values.
	 */
	inline void setZ(const short z) {
	    LOG_FUNCTION
		this->overlay->setZOrder(z);
	}

	/**
	 * Set the container position.
	 * @param left Left position.
	 * @param top Top position.
	 */
	inline void setPosition(const Ogre::Real left, const Ogre::Real top) {
	    LOG_FUNCTION
		this->container->setPosition(left, top);
	}

	/**
	 * Set the container background material.
	 * @param material Material name.
	 */
	inline void setMaterial(const yz::Material* material) {
	    LOG_FUNCTION
		this->container->setMaterialName(material->getName());
	}

	inline void addToChildren(const Ogre::Real left, const Ogre::Real top) {
	    LOG_FUNCTION
		Ogre::OverlayContainer::ChildIterator it =
				this->container->getChildIterator();
		while (it.hasMoreElements()) {
			Ogre::OverlayElement* e = it.getNext();
			e->setPosition(e->getLeft() + left, e->getTop() + top);
		}
	}

    inline static yz::GuiContainer* get(const POINTER pointer) {
        LOG_FUNCTION
        return reinterpret_cast<yz::GuiContainer*>(pointer);
    }

private:

	/**
	 * Overlay containing the container.
	 */
	Ogre::Overlay* overlay;

	/**
	 * Wrapped container.
	 */
	Ogre::OverlayContainer* container;
};
}

#endif
