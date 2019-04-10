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

#include "../includes/Camera.hpp"
#include "../includes/JniCamera.h"
#include "../includes/Lensflare.hpp"

JNIEXPORT void JNICALL Java_jni_JniCamera_attachToNode(JNIEnv* env, jobject o, POINTER pointer, POINTER nodePointer) {
    LOG_FUNCTION
    yz::Camera* camera = reinterpret_cast<yz::Camera*>(pointer);
    yz::Node* node = reinterpret_cast<yz::Node*>(nodePointer);
    node->attachObject(camera);
}

JNIEXPORT void JNICALL Java_jni_JniCamera_setFarClip(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jint distance) {
    LOG_FUNCTION
    reinterpret_cast<yz::Camera*>(pointer)->setFarClipDistance(distance);
}

JNIEXPORT void JNICALL Java_jni_JniCamera_setNearClip(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jint distance) {
    LOG_FUNCTION
    reinterpret_cast<yz::Camera*>(pointer)->setNearClipDistance(distance);
}

JNIEXPORT void JNICALL Java_jni_JniCamera_setAspectRatio(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jfloat ratio) {
    LOG_FUNCTION
    reinterpret_cast<yz::Camera*>(pointer)->setAspectRatio(ratio);
    }

JNIEXPORT void JNICALL Java_jni_JniCamera_enableRenderingDistance(
    JNIEnv* env,
    jobject o,
    POINTER pointer) {
    LOG_FUNCTION
    reinterpret_cast<yz::Camera*>(pointer)->enableRenderingDistance();
}

JNIEXPORT void JNICALL Java_jni_JniCamera_unregisterListener(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    POINTER lsPointer) {
    LOG_FUNCTION
    try {
        yz::LensFlare* ls = reinterpret_cast<yz::LensFlare*>(lsPointer);
        reinterpret_cast<yz::Camera*>(pointer)->removeListener(ls);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT void JNICALL Java_jni_JniCamera_forceListenersUpdate(
    JNIEnv* env,
    jobject o,
    POINTER pointer) {
    LOG_FUNCTION
    reinterpret_cast<yz::Camera*>(pointer)->forceListenersUpdate();
}

JNIEXPORT jboolean JNICALL Java_jni_JniCamera_isVisible(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jfloat x,
    jfloat y,
    jfloat z) {
    LOG_FUNCTION
    return reinterpret_cast<yz::Camera*>(pointer)->isVisible(x, y, z);
}

JNIEXPORT void JNICALL Java_jni_JniCamera_detachFromParent(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    reinterpret_cast<yz::Camera*>(pointer)->detachFromParent();
}

