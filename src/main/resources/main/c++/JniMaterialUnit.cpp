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

#include "../includes/JniMaterialUnit.h"
#include "../includes/MaterialUnit.hpp"
#include "../includes/EnumConversion.h"

JNIEXPORT void JNICALL Java_jni_JniTextureUnit_setTextureAnimated(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jstring jname,
    jint frame,
    jint duration) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    reinterpret_cast<Ogre::TextureUnitState*>(pointer)->setAnimatedTextureName(name.getValue(), frame, duration);
}

JNIEXPORT void JNICALL Java_jni_JniTextureUnit_setTextureFilter(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jint filter) {
    LOG_FUNCTION
    reinterpret_cast<Ogre::TextureUnitState*>(pointer)->setTextureFiltering(EnumConversion::getTextureFilter(filter));
}

JNIEXPORT void JNICALL Java_jni_JniTextureUnit_setCoordinateSet(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jint set) {
    LOG_FUNCTION
    reinterpret_cast<Ogre::TextureUnitState*>(pointer)->setTextureCoordSet (set);
}

JNIEXPORT void JNICALL Java_jni_JniTextureUnit_setColorOperation(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jint operation) {
    LOG_FUNCTION
    reinterpret_cast<Ogre::TextureUnitState*>(pointer)->setColourOperation(EnumConversion::getLayerBlendOperation(operation));
}

JNIEXPORT void JNICALL Java_jni_JniTextureUnit_scroll(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jfloat x,
    jfloat y) {
    LOG_FUNCTION
    reinterpret_cast<Ogre::TextureUnitState*>(pointer)->setScrollAnimation(x, y);
}

JNIEXPORT void JNICALL Java_jni_JniTextureUnit_setAlphaOperation(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jint operation,
    jint src,
    jint src2) {
    LOG_FUNCTION
    reinterpret_cast<Ogre::TextureUnitState*>(pointer)->setAlphaOperation(
            EnumConversion::getLayerBlendOperationEx(operation),
            EnumConversion::getLayerBlendSource(src),
            EnumConversion::getLayerBlendSource(src2));
}

JNIEXPORT void JNICALL Java_jni_JniTextureUnit_setColorOperationEx(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jint operation,
    jint src,
    jint src2) {
    LOG_FUNCTION
    reinterpret_cast<Ogre::TextureUnitState*>(pointer)->setColourOperationEx(
            EnumConversion::getLayerBlendOperationEx(operation),
            EnumConversion::getLayerBlendSource(src),
            EnumConversion::getLayerBlendSource(src2));
}

JNIEXPORT void JNICALL Java_jni_JniTextureUnit_setColorOperationExManual(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jint operation,
    jint src,
    jint src2,
    jfloat r,
    jfloat g,
    jfloat b) {
    LOG_FUNCTION
    reinterpret_cast<Ogre::TextureUnitState*>(pointer)->setColourOperationEx(
            EnumConversion::getLayerBlendOperationEx(operation),
            EnumConversion::getLayerBlendSource(src),
            EnumConversion::getLayerBlendSource(src2),
            Ogre::ColourValue(r, g, b));
}

JNIEXPORT void JNICALL Java_jni_JniTextureUnit_setTexture(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jstring materialName) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, materialName);
    reinterpret_cast<Ogre::TextureUnitState*>(pointer)->setTextureName(name.getValue());
}

JNIEXPORT void JNICALL Java_jni_JniTextureUnit_setScale(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat x,
    jfloat y) {
    LOG_FUNCTION
    reinterpret_cast<Ogre::TextureUnitState*>(pointer)->setTextureScale(x, y);
}
