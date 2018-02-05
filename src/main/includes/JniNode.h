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

#ifndef JNI_NODE_H
#define JNI_NODE_H

/**
*@author Grégory Van den Borre
*/
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL Java_jni_OgreNodeNative_getName(JNIEnv* env, jobject o, POINTER pointer);

JNIEXPORT void JNICALL Java_jni_OgreNodeNative_show(JNIEnv* env, jobject o, POINTER pointer);

JNIEXPORT void JNICALL Java_jni_OgreNodeNative_hide(JNIEnv* env, jobject o, POINTER pointer);

JNIEXPORT jfloatArray JNICALL Java_jni_OgreNodeNative_getPosition(JNIEnv* env, jobject o, POINTER pointer);

JNIEXPORT void JNICALL Java_jni_OgreNodeNative_setPosition(
    JNIEnv* env, jobject o, POINTER pointer, jfloat x, jfloat y, jfloat z);

JNIEXPORT jfloatArray JNICALL Java_jni_OgreNodeNative_getDirection(JNIEnv* env, jobject o, POINTER pointer);

JNIEXPORT void JNICALL Java_jni_OgreNodeNative_setDirection(
    JNIEnv* env, jobject o, POINTER pointer, jfloat x, jfloat y, jfloat z);

JNIEXPORT jfloatArray JNICALL Java_jni_OgreNodeNative_getOrientation(JNIEnv* env, jobject o, POINTER pointer);

JNIEXPORT jfloatArray JNICALL Java_jni_OgreNodeNative_translate(
    JNIEnv* env, jobject o, POINTER pointer, jfloat x, jfloat y, jfloat z);

JNIEXPORT jfloatArray JNICALL Java_jni_OgreNodeNative_rotate(
    JNIEnv* env, jobject o, POINTER pointer, jfloat x, jfloat y);

JNIEXPORT void JNICALL Java_jni_OgreNodeNative_rotateQuaternion(
    JNIEnv* env, jobject o, POINTER pointer, jfloat x, jfloat y, jfloat z, jfloat w);

JNIEXPORT void JNICALL Java_jni_OgreNodeNative_scale(
    JNIEnv* env, jobject o, POINTER pointer, jfloat scaleX, jfloat scaleY, jfloat scaleZ);

JNIEXPORT void JNICALL Java_jni_OgreNodeNative_attachToNode(
    JNIEnv* env, jobject o, POINTER pointer, POINTER other);

JNIEXPORT void JNICALL Java_jni_OgreNodeNative_attachTo(
    JNIEnv* env, jobject o, POINTER pointer, POINTER other);

JNIEXPORT void JNICALL Java_jni_OgreNodeNative_detachFromParentNode(
    JNIEnv* env, jobject o, POINTER pointer);

JNIEXPORT void JNICALL Java_jni_OgreNodeNative_detachFromParent(
    JNIEnv* env, jobject o, POINTER pointer, POINTER parent);

JNIEXPORT void JNICALL Java_jni_OgreNodeNative_delete(JNIEnv* env, jobject o, POINTER pointer);


#ifdef __cplusplus
}
#endif

#endif
