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
#include "../includes/JniNode.h"
#include "../includes/JniUtil.h"
#include "../includes/Node.hpp"

JNIEXPORT jstring JNICALL Java_jni_JniNode_getName(JNIEnv* env, jobject o, POINTER pointer) {
    LOG_FUNCTION
    return env->NewStringUTF(yz::Node::get(pointer)->getName().c_str());
}

JNIEXPORT void JNICALL Java_jni_JniNode_show(JNIEnv* env, jobject o, POINTER pointer) {
    LOG_FUNCTION
    yz::Node::get(pointer)->show();
}

JNIEXPORT void JNICALL Java_jni_JniNode_hide(JNIEnv* env, jobject o, POINTER pointer) {
    LOG_FUNCTION
    yz::Node::get(pointer)->hide();
}

JNIEXPORT jfloatArray JNICALL Java_jni_JniNode_getPosition(JNIEnv* env, jobject o, POINTER pointer) {
    LOG_FUNCTION
    return vectorToArray(env, yz::Node::get(pointer)->getPosition());
}

JNIEXPORT void JNICALL Java_jni_JniNode_setPosition(
    JNIEnv* env, jobject o, POINTER pointer, jfloat x, jfloat y, jfloat z) {
    LOG_FUNCTION
    yz::Node::get(pointer)->setPosition(x, y, z);
}

JNIEXPORT jfloatArray JNICALL Java_jni_JniNode_getDirection(JNIEnv* env, jobject o, POINTER pointer) {
    LOG_FUNCTION
    return vectorToArray(env, yz::Node::get(pointer)->getDirection());
}

JNIEXPORT void JNICALL Java_jni_JniNode_setDirection(
    JNIEnv* env, jobject o, POINTER pointer, jfloat x, jfloat y, jfloat z) {
    LOG_FUNCTION
    yz::Node::get(pointer)->setDirection(x, y, z);
}

JNIEXPORT jfloatArray JNICALL Java_jni_JniNode_getOrientation(JNIEnv* env, jobject o, POINTER pointer) {
    LOG_FUNCTION
    return quaternionToArray(env, yz::Node::get(pointer)->getOrientation());
}

JNIEXPORT jfloatArray JNICALL Java_jni_JniNode_translate(
    JNIEnv* env, jobject o, POINTER pointer, jfloat x, jfloat y, jfloat z) {
    LOG_FUNCTION
    yz::Node* node = yz::Node::get(pointer);
    node->translate(x, y, z);
    return vectorToArray(env, node->getPosition());
}

JNIEXPORT jfloatArray JNICALL Java_jni_JniNode_rotate(
    JNIEnv* env, jobject o, POINTER pointer, jfloat x, jfloat y) {
    LOG_FUNCTION
    return vectorToArray(env, yz::Node::get(pointer)->rotate(x, y));
}

JNIEXPORT void JNICALL Java_jni_JniNode_rotateQuaternion(
    JNIEnv* env, jobject o, POINTER pointer, jfloat x, jfloat y, jfloat z, jfloat w) {
    LOG_FUNCTION
    yz::Node::get(pointer)->rotate(w, x, y, z);
}

JNIEXPORT void JNICALL Java_jni_JniNode_scale(
    JNIEnv* env, jobject o, POINTER pointer, jfloat scaleX, jfloat scaleY, jfloat scaleZ) {
    LOG_FUNCTION
    yz::Node::get(pointer)->scale(scaleX, scaleY, scaleZ);
}

JNIEXPORT void JNICALL Java_jni_JniNode_attachTo(
    JNIEnv* env, jobject o, POINTER pointer, POINTER otherPointer) {
    LOG_FUNCTION
    yz::Node* node = yz::Node::get(pointer);
    yz::NativeMovableComponent* other = reinterpret_cast<yz::NativeMovableComponent*>(otherPointer);
    try {
        other->addMovableComponent(node);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT void JNICALL Java_jni_JniNode_attachToNode(
    JNIEnv* env, jobject o, POINTER pointer, POINTER otherPointer) {
    LOG_FUNCTION
    yz::Node* node = yz::Node::get(pointer);
    yz::Node* other = yz::Node::get(otherPointer);
    try {
        node->attachToNode(other);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT void JNICALL Java_jni_JniNode_detachFromParentNode(
    JNIEnv* env,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    yz::Node* node = yz::Node::get(pointer);
    try {
        node->detachFromParent();
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT void JNICALL Java_jni_JniNode_detachFromParent(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    POINTER parentPointer
    ) {
    LOG_FUNCTION
    yz::Node* node = yz::Node::get(pointer);
    yz::NativeMovableComponent* parent = reinterpret_cast<yz::NativeMovableComponent*>(parentPointer);
    try {
        parent->removeMovableComponent(node);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT void JNICALL Java_jni_JniNode_delete(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    yz::Node::get(pointer)->destroy();
}

