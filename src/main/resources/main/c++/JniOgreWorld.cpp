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
 * @author Grégory Van den Borre
 */

#include "../includes/JniOgreWorld.h"
#include "../includes/SceneManager.hpp"
#include "../includes/Planet.hpp"
#include "../includes/RenderWindow.hpp"

JNIEXPORT void JNICALL Java_jni_JniSceneManager_setSkybox(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jstring jfile) {
    LOG_FUNCTION
    JniStringWrapper file = JniStringWrapper(env, jfile);
    reinterpret_cast<yz::SceneManager*>(pointer)->setSkyBox(file.getValue());
}

JNIEXPORT void JNICALL Java_jni_JniSceneManager_setShadowTechnique(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jint tec) {
    LOG_FUNCTION
    reinterpret_cast<yz::SceneManager*>(pointer)->setShadowType(tec);
}


JNIEXPORT void JNICALL Java_jni_JniSceneManager_setShadowTextureSize(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jint size) {
    LOG_FUNCTION
    reinterpret_cast<yz::SceneManager*>(pointer)->setShadowTextureSize(size);
}

JNIEXPORT void JNICALL Java_jni_JniSceneManager_setShadowFarDistance(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jint distance) {
    LOG_FUNCTION
    reinterpret_cast<yz::SceneManager*>(pointer)->setShadowFarDistance(distance);
}

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createLensFlare(
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
        yz::SceneManager* sm = reinterpret_cast<yz::SceneManager*>(pointer);
        yz::Camera* cam = reinterpret_cast<yz::Camera*>(camPointer);
        yz::Material* light = reinterpret_cast<yz::Material*>(lightPointer);
        yz::Material* streak = reinterpret_cast<yz::Material*>(streakPointer);
        yz::Material* halo = reinterpret_cast<yz::Material*>(haloPointer);
        yz::Material* burst = reinterpret_cast<yz::Material*>(burstPointer);
        yz::LensFlare* lens = sm->createLensFlare(name.getValue(), light, streak, halo, burst, x, y, z);
        cam->addListener(lens);
        return reinterpret_cast<POINTER>(lens);
    } catch (const std::exception& e) {
        throwException(env, e.what());
    }
    return INVALID_POINTER;
}

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createCamera(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jstring jname) {
    LOG_FUNCTION
    try {
        JniStringWrapper name = JniStringWrapper(env, jname);
        yz::SceneManager* sm = reinterpret_cast<yz::SceneManager*>(pointer);
        yz::Camera* camera = sm->createCamera(name.getValue());
        return reinterpret_cast<POINTER>(camera);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
    return INVALID_POINTER;
}

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createQuery(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    POINTER rayPointer) {
    try {
    LOG_FUNCTION
    yz::SceneManager* sm = reinterpret_cast<yz::SceneManager*>(pointer);
    yz::Query* query = sm->createQuery(reinterpret_cast<yz::RayProvider*>(rayPointer));
    return reinterpret_cast<POINTER>(query);
    } catch (const std::exception& e) {
        throwException(env, e.what());
    }
    return INVALID_POINTER;
}

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createDummyGround(
    JNIEnv* env,
    jobject o,
    POINTER pointer) {
        yz::SceneManager* sm = reinterpret_cast<yz::SceneManager*>(pointer);
        yz::Entity* e = sm->createCube("cam_ground");
        e->setQueryFlags(Ogre::SceneManager::WORLD_GEOMETRY_TYPE_MASK);
        yz::Node* node = sm->createNode("cam_ground_node");
        node->scale(2000, 0.02, 2000);
        node->attachObject(e);
        node->hide();
        return reinterpret_cast<POINTER>(node);
    }

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createGroundQuery(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    POINTER rayPointer,
    POINTER nodePointer) {
    try {
        LOG_FUNCTION
        yz::SceneManager* sm = reinterpret_cast<yz::SceneManager*>(pointer);
        yz::RayProvider* provider = reinterpret_cast<yz::RayProvider*>(rayPointer);
        yz::Node* node = reinterpret_cast<yz::Node*>(nodePointer);
        yz::GroundQuery* query = sm->createGroundQuery(provider, node);
        return reinterpret_cast<POINTER>(query);
    } catch (const std::exception& e) {
        throwException(env, e.what());
    }
    return INVALID_POINTER;

}

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createMeshEntity(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jstring jmesh,
    POINTER nodePointer) {
    LOG_FUNCTION
    JniStringWrapper mesh = JniStringWrapper(env, jmesh);
    yz::SceneManager* sm = reinterpret_cast<yz::SceneManager*>(pointer);
    yz::Entity* entity = sm->createEntity(mesh.getValue());
    yz::Node* node = reinterpret_cast<yz::Node*>(nodePointer);
    node->attachObject(entity);
    return reinterpret_cast<POINTER>(entity);
}

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createBoxEntity(
    JNIEnv*,
    jobject,
    POINTER pointer,
    POINTER nodePointer) {
    LOG_FUNCTION
    yz::SceneManager* sm = reinterpret_cast<yz::SceneManager*>(pointer);
    yz::Entity* entity = sm->createCube();
    yz::Node* node = reinterpret_cast<yz::Node*>(nodePointer);
    node->attachObject(entity);
    return reinterpret_cast<POINTER>(entity);
}

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createPlaneEntity(
    JNIEnv*,
    jobject,
    POINTER pointer,
    POINTER nodePointer) {
    LOG_FUNCTION
    yz::SceneManager* sm = reinterpret_cast<yz::SceneManager*>(pointer);
    yz::Entity* entity = sm->createPlane();
    yz::Node* node = reinterpret_cast<yz::Node*>(nodePointer);
    node->attachObject(entity);
    return reinterpret_cast<POINTER>(entity);
}

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createSphereEntity(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    POINTER nodePointer,
    jstring jname) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    yz::SceneManager* sm = reinterpret_cast<yz::SceneManager*>(pointer);
    yz::Node* node = reinterpret_cast<yz::Node*>(nodePointer);
    yz::Entity* entity = sm->createSphere(name.getValue(), 64, 64, 100); //sm->createSphere();
    node->attachObject(entity);
    return reinterpret_cast<POINTER>(entity);
}

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createNode(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jstring jname) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    yz::SceneManager* sm = reinterpret_cast<yz::SceneManager*>(pointer);
    try {
        yz::Node* node = sm->createNode(name.getValue());
        return reinterpret_cast<POINTER>(node);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
    return INVALID_POINTER;
}

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createNodeId(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    POINTER id,
    jstring jname) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    yz::SceneManager* sm = reinterpret_cast<yz::SceneManager*>(pointer);
    try {
        yz::Node* node = sm->createNode(new yz::Id(id), name.getValue());
        return reinterpret_cast<POINTER>(node);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
    return INVALID_POINTER;
}

JNIEXPORT void JNICALL Java_jni_JniSceneManager_setAmbientLight(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat red,
    jfloat green,
    jfloat blue,
    jfloat alpha) {
    LOG_FUNCTION
    reinterpret_cast<yz::SceneManager*>(pointer)->setAmbientLight(red, green, blue, alpha);
}

JNIEXPORT void JNICALL Java_jni_JniSceneManager_setShadowType(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jint type) {
    LOG_FUNCTION
    reinterpret_cast<yz::SceneManager*>(pointer)->setShadowType(type);
}

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createPointLight(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jstring jname,
    jfloat x,
    jfloat y,
    jfloat z) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    yz::SceneManager* sm = reinterpret_cast<yz::SceneManager*>(pointer);
    try {
        yz::PointLight* light = sm->createPointLight(name.getValue(), x, y, z);
        return reinterpret_cast<POINTER>(light);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
    return INVALID_POINTER;
}

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createSpotLight(
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
    yz::SceneManager* sm = reinterpret_cast<yz::SceneManager*>(pointer);
    try {
        yz::SpotLight* light = sm->createSpotLight(name.getValue(), x, y, z, tgtX, tgtY, tgtZ);
        return reinterpret_cast<POINTER>(light);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
    return INVALID_POINTER;
}

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createDirectionalLight(
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
    yz::SceneManager* sm = reinterpret_cast<yz::SceneManager*>(pointer);
    try {
        yz::DirectionalLight* light = sm->createDirectionalLight(name.getValue(), x, y, z, tgtX, tgtY, tgtZ);
        return reinterpret_cast<POINTER>(light);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
    return INVALID_POINTER;
}

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createElectricArc(
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
    yz::SceneManager* sm = reinterpret_cast<yz::SceneManager*>(pointer);
    yz::ElectricArc* arc = sm->createElectricArc(name.getValue(), x, y, z, eX, eY, eZ, width);
    return reinterpret_cast<POINTER>(arc);
}

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createParticleSystem(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    yz::SceneManager* sm = reinterpret_cast<yz::SceneManager*>(pointer);
    yz::ParticleSystem* system = sm->createParticleSystem();
    return reinterpret_cast<POINTER>(system);
}

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createBillboardSet(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    POINTER matPointer) {
    LOG_FUNCTION
    yz::SceneManager* sm = reinterpret_cast<yz::SceneManager*>(pointer);
    yz::Material* material = reinterpret_cast<yz::Material*>(matPointer);
    yz::BillboardSet* set = sm->createBillboardSet(material);
    return reinterpret_cast<POINTER>(set);
}

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_getRootNode(
    JNIEnv* env, jobject, POINTER pointer) {
    LOG_FUNCTION
    return reinterpret_cast<POINTER>(reinterpret_cast<yz::SceneManager*>(pointer)->getRootNode());
}

