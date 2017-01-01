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

#include "../includes/JniMaterialTechnique.h"
#include "../includes/MaterialTechnique.hpp"
#include "../includes/EnumConversion.h"
#include "../includes/JniUtil.h"

JNIEXPORT jlongArray JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialTechnique_getPassList(
    JNIEnv* env,
    jclass,
    POINTER pointer) {
    LOG_FUNCTION
    Ogre::Technique* technique = YZ::MaterialTechnique::get(pointer);
    int size = technique->getNumPasses();
    jlong* buf;
    buf = new jlong[size];
    for (int i = 0; i < size; i++) {
        buf[i] = reinterpret_cast<jlong>(technique->getPass(i));
    }
    jlongArray result = env->NewLongArray(size);
    env->SetLongArrayRegion(result, 0, size, buf);
    return result;
}

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialTechnique_createPass(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    Ogre::Technique* technique = YZ::MaterialTechnique::get(pointer);
    return reinterpret_cast<POINTER>(technique->createPass());
}

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialTechnique_getPass(
    JNIEnv* env,
    jclass c,
    POINTER pointer,
    jint index) {
    LOG_FUNCTION
    return reinterpret_cast<jlong>(YZ::MaterialTechnique::get(pointer)->getPass(
            index));
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialTechnique_setGlow(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    YZ::MaterialTechnique::get(pointer)->setSchemeName("glow");
}

