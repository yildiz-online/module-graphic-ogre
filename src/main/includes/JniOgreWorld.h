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

#include <jni.h>
#include "stdafx.h"

#ifndef _JNI_OGRE_WORLD_H_
#define _JNI_OGRE_WORLD_H_

/**
*@author Grégory Van den Borre
*/
#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createLensFlare(
    JNIEnv* env,
    jobject,
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

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_setShadowTextureSize(
    JNIEnv* env,
    jobject,
    POINTER smPointer,
    jint size);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_setShadowFarDistance(
    JNIEnv* env,
    jobject,
    POINTER smPointer,
    jint distance);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_setSkybox(
    JNIEnv *,
    jobject,
    POINTER,
    jstring);
JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createCamera(
    JNIEnv *,
    jobject,
    POINTER,
    jstring);
JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createMeshEntity(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jstring mesh,
    POINTER);
JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createBoxEntity(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    POINTER jnode);
JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createSphereEntity(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    POINTER jnode,
    jstring jname);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_setShadowTechnique(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jint tec);

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createPlaneEntity(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    POINTER jnode);

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createNode(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jstring);
JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createNodeId(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    POINTER id,
    jstring);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_setAmbientLight(
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
JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createPointLight(
    JNIEnv *,
    jobject,
    POINTER,
    jstring,
    jfloat,
    jfloat,
    jfloat);
JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createSpotLight(
    JNIEnv *env,
    jobject o,
    POINTER smPointer,
    jstring jname,
    jfloat x,
    jfloat y,
    jfloat z,
    jfloat tgtX,
    jfloat tgtY,
    jfloat tgtZ);

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createDirectionalLight(
    JNIEnv *env,
    jobject o,
    POINTER smPointer,
    jstring jname,
    jfloat x,
    jfloat y,
    jfloat z,
    jfloat tgtX,
    jfloat tgtY,
    jfloat tgtZ);

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createElectricArc(
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

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createParticleSystem(
    JNIEnv *env,
    jobject o,
    POINTER smPointer);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_setShadowType(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jint type);

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_createBillboardSet(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    POINTER mat);
JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSceneManager_getRootNode(
    JNIEnv* env,
    jobject,
    POINTER pointer);

#ifdef __cplusplus
}
#endif
#endif
