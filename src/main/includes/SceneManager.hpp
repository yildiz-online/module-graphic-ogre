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

#ifndef YZ_SCENEMANAGER_H
#define YZ_SCENEMANAGER_H

#define SCENEMANAGER YZ::SceneManager

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

namespace YZ {

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
        Ogre::SceneNode::ChildNodeIterator it =
                this->sceneManager->getRootSceneNode()->getChildIterator();
        while (it.hasMoreElements()) {
            dynamic_cast<Ogre::SceneNode*>(it.getNext())->showBoundingBox(true);
        }
    }

    YZ::Camera* createCamera(const std::string& name);

    //FIXME use java sky object and retrieve name from native.
    inline void setSkyBox(const std::string& file) {
        LOG_FUNCTION
        this->sceneManager->setSkyBox(true, file);
    }

    inline YZ::Node* getRootNode() {
        LOG_FUNCTION
        return this->rootNode;
    }

    YZ::PointLight* createPointLight(
        const std::string& name,
        const Ogre::Real x,
        const Ogre::Real y,
        const Ogre::Real z);

    YZ::SpotLight* createSpotLight(
        const std::string& name,
        const Ogre::Real x,
        const Ogre::Real y,
        const Ogre::Real z,
        const Ogre::Real dirX,
        const Ogre::Real dirY,
        const Ogre::Real dirZ);

    YZ::DirectionalLight* createDirectionalLight(
        const std::string& name,
        const Ogre::Real x,
        const Ogre::Real y,
        const Ogre::Real z,
        const Ogre::Real dirX,
        const Ogre::Real dirY,
        const Ogre::Real dirZ);

    Ogre::Vector3 getPoint(
        const Ogre::Vector3&,
        YZ::Camera* cam,
        const Ogre::Real x,
        const Ogre::Real y);

    inline YZ::Entity* createEntity(const std::string& mesh) {
        LOG_FUNCTION
        YZ::Entity* e = new YZ::Entity(this->sceneManager->createEntity(mesh));
        e->setQueryFlags(Ogre::SceneManager::ENTITY_TYPE_MASK);
        return e;
    }

    Ogre::Entity* createUnpickableEntity(const std::string& mesh);

    inline YZ::ParticleSystem* createParticleSystem() {
        LOG_FUNCTION
        return new YZ::ParticleSystem(
                this->sceneManager->createParticleSystem());
    }

    inline YZ::BillboardSet* createBillboardSet(YZ::Material* material) {
        LOG_FUNCTION
        YZ::BillboardSet* set = new YZ::BillboardSet(this->sceneManager->createBillboardSet());
        set->setMaterial(material);
        return set;
    }

    inline YZ::Node* createNode(const std::string& name) {
        LOG_FUNCTION
        YZ::Node* node = new YZ::Node(
                this->sceneManager->getRootSceneNode()->createChildSceneNode(
                        name));
        if (this->debug) {
            node->showBoundingBox(true);
        }
        return node;
    }

    /**
     * Create a YZ::Node and associate it with an ID.
     */
    inline YZ::Node* createNode(YZ::Id* id, const std::string& name) {
        LOG_FUNCTION
        YZ::Node* node = new YZ::Node(
                this->sceneManager->getRootSceneNode()->createChildSceneNode(
                        name), id);
        if (this->debug) {
            node->showBoundingBox(true);
        }
        return node;
    }

    YZ::LensFlare* createLensFlare(
        const std::string& name,
        YZ::Material* light,
        YZ::Material* streak,
        YZ::Material* halo,
        YZ::Material* burst,
        const Ogre::Real x,
        const Ogre::Real y,
        const Ogre::Real z);

    inline void setAmbientLight(
    		const Ogre::Real red,
    		const Ogre::Real green,
    		const Ogre::Real blue,
    		const Ogre::Real alpha) {
        LOG_FUNCTION
        this->sceneManager->setAmbientLight(
                Ogre::ColourValue(red, green, blue, alpha));
    }

    inline YZ::Entity* createCube(const std::string& name) {
        LOG_FUNCTION
        Ogre::Entity* e = this->sceneManager->createEntity(name,
                Ogre::SceneManager::PT_CUBE);
        e->setMaterialName("_internal_red_");
        return new YZ::Entity(e);
    }

    inline YZ::Entity* createCube() {
        LOG_FUNCTION
        return new YZ::Entity(this->sceneManager->createEntity(Ogre::SceneManager::PT_CUBE));
    }

    inline YZ::Entity* createPlane(const std::string& name) {
        LOG_FUNCTION
        return new YZ::Entity(this->sceneManager->createEntity(name,
                Ogre::SceneManager::PT_PLANE));
    }

    inline YZ::Entity* createPlane() {
        LOG_FUNCTION
        return new YZ::Entity(this->sceneManager->createEntity(Ogre::SceneManager::PT_PLANE));
    }

    inline YZ::Entity* createSphere(const std::string& name) {
        LOG_FUNCTION
        return new YZ::Entity(this->sceneManager->createEntity(name,
                Ogre::SceneManager::PT_SPHERE));
    }

    YZ::Entity* createSphere(
        const std::string& name,
        const int ring,
        const int segment,
        const float radius = 100.0f);

    inline YZ::Entity* createSphere() {
        LOG_FUNCTION
        return new YZ::Entity(this->sceneManager->createEntity(Ogre::SceneManager::PT_SPHERE));
    }

    inline Ogre::SceneManager* getSceneManager() {
        LOG_FUNCTION
        return this->sceneManager;
    }

    inline YZ::ElectricArc* createElectricArc(
        const std::string& name, const Ogre::Real x, const Ogre::Real y, const Ogre::Real z,
        const Ogre::Real eX, const Ogre::Real eY, const Ogre::Real eZ, const Ogre::Real width) {
        LOG_FUNCTION
    Node* start = this->createNode(name + "01");
    start->setPosition(x, y, z);
    Node* end = this->createNode(name + "02");
    end->setPosition(eX, eY, eZ);
    Node* base = this->createNode(name + "03");
    return new YZ::ElectricArc(start, end, base, name, width);
    }

    static inline YZ::SceneManager* get(const POINTER pointer) {
        LOG_FUNCTION
        return reinterpret_cast<YZ::SceneManager*>(pointer);
    }

private:
    Ogre::SceneManager* sceneManager;
    bool debug;
    YZ::Node* rootNode;
};
}
#endif

