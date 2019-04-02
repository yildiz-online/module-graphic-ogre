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

#include <jni.h>
#include "stdafx.h"

#ifndef JNI_OGRE_WORLD_H
#define JNI_OGRE_WORLD_H

/**
 *@author Grégory Van den Borre
 */

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createLensFlare(
    JNIEnv* env,
    jobject o,
    jstring name,
    POINTER pointer,
    POINTER cameraPointer,
    POINTER jlight,
    POINTER jstreak,
    POINTER jhalo,
    POINTER jburst,
    jfloat x,
    jfloat y,
    jfloat z);

JNIEXPORT void JNICALL Java_jni_JniSceneManager_setShadowTextureSize(
    JNIEnv* env,
    jobject o,
    POINTER smPointer,
    jint size);

JNIEXPORT void JNICALL Java_jni_JniSceneManager_setShadowFarDistance(
    JNIEnv* env,
    jobject o,
    POINTER smPointer,
    jint distance);

JNIEXPORT void JNICALL Java_jni_JniSceneManager_setSkybox(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jstring name);
JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createCamera(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jstring name);

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createQuery(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    POINTER rayProvider);

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createGroundQuery(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    POINTER rayProvider,
    POINTER nodePointer);

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createDummyGround(
    JNIEnv* env,
    jobject o,
    POINTER pointer);

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createMeshEntity(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jstring mesh,
    POINTER);
JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createBoxEntity(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    POINTER jnode);
JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createSphereEntity(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    POINTER jnode,
    jstring jname);

JNIEXPORT void JNICALL Java_jni_JniSceneManager_setShadowTechnique(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jint tec);

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createPlaneEntity(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    POINTER jnode);

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createNode(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jstring);
JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createNodeId(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    POINTER id,
    jstring);

JNIEXPORT void JNICALL Java_jni_JniSceneManager_setAmbientLight(
    JNIEnv *env,
    jobject o,
    POINTER pointer,
    jfloat red,
    jfloat green,
    jfloat blue,
    jfloat alpha);
///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// LIGHTS /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createPointLight(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jstring,
    jfloat,
    jfloat,
    jfloat);
JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createSpotLight(
    JNIEnv* env,
    jobject o,
    POINTER smPointer,
    jstring jname,
    jfloat x,
    jfloat y,
    jfloat z,
    jfloat tgtX,
    jfloat tgtY,
    jfloat tgtZ);

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createDirectionalLight(
    JNIEnv* env,
    jobject o,
    POINTER smPointer,
    jstring jname,
    jfloat x,
    jfloat y,
    jfloat z,
    jfloat tgtX,
    jfloat tgtY,
    jfloat tgtZ);

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createElectricArc(
    JNIEnv *env,
    jobject o,
    POINTER smPointer,
    jstring name,
    jfloat x,
    jfloat y,
    jfloat z,
    jfloat eX,
    jfloat eY,
    jfloat eZ,
    jfloat width);

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createParticleSystem(
    JNIEnv* env,
    jobject o,
    POINTER smPointer);

JNIEXPORT void JNICALL Java_jni_JniSceneManager_setShadowType(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jint type);

JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_createBillboardSet(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    POINTER mat);
JNIEXPORT POINTER JNICALL Java_jni_JniSceneManager_getRootNode(
    JNIEnv* env,
    jobject o,
    POINTER pointer);

#ifdef __cplusplus
}
#endif
#endif
