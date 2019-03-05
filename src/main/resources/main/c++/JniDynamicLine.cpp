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

#include "../includes/stdafx.h"
#include "../includes/JniDynamicLine.h"
#include "../includes/DynamicLine.hpp"

JNIEXPORT POINTER JNICALL Java_jni_JniDynamicLine_constructor(
    JNIEnv*,
    jobject,
    POINTER nodePointer) {
    LOG_FUNCTION
    yz::Node* node = yz::Node::get(nodePointer);
    DynamicLines* line  = new DynamicLines(node);
    return reinterpret_cast<POINTER>(line);
}

JNIEXPORT void JNICALL Java_jni_JniDynamicLine_setMaterial(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    POINTER matPointer) {
    LOG_FUNCTION
    DynamicLines* line = DynamicLines::get(pointer);
    yz::Material* material = yz::Material::get(matPointer);
    line->setMaterial(material);
}

JNIEXPORT void JNICALL Java_jni_JniDynamicLine_show(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    DynamicLines::get(pointer)->show();
}

JNIEXPORT void JNICALL Java_jni_JniDynamicLine_hide(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    DynamicLines::get(pointer)->hide();
}

JNIEXPORT void JNICALL Java_jni_JniDynamicLine_update(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat beginX,
    jfloat beginY,
    jfloat beginZ,
    jfloat endX,
    jfloat endY,
    jfloat endZ) {
    LOG_FUNCTION
    DynamicLines* line = DynamicLines::get(pointer);
    line->setPoint(0, beginX, beginY, beginZ);
    line->setPoint(1, endX, endY, endZ);
    line->update();
}
