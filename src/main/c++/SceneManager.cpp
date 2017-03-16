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

/**
*@author Grégory Van den Borre
*/

#include "../includes/SceneManager.hpp"

yz::SceneManager::SceneManager(Ogre::SceneManager* manager) : sceneManager(sceneManager) {
    LOG_FUNCTION
    this->debug = false;
    this->rootNode = new yz::Node(this->sceneManager->getRootSceneNode());
    this->sceneManager->setAmbientLight(Ogre::ColourValue::Black);
   /* this->collisionTool = new yz::CollisionTools(
    this->sceneManager->createRayQuery(Ogre::Ray(),
                    Ogre::SceneManager::ENTITY_TYPE_MASK),
    this->sceneManager->createRayQuery(Ogre::Ray(),
                    Ogre::SceneManager::ENTITY_TYPE_MASK));*/

    //this->query = this->sceneManager->createRayQuery(
    //    Ogre::Ray(), Ogre::SceneManager::ENTITY_TYPE_MASK);
    //this->query->setSortByDistance(true, 5);
    //this->mStencilOpFrameListener = new StencilOpQueueListener();
    //this->sceneManager->addRenderQueueListener(mStencilOpFrameListener);
}

yz::Camera* yz::SceneManager::createCamera(const std::string& name) {
    LOG_FUNCTION
    Ogre::RaySceneQuery* query = this->sceneManager->createRayQuery(Ogre::Ray());
    Ogre::PlaneBoundedVolumeListSceneQuery* planeQuery = this->sceneManager->createPlaneBoundedVolumeQuery(Ogre::PlaneBoundedVolumeList());
    yz::Camera* cam = new yz::Camera(this->sceneManager->createCamera(name), query, planeQuery);
    return cam;
}

Ogre::Entity* yz::SceneManager::createUnpickableEntity(
    const std::string& mesh) {
    LOG_FUNCTION
    Ogre::Entity* e = this->sceneManager->createEntity(mesh);
    e->setQueryFlags(Ogre::SceneManager::STATICGEOMETRY_TYPE_MASK);
    return e;
}

yz::LensFlare* yz::SceneManager::createLensFlare(
    const std::string& name,
    yz::Material* light,
    yz::Material* streak,
    yz::Material* halo,
    yz::Material* burst,
    const Ogre::Real x,
    const Ogre::Real y,
    const Ogre::Real z) {
    LOG_FUNCTION
    yz::BillboardSet* lightSet = this->createBillboardSet(light);
    yz::BillboardSet* streakSet = this->createBillboardSet(streak);
    yz::BillboardSet* haloSet = this->createBillboardSet(halo);
    yz::BillboardSet* burstSet = this->createBillboardSet(burst);
    Ogre::RaySceneQuery* query = this->sceneManager->createRayQuery(Ogre::Ray(),
            Ogre::SceneManager::ENTITY_TYPE_MASK);
    yz::Node* node = this->createNode(name);
    return new yz::LensFlare(node, lightSet, streakSet, haloSet, burstSet,
            query, x, y, z);
}

yz::Entity* yz::SceneManager::createSphere(
    const std::string& name,
    const int rings,
    const int segments,
    const Ogre::Real radius) {
    LOG_FUNCTION
    Ogre::MeshPtr sphere = Ogre::MeshManager::getSingleton().createManual(name,
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    Ogre::SubMesh *pSphereVertex = sphere->createSubMesh();

    sphere->sharedVertexData = new Ogre::VertexData();
    Ogre::VertexData* vertexData = sphere->sharedVertexData;

// define the vertex format
    Ogre::VertexDeclaration* vertexDecl = vertexData->vertexDeclaration;
    size_t currOffset = 0;
// positions
    vertexDecl->addElement(0, currOffset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
    currOffset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
// normals
    vertexDecl->addElement(0, currOffset, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
    currOffset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
// two dimensional texture coordinates
    vertexDecl->addElement(0, currOffset, Ogre::VET_FLOAT2,
            Ogre::VES_TEXTURE_COORDINATES, 0);
    currOffset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT2);

// allocate the vertex buffer
    vertexData->vertexCount = (rings + 1) * (segments + 1);
    Ogre::HardwareVertexBufferSharedPtr vBuf =
            Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
                    vertexDecl->getVertexSize(0), vertexData->vertexCount,
                    Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY, false);
    Ogre::VertexBufferBinding* binding = vertexData->vertexBufferBinding;
    binding->setBinding(0, vBuf);
    float* pVertex = static_cast<float*>(vBuf->lock(
            Ogre::HardwareBuffer::HBL_DISCARD));

// allocate index buffer
    pSphereVertex->indexData->indexCount = 6 * rings * (segments + 1);
    pSphereVertex->indexData->indexBuffer =
            Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(
                    Ogre::HardwareIndexBuffer::IT_16BIT,
                    pSphereVertex->indexData->indexCount,
                    Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY, false);
    Ogre::HardwareIndexBufferSharedPtr iBuf =
            pSphereVertex->indexData->indexBuffer;
    unsigned short* pIndices = static_cast<unsigned short*>(iBuf->lock(
            Ogre::HardwareBuffer::HBL_DISCARD));

    float fDeltaRingAngle = (Ogre::Math::PI / rings);
    float fDeltaSegAngle = (2 * Ogre::Math::PI / segments);
    unsigned short wVerticeIndex = 0;

// Generate the group of rings for the sphere
    for (int ring = 0; ring <= rings; ring++) {
        float r0 = radius * sinf(ring * fDeltaRingAngle);
        float y0 = radius * cosf(ring * fDeltaRingAngle);

        // Generate the group of segments for the current ring
        for (int seg = 0; seg <= segments; seg++) {
            float x0 = r0 * sinf(seg * fDeltaSegAngle);
            float z0 = r0 * cosf(seg * fDeltaSegAngle);

            // Add one vertex to the strip which makes up the sphere
            *pVertex++ = x0;
            *pVertex++ = y0;
            *pVertex++ = z0;

            Ogre::Vector3 vNormal = Ogre::Vector3(x0, y0, z0).normalisedCopy();
            *pVertex++ = vNormal.x;
            *pVertex++ = vNormal.y;
            *pVertex++ = vNormal.z;

            *pVertex++ = (float) seg / (float) segments;
            *pVertex++ = (float) ring / (float) rings;

            if (ring != rings) {
                // each vertex (except the last) has six indices pointing to it
                *pIndices++ = wVerticeIndex + segments + 1;
                *pIndices++ = wVerticeIndex;
                *pIndices++ = wVerticeIndex + segments;
                *pIndices++ = wVerticeIndex + segments + 1;
                *pIndices++ = wVerticeIndex + 1;
                *pIndices++ = wVerticeIndex;
                wVerticeIndex++;
            }
        }; // end for seg
    } // end for ring

// Unlock
    vBuf->unlock();
    iBuf->unlock();
// Generate face list
    pSphereVertex->useSharedVertices = true;

// the original code was missing this line:
    sphere->_setBounds(
            Ogre::AxisAlignedBox(Ogre::Vector3(-radius, -radius, -radius),
                    Ogre::Vector3(radius, radius, radius)), false);
    sphere->_setBoundingSphereRadius(radius);
// this line makes clear the mesh is loaded (avoids memory leaks)
    sphere->load();
    return new yz::Entity(this->sceneManager->createEntity(name));
}

yz::PointLight* yz::SceneManager::createPointLight(
    const std::string& name,
    const Ogre::Real x,
    const Ogre::Real y,
    const Ogre::Real z) {
    LOG_FUNCTION
    Ogre::Light* base = this->sceneManager->createLight(name);
    base->setType(Ogre::Light::LT_POINT);
    yz::PointLight* light = new yz::PointLight(base, this->sceneManager);
    light->setPosition(x, y, z);
    return light;
}

yz::SpotLight* yz::SceneManager::createSpotLight(
    const std::string& name,
    const Ogre::Real x,
    const Ogre::Real y,
    const Ogre::Real z,
    const Ogre::Real dirX,
    const Ogre::Real dirY,
    const Ogre::Real dirZ) {
    LOG_FUNCTION
    Ogre::Light* base = this->sceneManager->createLight(name);
    base->setType(Ogre::Light::LT_SPOTLIGHT);
    base->setSpotlightRange(Ogre::Degree(30), Ogre::Degree(60), 1.0);
    yz::SpotLight* light = new yz::SpotLight(base, this->sceneManager);
    light->setPosition(x, y, z);
    light->setDirection(dirX, dirY, dirZ);
    return light;
}

yz::DirectionalLight* yz::SceneManager::createDirectionalLight(
    const std::string& name,
    const Ogre::Real x,
    const Ogre::Real y,
    const Ogre::Real z,
    const Ogre::Real dirX,
    const Ogre::Real dirY,
    const Ogre::Real dirZ) {
    LOG_FUNCTION
    Ogre::Light* base = this->sceneManager->createLight(name);
    base->setType(Ogre::Light::LT_DIRECTIONAL);
    yz::DirectionalLight* light = new yz::DirectionalLight(base, this->sceneManager);
    light->setPosition(x, y, z);
    light->setDirection(dirX, dirY, dirZ);
    return light;
}

