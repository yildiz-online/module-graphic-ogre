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

#include "../includes/JniMaterialUnit.h"
#include "../includes/MaterialUnit.hpp"
#include "../includes/EnumConversion.h"
#include "../includes/JniUtil.h"

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreTextureUnit_setTextureAnimated(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jstring jname,
    jint frame,
    jint duration) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    YZ::TextureUnit::get(pointer)->setAnimatedTextureName(name.getValue(), frame, duration);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreTextureUnit_setTextureFilter(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jint filter) {
    LOG_FUNCTION
    YZ::TextureUnit::get(pointer)->setTextureFiltering(EnumConversion::getTextureFilter(filter));
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreTextureUnit_setCoordinateSet(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jint set) {
    LOG_FUNCTION
    YZ::TextureUnit::get(pointer)->setTextureCoordSet (set);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreTextureUnit_setColorOperation(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jint operation) {
    LOG_FUNCTION
    YZ::TextureUnit::get(pointer)->setColourOperation(EnumConversion::getLayerBlendOperation(operation));
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreTextureUnit_scroll(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jfloat x,
    jfloat y) {
    LOG_FUNCTION
    YZ::TextureUnit::get(pointer)->setScrollAnimation(x, y);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreTextureUnit_setAlphaOperation(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jint operation,
    jint src,
    jint src2) {
    LOG_FUNCTION
    YZ::TextureUnit::get(pointer)->setAlphaOperation(
            EnumConversion::getLayerBlendOperationEx(operation),
            EnumConversion::getLayerBlendSource(src),
            EnumConversion::getLayerBlendSource(src2));
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreTextureUnit_setColorOperationEx(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jint operation,
    jint src,
    jint src2) {
    LOG_FUNCTION
    YZ::TextureUnit::get(pointer)->setColourOperationEx(
            EnumConversion::getLayerBlendOperationEx(operation),
            EnumConversion::getLayerBlendSource(src),
            EnumConversion::getLayerBlendSource(src2));
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreTextureUnit_setColorOperationExManual(
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
    YZ::TextureUnit::get(pointer)->setColourOperationEx(
            EnumConversion::getLayerBlendOperationEx(operation),
            EnumConversion::getLayerBlendSource(src),
            EnumConversion::getLayerBlendSource(src2),
            Ogre::ColourValue(r, g, b));
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreTextureUnit_setTexture(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jstring materialName) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, materialName);
    YZ::TextureUnit::get(pointer)->setTextureName(name.getValue());
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreTextureUnit_setScale(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat x,
    jfloat y) {
    LOG_FUNCTION
    YZ::TextureUnit::get(pointer)->setTextureScale(x, y);
}
