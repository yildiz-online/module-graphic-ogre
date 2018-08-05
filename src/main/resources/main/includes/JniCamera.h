/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 * Copyright (c) 2018 Grégory Van den Borre
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

#include <jni.h>
#include "stdafx.h"

#ifndef JNI_CAMERA_H
#define JNI_CAMERA_H

/**
* @author Grégory Van den Borre
*/
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_jni_JniCamera_attachToNode(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    POINTER nodePointer);

JNIEXPORT void JNICALL Java_jni_JniCamera_setFarClip(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jint distance);

JNIEXPORT void JNICALL Java_jni_JniCamera_setAspectRatio(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jfloat ratio);


JNIEXPORT void JNICALL Java_jni_JniCamera_setNearClip(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jint distance);

JNIEXPORT void JNICALL Java_jni_JniCamera_enableRenderingDistance(
    JNIEnv* env,
    jobject o,
    POINTER pointer);

JNIEXPORT void JNICALL Java_jni_JniCamera_unregisterListener(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    POINTER lsPointer);

JNIEXPORT void JNICALL Java_jni_JniCamera_forceListenersUpdate(
    JNIEnv* env,
    jobject o,
    POINTER pointer);

JNIEXPORT jfloatArray JNICALL Java_jni_JniCamera_move(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jfloat x,
    jfloat y,
    jfloat z);
JNIEXPORT jfloatArray JNICALL Java_jni_JniCamera_lookAt(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jfloat x,
    jfloat y,
    jfloat z);
JNIEXPORT jboolean JNICALL Java_jni_JniCamera_isVisible(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jfloat x,
    jfloat y,
    jfloat z);
JNIEXPORT jfloatArray JNICALL Java_jni_JniCamera_getDirection(
    JNIEnv* env,
    jobject o,
    POINTER pointer);
JNIEXPORT jfloatArray JNICALL Java_jni_JniCamera_setPositionAxis(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jfloat x,
    jfloat y,
    jint axis);

JNIEXPORT void JNICALL Java_jni_JniCamera_setPosition(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jfloat x,
    jfloat y,
    jfloat z);

JNIEXPORT void JNICALL Java_jni_JniCamera_setOrientation(
    JNIEnv *,
    jobject,
    POINTER,
    jfloat,
    jfloat,
    jfloat);

JNIEXPORT void JNICALL Java_jni_JniCamera_detachFromParent(
    JNIEnv *,
    jobject,
    POINTER);

JNIEXPORT void JNICALL Java_jni_JniCamera_setAutotrack(
    JNIEnv *,
    jobject,
    POINTER,
    POINTER);

JNIEXPORT void JNICALL Java_jni_JniCamera_stopAutotrack(
    JNIEnv *,
    jobject,
    POINTER);

JNIEXPORT POINTER JNICALL Java_jni_JniCamera_throwRay(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jfloat x,
    jfloat y,
    jboolean poly);

JNIEXPORT jlongArray JNICALL Java_jni_JniCamera_throwPlaneRay(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jfloat left,
    jfloat top,
    jfloat right,
    jfloat bottom);

JNIEXPORT jfloatArray JNICALL Java_jni_JniCamera_computeMoveDestinationGroundIntersect(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jfloat x,
    jfloat y);

#ifdef __cplusplus
}
#endif
#endif
