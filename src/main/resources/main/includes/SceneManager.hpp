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

#ifndef YZ_SCENEMANAGER_H
#define YZ_SCENEMANAGER_H

#define SCENEMANAGER yz::SceneManager

#include <Ogre.h>
#include "CollisionTools.h"
#include "PointLight.hpp"
#include "SpotLight.hpp"
#include "DirectionalLight.hpp"
#include "Camera.hpp"
#include "DynamicLine.hpp"
#include "Node.hpp"
#include "Lensflare.hpp"
#include "ParticleSystem.hpp"
#include "BillboardSet.hpp"
#include "ElectricArc.hpp"
#include "Entity.hpp"
#include "Query.hpp"
#include "GroundQuery.hpp"
#include "RayProvider.hpp"

namespace yz {

/**
 * Wrap an Ogre::SceneManager to provide construction and management for graphic objects.
 *@author Grégory Van den Borre
 */
class SceneManager {

public:
    SceneManager(Ogre::SceneManager* sm);

    inline void preloadMesh(const std::string& mesh) {
        LOG_FUNCTION
        this->sceneManager->createEntity("preload_" + mesh, mesh, "General");
    }

    inline void setShadowTextureSize(const int size) {
        LOG_FUNCTION
        this->sceneManager->setShadowTextureSize(size);
    }

    inline void setShadowFarDistance(const int distance) {
        LOG_FUNCTION
        this->sceneManager->setShadowFarDistance(distance);
    }

    inline void setShadowType(const int shadowType) {
        LOG_FUNCTION
        Ogre::ShadowTechnique shadow;
        switch (shadowType) {
        case 0:
            shadow = Ogre::SHADOWTYPE_NONE;
            break;
        case 1:
            shadow = Ogre::SHADOWTYPE_TEXTURE_ADDITIVE;
            break;
        case 2:
            shadow = Ogre::SHADOWTYPE_TEXTURE_MODULATIVE;
            break;
        case 3:
            shadow = Ogre::SHADOWTYPE_STENCIL_ADDITIVE;
            break;
        case 4:
            shadow = Ogre::SHADOWTYPE_STENCIL_MODULATIVE;
            break;
        default:
            shadow = Ogre::SHADOWTYPE_NONE;
            break;
        }
        this->sceneManager->setShadowTechnique(shadow);
    }

    inline void setDebugMode() {
        LOG_FUNCTION
        this->debug = true;
        Ogre::Node::ChildNodeMap children = this->sceneManager->getRootSceneNode()->getChildren();
        for (int i = 0; i < children.size(); i++) {
            static_cast<Ogre::SceneNode*>(children.at(i))->showBoundingBox(true);
	    }
    }

    yz::Camera* createCamera(const std::string& name);

    yz::Query* createQuery(yz::RayProvider* provider);

    yz::GroundQuery* createGroundQuery(yz::RayProvider* provider, yz::Node* e);

    //FIXME use java sky object and retrieve name from native.
    inline void setSkyBox(const std::string& file) {
        LOG_FUNCTION
        this->sceneManager->setSkyBox(true, file);
    }

    inline yz::Node* getRootNode() {
        LOG_FUNCTION
        return this->rootNode;
    }

    yz::PointLight* createPointLight(
        const std::string& name,
        const Ogre::Real x,
        const Ogre::Real y,
        const Ogre::Real z);

    yz::SpotLight* createSpotLight(
        const std::string& name,
        const Ogre::Real x,
        const Ogre::Real y,
        const Ogre::Real z,
        const Ogre::Real dirX,
        const Ogre::Real dirY,
        const Ogre::Real dirZ);

    yz::DirectionalLight* createDirectionalLight(
        const std::string& name,
        const Ogre::Real x,
        const Ogre::Real y,
        const Ogre::Real z,
        const Ogre::Real dirX,
        const Ogre::Real dirY,
        const Ogre::Real dirZ);

    Ogre::Vector3 getPoint(
        const Ogre::Vector3&,
        yz::Camera* cam,
        const Ogre::Real x,
        const Ogre::Real y);

    inline yz::Entity* createEntity(const std::string& mesh) {
        LOG_FUNCTION
        yz::Entity* e = new yz::Entity(this->sceneManager->createEntity(mesh));
        e->setQueryFlags(Ogre::SceneManager::ENTITY_TYPE_MASK);
        return e;
    }

    Ogre::Entity* createUnpickableEntity(const std::string& mesh);

    inline yz::ParticleSystem* createParticleSystem() {
        LOG_FUNCTION
        return new yz::ParticleSystem(this->sceneManager->createParticleSystem());
    }

    inline yz::BillboardSet* createBillboardSet(yz::Material* material) {
        LOG_FUNCTION
        yz::BillboardSet* set = new yz::BillboardSet(this->sceneManager->createBillboardSet());
        set->setMaterial(material);
        return set;
    }

    inline yz::Node* createNode(const std::string& name) {
        LOG_FUNCTION
        yz::Node* node = new yz::Node(this->sceneManager->getRootSceneNode()->createChildSceneNode(name));
        if (this->debug) {
            node->showBoundingBox(true);
        }
        return node;
    }

    /**
     * Create a yz::Node and associate it with an ID.
     */
    inline yz::Node* createNode(yz::Id* id, const std::string& name) {
        LOG_FUNCTION
        yz::Node* node = new yz::Node(this->sceneManager->getRootSceneNode()->createChildSceneNode(name), id);
        if (this->debug) {
            node->showBoundingBox(true);
        }
        return node;
    }

    yz::LensFlare* createLensFlare(
        const std::string& name,
        yz::Material* light,
        yz::Material* streak,
        yz::Material* halo,
        yz::Material* burst,
        const Ogre::Real x,
        const Ogre::Real y,
        const Ogre::Real z);

    inline void setAmbientLight(
    		const Ogre::Real red,
    		const Ogre::Real green,
    		const Ogre::Real blue,
    		const Ogre::Real alpha) {
        LOG_FUNCTION
        this->sceneManager->setAmbientLight(Ogre::ColourValue(red, green, blue, alpha));
    }

    inline yz::Entity* createCube(const std::string& name) {
        LOG_FUNCTION
        return this->createEntity(this->sceneManager->createEntity(name, Ogre::SceneManager::PT_CUBE));
    }

    inline yz::Entity* createCube() {
        LOG_FUNCTION
        return this->createEntity(this->sceneManager->createEntity(Ogre::SceneManager::PT_CUBE));
    }

    inline yz::Entity* createPlane(const std::string& name) {
        LOG_FUNCTION
        return new yz::Entity(this->sceneManager->createEntity(name, Ogre::SceneManager::PT_PLANE));
    }

    inline yz::Entity* createPlane() {
        LOG_FUNCTION
        return new yz::Entity(this->sceneManager->createEntity(Ogre::SceneManager::PT_PLANE));
    }

    inline yz::Entity* createSphere(const std::string& name) {
        LOG_FUNCTION
        return this->createEntity(this->sceneManager->createEntity(name, Ogre::SceneManager::PT_SPHERE));
    }

    yz::Entity* createSphere(
        const std::string& name,
        const int ring,
        const int segment,
        const float radius = 100.0f);

    inline yz::Entity* createSphere() {
        LOG_FUNCTION
        return this->createEntity(this->sceneManager->createEntity(Ogre::SceneManager::PT_SPHERE));

    }

    inline Ogre::SceneManager* getSceneManager() {
        LOG_FUNCTION
        return this->sceneManager;
    }

    inline yz::ElectricArc* createElectricArc(
          const std::string& name,
          const Ogre::Real x,
          const Ogre::Real y,
          const Ogre::Real z,
          const Ogre::Real eX,
          const Ogre::Real eY,
          const Ogre::Real eZ,
          const Ogre::Real width) {
        LOG_FUNCTION
        Node* start = this->createNode(name + "01");
        start->setPosition(x, y, z);
        Node* end = this->createNode(name + "02");
        end->setPosition(eX, eY, eZ);
        Node* base = this->createNode(name + "03");
        return new yz::ElectricArc(start, end, base, name, width);
    }

private:
    Ogre::SceneManager* sceneManager;
    bool debug;
    yz::Node* rootNode;

    yz::Entity* createEntity(Ogre::Entity* e) {
        e->setMaterialName("_internal_red_");
        e->setQueryFlags(Ogre::SceneManager::ENTITY_TYPE_MASK);
        return new yz::Entity(e);
    }
};
}
#endif

