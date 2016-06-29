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

/**
*@author Grégory Van den Borre
*/

#include "../includes/JniOgreWorld.h"
#include "../includes/SceneManager.hpp"
#include "../includes/ElectricArc.hpp"
#include "../includes/Planet.hpp"
#include "../includes/JniUtil.h"
#include "../includes/Node.hpp"
#include "../includes/DummyGroundCamListener.hpp"
#include "../includes/RenderWindow.hpp"

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_setSkybox(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jstring jfile) {
    LOG_FUNCTION
    JniStringWrapper file = JniStringWrapper(env, jfile);
    YZ::SceneManager::get(pointer)->setSkyBox(file.getValue());
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_setShadowTechnique(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jint tec) {
    LOG_FUNCTION
    YZ::SceneManager::get(pointer)->setShadowType(tec);
}


JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_setShadowTextureSize(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jint size) {
    LOG_FUNCTION
    YZ::SceneManager::get(pointer)->setShadowTextureSize(size);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_setShadowFarDistance(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jint distance) {
    LOG_FUNCTION
    YZ::SceneManager::get(pointer)->setShadowFarDistance(distance);
}

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createLensFlare(
    JNIEnv* env,
    jobject,
    jstring jname,
    POINTER pointer,
    POINTER camPointer,
    POINTER lightPointer,
    POINTER streakPointer,
    POINTER haloPointer,
    POINTER burstPointer,
    jfloat x,
    jfloat y,
    jfloat z) {
    LOG_FUNCTION
    try {
        JniStringWrapper name = JniStringWrapper(env, jname);
        YZ::SceneManager* sm = YZ::SceneManager::get(pointer);
        YZ::Camera* cam = YZ::Camera::get(camPointer);
        YZ::Material* light = YZ::Material::get(lightPointer);
        YZ::Material* streak = YZ::Material::get(streakPointer);
        YZ::Material* halo = YZ::Material::get(haloPointer);
        YZ::Material* burst = YZ::Material::get(burstPointer);
        YZ::LensFlare* lens = sm->createLensFlare(name.getValue(), light, streak, halo, burst, x, y, z);
        cam->addListener(lens);
        return reinterpret_cast<POINTER>(lens);
    } catch (const std::exception& e) {
        throwException(env, e.what());
    }
    return INVALID_POINTER;
}

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createCamera(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jstring jname) {
    LOG_FUNCTION
    try {
        JniStringWrapper name = JniStringWrapper(env, jname);
        YZ::SceneManager* sm = YZ::SceneManager::get(pointer);
        YZ::Camera* camera = sm->createCamera(name.getValue());
        YZ::Entity* e = sm->createCube(camera->getName() + "cam_ground");
        e->setQueryFlags(Ogre::SceneManager::WORLD_GEOMETRY_TYPE_MASK);
        YZ::Node* node = sm->createNode(camera->getName() + "cam_ground_node");
        node->scale(200, 0.02, 200);
        node->attachObject(e);
        node->hide();
        YZ::AbstractCameraListener* ls = new YZ::DummyGroundCamListener(node);
        camera->addListener(ls);
        return reinterpret_cast<POINTER>(camera);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
    return INVALID_POINTER;
}

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createMeshEntity(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jstring jmesh,
    POINTER nodePointer) {
    LOG_FUNCTION
    JniStringWrapper mesh = JniStringWrapper(env, jmesh);
    YZ::SceneManager* sm = YZ::SceneManager::get(pointer);
    YZ::Entity* entity = sm->createEntity(mesh.getValue());
    YZ::Node* node = YZ::Node::get(nodePointer);
    node->attachObject(entity);
    return reinterpret_cast<POINTER>(entity);
}

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createBoxEntity(
    JNIEnv*,
    jobject,
    POINTER pointer,
    POINTER nodePointer) {
    LOG_FUNCTION
    YZ::SceneManager* sm = YZ::SceneManager::get(pointer);
    YZ::Entity* entity = sm->createCube();
    YZ::Node* node = YZ::Node::get(nodePointer);
    node->attachObject(entity);
    return reinterpret_cast<POINTER>(entity);
}

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createPlaneEntity(
    JNIEnv*,
    jobject,
    POINTER pointer,
    POINTER nodePointer) {
    LOG_FUNCTION
    YZ::SceneManager* sm = YZ::SceneManager::get(pointer);
    YZ::Entity* entity = sm->createPlane();
    YZ::Node* node = YZ::Node::get(nodePointer);
    node->attachObject(entity);
    return reinterpret_cast<POINTER>(entity);
}

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createSphereEntity(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    POINTER nodePointer,
    jstring jname) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    YZ::SceneManager* sm = YZ::SceneManager::get(pointer);
    YZ::Node* node = YZ::Node::get(nodePointer);
    YZ::Entity* entity = sm->createSphere(name.getValue(), 64, 64, 100); //sm->createSphere();
    node->attachObject(entity);
    return reinterpret_cast<POINTER>(entity);
}

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createNode(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jstring jname) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    YZ::SceneManager* sm = YZ::SceneManager::get(pointer);
    try {
        YZ::Node* node = sm->createNode(name.getValue());
        return reinterpret_cast<POINTER>(node);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
    return INVALID_POINTER;
}

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createNodeId(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    POINTER id,
    jstring jname) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    YZ::SceneManager* sm = YZ::SceneManager::get(pointer);
    try {
        YZ::Node* node = sm->createNode(new YZ::Id(id), name.getValue());
        return reinterpret_cast<POINTER>(node);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
    return INVALID_POINTER;
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_setAmbientLight(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat red,
    jfloat green,
    jfloat blue,
    jfloat alpha) {
    LOG_FUNCTION
    YZ::SceneManager::get(pointer)->setAmbientLight(red, green, blue, alpha);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_setShadowType(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jint type) {
    LOG_FUNCTION
    YZ::SceneManager::get(pointer)->setShadowType(type);
}

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createPointLight(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jstring jname,
    jfloat x,
    jfloat y,
    jfloat z) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    YZ::SceneManager* sm = YZ::SceneManager::get(pointer);
    try {
        YZ::PointLight* light = sm->createPointLight(name.getValue(), x, y, z);
        return reinterpret_cast<POINTER>(light);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
    return INVALID_POINTER;
}

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createSpotLight(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jstring jname,
    jfloat x,
    jfloat y,
    jfloat z,
    jfloat tgtX,
    jfloat tgtY,
    jfloat tgtZ) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    YZ::SceneManager* sm = YZ::SceneManager::get(pointer);
    try {
        YZ::SpotLight* light = sm->createSpotLight(name.getValue(), x, y, z, tgtX, tgtY, tgtZ);
        return reinterpret_cast<POINTER>(light);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
    return INVALID_POINTER;
}

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createDirectionalLight(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jstring jname,
    jfloat x,
    jfloat y,
    jfloat z,
    jfloat tgtX,
    jfloat tgtY,
    jfloat tgtZ) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    YZ::SceneManager* sm = YZ::SceneManager::get(pointer);
    try {
        YZ::DirectionalLight* light = sm->createDirectionalLight(name.getValue(), x, y, z, tgtX, tgtY, tgtZ);
        return reinterpret_cast<POINTER>(light);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
    return INVALID_POINTER;
}

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createElectricArc(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jstring jname,
    jfloat x,
    jfloat y,
    jfloat z,
    jfloat eX,
    jfloat eY,
    jfloat eZ,
    jfloat width) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    YZ::SceneManager* sm = YZ::SceneManager::get(pointer);
    YZ::ElectricArc* arc = sm->createElectricArc(name.getValue(), x, y, z, eX, eY, eZ, width);
    return reinterpret_cast<POINTER>(arc);
}

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createParticleSystem(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    YZ::SceneManager* sm = YZ::SceneManager::get(pointer);
    YZ::ParticleSystem* system = sm->createParticleSystem();
    return reinterpret_cast<POINTER>(system);
}

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createBillboardSet(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    POINTER matPointer) {
    LOG_FUNCTION
    YZ::SceneManager* sm = YZ::SceneManager::get(pointer);
    YZ::Material* material = YZ::Material::get(matPointer);
    YZ::BillboardSet* set = sm->createBillboardSet(material);
    return reinterpret_cast<POINTER>(set);
}

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_getRootNode(
    JNIEnv* env, jobject, POINTER pointer) {
    LOG_FUNCTION
    return reinterpret_cast<POINTER>(YZ::SceneManager::get(pointer)->getRootNode());
}

