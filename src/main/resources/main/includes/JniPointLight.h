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

#include "JniUtil.h"

#ifndef JNI_POINT_LIGHT_H
#define JNI_POINT_LIGHT_H

/**
*@author Grégory Van den Borre
*/
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Enable the debug render.
 * @param pointer yz::PointLight pointer address.
 */
JNIEXPORT void JNICALL Java_jni_JniPointLight_setDebug(
    JNIEnv* env,
    jobject o,
    POINTER pointer);

JNIEXPORT void JNICALL Java_jni_JniPointLight_setPosition(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jfloat x,
    jfloat y,
    jfloat z);

JNIEXPORT void JNICALL Java_jni_JniPointLight_setColor(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jfloat r,
    jfloat g,
    jfloat b);

JNIEXPORT void JNICALL Java_jni_JniPointLight_setAttenuation(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jfloat range,
    jfloat constant,
    jfloat linear,
    jfloat quadratic);

JNIEXPORT void JNICALL Java_jni_JniPointLight_delete(
    JNIEnv* env,
    jobject o,
    POINTER pointer);

#ifdef __cplusplus
}
#endif

#endif
