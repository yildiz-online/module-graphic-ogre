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

#include <jni.h>
#include "stdafx.h"

#ifndef JNI_OGRE_MATERIAL_H
#define JNI_OGRE_MATERIAL_H

/**
*@author Grégory Van den Borre
*/
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterial_copy(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jstring materialName);

JNIEXPORT jlongArray JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterial_getTechniqueList(
    JNIEnv* env,
    jclass c,
    POINTER materialPointer);

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterial_getTechnique(
    JNIEnv* env,
    jobject o,
    POINTER materialPointer,
    jint number);

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterial_createTexture(
    JNIEnv* env,
    jobject o,
    jstring name);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterial_loadTexture(
    JNIEnv* env,
    jobject o,
    POINTER pointer);

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterial_createTechnique(
    JNIEnv* env,
    jobject o,
    POINTER pointer);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterial_receiveShadow(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jboolean b);

#ifdef __cplusplus
}
#endif

#endif // TEXTURE_H
