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

#include "../includes/Camera.hpp"
#include "../includes/JniCamera.h"
#include "../includes/JniUtil.h"
#include "../includes/Lensflare.hpp"

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreCamera_setFarClip(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jint distance) {
    LOG_FUNCTION
    YZ::Camera::get(pointer)->setFarClipDistance(distance);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreCamera_setNearClip(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jint distance) {
    LOG_FUNCTION
    YZ::Camera::get(pointer)->setNearClipDistance(distance);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreCamera_enableRenderingDistance(
    JNIEnv* env,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    YZ::Camera::get(pointer)->enableRenderingDistance();
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreCamera_unregisterListener(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    POINTER lsPointer) {
    LOG_FUNCTION
    try {
        YZ::LensFlare* ls = YZ::LensFlare::get(lsPointer);
        YZ::Camera::get(pointer)->removeListener(ls);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreCamera_forceListenersUpdate(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    YZ::Camera::get(pointer)->forceListenersUpdate();
}

JNIEXPORT jfloatArray JNICALL Java_be_yildiz_module_graphic_ogre_OgreCamera_rotate(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jfloat x,
    jfloat y) {
    LOG_FUNCTION
    return vectorToArray(env, YZ::Camera::get(pointer)->rotate(x, y));
}

JNIEXPORT jfloatArray JNICALL Java_be_yildiz_module_graphic_ogre_OgreCamera_move(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jfloat x,
    jfloat y,
    jfloat z) {
    LOG_FUNCTION
    return vectorToArray(env, YZ::Camera::get(pointer)->move(x, y, z));
}

JNIEXPORT jfloatArray JNICALL Java_be_yildiz_module_graphic_ogre_OgreCamera_getDirection(
    JNIEnv* env,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    return vectorToArray(env, YZ::Camera::get(pointer)->getDirection());
}

JNIEXPORT jfloatArray JNICALL Java_be_yildiz_module_graphic_ogre_OgreCamera_setPositionAxis(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jfloat x,
    jfloat y,
    jint axis) {
    LOG_FUNCTION
    return vectorToArray(env, YZ::Camera::get(pointer)->setPositionAxis(x, y, axis));
}

JNIEXPORT jboolean JNICALL Java_be_yildiz_module_graphic_ogre_OgreCamera_isVisible(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat x,
    jfloat y,
    jfloat z) {
    LOG_FUNCTION
    return YZ::Camera::get(pointer)->isVisible(x, y, z);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreCamera_setPosition(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat x,
    jfloat y,
    jfloat z) {
    LOG_FUNCTION
    YZ::Camera::get(pointer)->setPosition(x, y, z);
}

JNIEXPORT jfloatArray JNICALL Java_be_yildiz_module_graphic_ogre_OgreCamera_lookAt(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jfloat x,
    jfloat y,
    jfloat z) {
    LOG_FUNCTION
    return vectorToArray(env, YZ::Camera::get(pointer)->lookAt(x, y, z));
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreCamera_setOrientation(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat x,
    jfloat y,
    jfloat z) {
    LOG_FUNCTION
    YZ::Camera::get(pointer)->setDirection(x, y, z);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreCamera_detachFromParent(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    YZ::Camera::get(pointer)->detachFromParent();
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreCamera_setAutotrack(
    JNIEnv *,
    jobject,
    POINTER pointer,
    POINTER nodePointer) {
    LOG_FUNCTION
    YZ::Camera::get(pointer)->track(YZ::Node::get(nodePointer));
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreCamera_stopAutotrack(
    JNIEnv *,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    YZ::Camera::get(pointer)->stopTrack();
}

JNIEXPORT jfloatArray JNICALL Java_be_yildiz_module_graphic_ogre_OgreCamera_computeMoveDestinationGroundIntersect(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jfloat x,
    jfloat y) {
    LOG_FUNCTION
    return vectorToArray(env, YZ::Camera::get(pointer)->throwRayPos(x, y));
}

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreCamera_throwRay(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jfloat x,
    jfloat y,
    jboolean poly) {
    LOG_FUNCTION
    return YZ::Camera::get(pointer)->throwRay(x, y, poly)->value();
}

JNIEXPORT jlongArray JNICALL Java_be_yildiz_module_graphic_ogre_OgreCamera_throwPlaneRay(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jfloat left,
    jfloat top,
    jfloat right,
    jfloat bottom) {
    LOG_FUNCTION
    YZ::Camera* cam = YZ::Camera::get(pointer);
    try {
        std::vector<YZ::Id*> list = cam->throwPlaneRay(left, right, top, bottom);

        if (list.empty()) {
            jlong buf[1];
            jlongArray result = env->NewLongArray(0);
            env->SetLongArrayRegion(result, 0, 0, buf);
            return result;
        }
        const int size = list.size();

        jlong* buf;
        buf = new jlong[size];
        for (int i = 0; i < size; i++) {
            buf[i] = list[i]->value();
        }
        jlongArray result = env->NewLongArray(size);
        env->SetLongArrayRegion(result, 0, size, buf);
        return result;
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
    return env->NewLongArray(1);
}
