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

#include "../includes/JniBillboardChain.h"
#include "../includes/Node.hpp"
#include "../includes/BillboardChain.hpp"

JNIEXPORT POINTER JNICALL Java_jni_JniBillboardChain_constructor(
    JNIEnv* env,
    jobject,
    jstring jname,
    POINTER nodePointer) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    yz::BillboardChain* chain = new yz::BillboardChain(name.getValue());
    yz::Node* node = reinterpret_cast<yz::Node*>(nodePointer);
    node->attachObject(chain);
    return reinterpret_cast<POINTER>(chain);
}

JNIEXPORT void JNICALL Java_jni_JniBillboardChain_delete(
    JNIEnv* env,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    delete reinterpret_cast<yz::BillboardChain*>(pointer);
}

JNIEXPORT void JNICALL Java_jni_JniBillboardChain_setMaterial(
    JNIEnv*,
    jobject,
    POINTER pointer,
    POINTER matPointer) {
    LOG_FUNCTION
    reinterpret_cast<yz::BillboardChain*>(pointer)->setMaterial(reinterpret_cast<yz::Material*>(matPointer));
}

JNIEXPORT void JNICALL Java_jni_JniBillboardChain_ddElement(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat x,
    jfloat y,
    jfloat z,
    jfloat width) {
    LOG_FUNCTION
    reinterpret_cast<yz::BillboardChain*>(pointer)->addElement(x, y, z, width);
}

JNIEXPORT void JNICALL Java_jni_JniBillboardChain_setElementPosition(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jint element,
    jfloat x,
    jfloat y,
    jfloat z) {
    LOG_FUNCTION
    reinterpret_cast<yz::BillboardChain*>(pointer)->setElementPosition(element, x, y, z);
}
