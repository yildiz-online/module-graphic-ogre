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

#ifndef YZ_NODE_H
#define YZ_NODE_H

#include "stdafx.h"
#include <Ogre.h>
#include <OgreSceneNode.h>
#include <OgreMovableObject.h>
#include "AbstractNodeListener.hpp"
#include "NodeListeners.hpp"
#include "AbstractMovable.hpp"
#include <OgreSceneManager.h>

namespace YZ {

/**
 * Simple wrapper for an Ogre::Scenenode, this class provide uniform use for setting direction, yaw,...
 * @author Grégory Van den Borre
 */
class Node {

public:

	/**
	 * Full constructor.
	 * @param wrappedNode
	 *           Node used as wrapped object.
	 */
	Node(Ogre::SceneNode* wrappedNode) {
	    LOG_FUNCTION
		this->node = wrappedNode;
		this->listenerList = new YZ::NodeListeners();
		this->node->setListener(this->listenerList);
	}

	Node(Ogre::SceneNode* wrappedNode, YZ::Id* id) {
	    LOG_FUNCTION
		this->node = wrappedNode;
		this->listenerList = new YZ::NodeListeners();
		this->node->setListener(this->listenerList);
		this->node->getUserObjectBindings().setUserAny(Ogre::Any(id));
	}

	~Node(void) {
	    LOG_FUNCTION
		this->destroy();
        this->node = NULL;
	}

	inline void attachTo(YZ::Node* other) {
	    LOG_FUNCTION
		Ogre::SceneNode* parent = this->node->getParentSceneNode();
		parent->removeChild(this->node);
		other->addChild(this);
	}

	inline void addChild(YZ::Node* child) {
	    LOG_FUNCTION
		this->node->addChild(child->getWrappedNode());
	}

	/**
	 * @return The wrapped Ogre::SceneNode
	 */
	inline Ogre::SceneNode* getWrappedNode(void) {
	    LOG_FUNCTION
		return this->node;
	}

	inline void needUpdate(void) {
	    LOG_FUNCTION
		this->node->needUpdate();
	}

	/**
	 * Display every objects attached on this node.
	 */
	inline void show(void) {
	    LOG_FUNCTION
		this->node->setVisible(true);
	}

	/**
	 * Hide every objects attached on this node.
	 */
	inline void hide(void) {
	    LOG_FUNCTION
		this->node->setVisible(false);
	}

	void attachObject(YZ::AbstractMovable* movable) {
	    LOG_FUNCTION
		this->node->attachObject(movable->getMovableObject());
	}

	inline void addListener(YZ::AbstractNodeListener* l) {
	    LOG_FUNCTION
		this->listenerList->addListener(l);
	}

	/**
	 * Rotate only on Y axis to face a point.
	 */
	inline void rotateTo(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z) {
	    LOG_FUNCTION
		Ogre::Vector3 yAxis = this->node->getOrientation().yAxis();
		Ogre::Quaternion rotation = yAxis.getRotationTo(yAxis, Ogre::Vector3::UNIT_Y);
		this->node->pitch(rotation.getPitch());
		this->node->roll(rotation.getRoll());
	}

	/**
	 * Create a child for this node.
	 * @return A new YZ::Node child of this one.
	 */
	inline YZ::Node* createChildNode(void) {
	    LOG_FUNCTION
		YZ::Node* child = new YZ::Node(this->node->createChildSceneNode());
		//     this->childrenList.push_back(child);
		return child;
	}

	/**
	 * Get the wrapped node name.
	 * @return The name.
	 */
	inline std::string getName(void) const{
	    LOG_FUNCTION
		return this->node->getName();
	}

	inline void destroy(void) {
	    LOG_FUNCTION
		for (unsigned int i = 0; i < this->manualList.size(); ++i) {
			Ogre::MovableObject* o = this->manualList.at(i);
			this->node->detachObject(o);
			delete o;
		}
		this->destroyAllAttachedMovableObjects(this->node);
		this->node->removeAndDestroyAllChildren();
		this->node->getCreator()->destroySceneNode(this->node);
	}

	/**
	 * Scale all objects attached to the node.
	 * @param value
	 *           Scale value.
	 */
	inline void scale(const Ogre::Real value) {
	    LOG_FUNCTION
		this->scale(value, value, value);
	}

	/**
	 * Scale all objects attached to the node.
	 * @param scaleX
	 *           X scale value.
	 * @param scaleY
	 *           y scale value.
	 * @param scaleZ
	 *           Z scale value.
	 */
	inline void scale(const Ogre::Real scaleX, const Ogre::Real scaleY,
			const Ogre::Real scaleZ) {
	    LOG_FUNCTION
		this->node->scale(scaleX, scaleY, scaleZ);
	}

	inline void rotate(const Ogre::Real w, const Ogre::Real x, const Ogre::Real y,
			const Ogre::Real z) {
	    LOG_FUNCTION
		this->node->rotate(Ogre::Quaternion(w, x, y, z));
	}

	/**
	 * Rotate the node.
	 * @param x
	 *           X axis rotation angle, in radians.
	 * @param y
	 *           Y axis rotation angle, in radians.
	 */
	inline Ogre::Vector3 rotate(const Ogre::Real x, const Ogre::Real y) {
	    LOG_FUNCTION
		this->node->yaw(Ogre::Radian(x), Ogre::Node::TS_WORLD);
		this->node->pitch(Ogre::Radian(y), Ogre::Node::TS_WORLD);
		Ogre::Quaternion rotation = node->getOrientation();
		return rotation.zAxis();
	}

	inline Ogre::Quaternion getOrientation(void) {
	    LOG_FUNCTION
		return this->node->getOrientation();
	}

	/**
	 * Set the node position.
	 * @param x
	 *           New X position.
	 * @param y
	 *           New y position.
	 * @param z
	 *           New Z position.
	 */
	inline void setPosition(const Ogre::Real x, const Ogre::Real y,
			const Ogre::Real z) {
	    LOG_FUNCTION
		this->node->setPosition(x, y, z);
	}

	/**
	 * Set the direction using Ogre::Node::TS_WORLD and Ogre::Vector3::NEGATIVE_UNIT_Z.
	 * @param x
	 *           New X direction.
	 * @param y
	 *           New y direction.
	 * @param z
	 *           New Z direction.
	 */
	inline void setDirection(const Ogre::Real x, const Ogre::Real y,
			const Ogre::Real z) {
	    LOG_FUNCTION
		this->node->setDirection(x, y, z, Ogre::Node::TS_WORLD,
				Ogre::Vector3::NEGATIVE_UNIT_Z);
	}

	inline void setOrientation(const Ogre::Real w, const Ogre::Real x,
			const Ogre::Real y, const Ogre::Real z) {
	    LOG_FUNCTION
		this->node->setOrientation(w, x, y, z);
	}

	inline void translate(const Ogre::Real x, const Ogre::Real y,
			const Ogre::Real z) {
	    LOG_FUNCTION
		node->translate(x, y, z, Ogre::Node::TS_WORLD);
	}

	inline Ogre::Vector3 getPosition(void) const {
	    LOG_FUNCTION
		return this->node->getPosition();
	}

	inline Ogre::Vector3 getDirection(void) const {
	    LOG_FUNCTION
		return this->node->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
	}

	inline Ogre::Vector3 getWorldDirection(void) const {
	    LOG_FUNCTION
		return this->node->_getDerivedOrientation()
				* Ogre::Vector3::NEGATIVE_UNIT_Z;
	}

	inline void showBoundingBox(const bool visible) {
	    LOG_FUNCTION
		this->node->showBoundingBox(visible);
	}
    
    inline void detachFromParent() {
        LOG_FUNCTION
        Ogre::SceneNode* parent = this->node->getParentSceneNode();
		parent->removeChild(this->node);
		this->node->getCreator()->getRootSceneNode()->addChild(this->node);
    }

	inline void addManualMovable(Ogre::MovableObject* manual) {
	    LOG_FUNCTION
		this->manualList.push_back(manual);
	}

	inline static YZ::Node* get(const POINTER pointer) {
	    LOG_FUNCTION
		return reinterpret_cast<YZ::Node*>(pointer);
	}

private:

    /**
    * Wrapped Ogre::Node.
    */
	Ogre::SceneNode* node;

	YZ::NodeListeners* listenerList;

	/**
	 * List containing object manually created(not using scene manager), they must be detached and manually deleted.
	 */
	std::vector<Ogre::MovableObject*> manualList;

	void destroyAllAttachedMovableObjects(Ogre::SceneNode* i_pSceneNode) {

		// Destroy all the attached objects
		Ogre::SceneNode::ObjectIterator itObject =
				i_pSceneNode->getAttachedObjectIterator();
		while (itObject.hasMoreElements()) {
			Ogre::MovableObject* pObject =
					static_cast<Ogre::MovableObject*>(itObject.getNext());
			i_pSceneNode->getCreator()->destroyMovableObject(pObject);
		}
		// Recurse to child SceneNodes
		Ogre::SceneNode::ChildNodeIterator itChild =
				i_pSceneNode->getChildIterator();
		while (itChild.hasMoreElements()) {
			Ogre::SceneNode* pChildNode =
					static_cast<Ogre::SceneNode*>(itChild.getNext());
			destroyAllAttachedMovableObjects(pChildNode);
		}
	}
};
}

#endif
