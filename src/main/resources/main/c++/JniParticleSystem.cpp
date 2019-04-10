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

#include "../includes/JniParticleSystem.h"
#include "../includes/ParticleSystem.hpp"
#include "../includes/EnumConversion.h"

JNIEXPORT void JNICALL Java_jni_JniParticleSystem_attachToNode(
    JNIEnv*,
    jobject,
    POINTER pointer,
    POINTER nodePointer) {
    LOG_FUNCTION
    yz::ParticleSystem* system = reinterpret_cast<yz::ParticleSystem*>(pointer);
    yz::Node* node = reinterpret_cast<yz::Node*>(nodePointer);
    node->attachObject(system);
}

JNIEXPORT void JNICALL Java_jni_JniParticleSystem_keepInLocalSpace(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jboolean keep) {
    LOG_FUNCTION
    reinterpret_cast<yz::ParticleSystem*>(pointer)->keepInLocalSpace(keep);
}

JNIEXPORT void JNICALL Java_jni_JniParticleSystem_setParticleOrientation(
    JNIEnv *,
    jobject,
    POINTER pointer,
    jint type) {
    LOG_FUNCTION
    reinterpret_cast<yz::ParticleSystem*>(pointer)->setParticleOrientation(EnumConversion::getBillboardType(type));
}

JNIEXPORT POINTER JNICALL Java_jni_JniParticleSystem_createEmitter(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    return reinterpret_cast<POINTER>(reinterpret_cast<yz::ParticleSystem*>(pointer)->createEmitter());
}

JNIEXPORT void JNICALL Java_jni_JniParticleSystem_setBillboardOrigin(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jint origin) {
    LOG_FUNCTION
    reinterpret_cast<yz::ParticleSystem*>(pointer)->setParticleBillboardOrigin(EnumConversion::getBillboardOrigin(origin));
}


JNIEXPORT POINTER JNICALL Java_jni_JniParticleSystem_createColorAffector(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    return reinterpret_cast<POINTER>(reinterpret_cast<yz::ParticleSystem*>(pointer)->createColorAffector());
}

JNIEXPORT POINTER JNICALL Java_jni_JniParticleSystem_createForceAffector(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    return reinterpret_cast<POINTER>(reinterpret_cast<yz::ParticleSystem*>(pointer)->createForceAffector());
}

JNIEXPORT POINTER JNICALL Java_jni_JniParticleSystem_createScaleAffector(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    return reinterpret_cast<POINTER>(reinterpret_cast<yz::ParticleSystem*>(pointer)->createScaleAffector());
}

JNIEXPORT void JNICALL Java_jni_JniParticleSystem_setSize(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat width,
    jfloat height) {
    LOG_FUNCTION
    reinterpret_cast<yz::ParticleSystem*>(pointer)->setDefaultDimensions(width, height);
}

JNIEXPORT void JNICALL Java_jni_JniParticleSystem_setMaterial(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    POINTER matPointer) {
    LOG_FUNCTION
    yz::ParticleSystem* system = reinterpret_cast<yz::ParticleSystem*>(pointer);
    yz::Material* material = reinterpret_cast<yz::Material*>(matPointer);
    system->setMaterial(material);
}

JNIEXPORT void JNICALL Java_jni_JniParticleSystem_setQuota(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jint quota) {
    LOG_FUNCTION
    reinterpret_cast<yz::ParticleSystem*>(pointer)->setParticleQuota(quota);
}

JNIEXPORT void JNICALL Java_jni_JniParticleSystem_show(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    reinterpret_cast<yz::ParticleSystem*>(pointer)->show();
}

JNIEXPORT void JNICALL Java_jni_JniParticleSystem_hide(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    reinterpret_cast<yz::ParticleSystem*>(pointer)->hide();
}
