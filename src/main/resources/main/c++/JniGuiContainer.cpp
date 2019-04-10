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

#include "../includes/JniGuiContainer.h"
#include "../includes/GuiContainer.hpp"

JNIEXPORT POINTER JNICALL Java_jni_JniGuiContainer_constructor(
    JNIEnv* env,
    jclass,
    POINTER matPointer,
    jstring jname,
    jfloat width,
    jfloat height) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    yz::Material* material = reinterpret_cast<yz::Material*>(matPointer);
    return reinterpret_cast<POINTER>(new yz::GuiContainer(name.getValue(), material, width, height));
}

JNIEXPORT POINTER JNICALL Java_jni_JniGuiContainer_constructorParent(
    JNIEnv* env,
    jclass,
    POINTER matPointer,
    jstring jname,
    jfloat width,
    jfloat height,
    POINTER parentPointer) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    yz::GuiContainer* parent = reinterpret_cast<yz::GuiContainer*>(parentPointer);
    yz::Material* material = reinterpret_cast<yz::Material*>(matPointer);
    return reinterpret_cast<POINTER>(new yz::GuiContainer(name.getValue(), material, width, height, parent));
}

JNIEXPORT void JNICALL Java_jni_JniGuiContainer_setPosition(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat x,
    jfloat y) {
    LOG_FUNCTION
    reinterpret_cast<yz::GuiContainer*>(pointer)->setPosition(x, y);
}

JNIEXPORT void JNICALL Java_jni_JniGuiContainer_show(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    reinterpret_cast<yz::GuiContainer*>(pointer)->show();
}

JNIEXPORT void JNICALL Java_jni_JniGuiContainer_hide(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    reinterpret_cast<yz::GuiContainer*>(pointer)->hide();
}

JNIEXPORT void JNICALL Java_jni_JniGuiContainer_setSize(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat width,
    jfloat height) {
    LOG_FUNCTION
    reinterpret_cast<yz::GuiContainer*>(pointer)->setSize(width, height);
}

JNIEXPORT jstring JNICALL Java_jni_JniGuiContainer_getElement(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jfloat x,
    jfloat y) {
    LOG_FUNCTION
    try {
        return env->NewStringUTF(
        		reinterpret_cast<yz::GuiContainer*>(pointer)->getElementAt(x, y).c_str());
    } catch (const std::exception& e) {
        return env->NewStringUTF("world");
        //FIXME do something.
    }
    return env->NewStringUTF("world");
}

JNIEXPORT void JNICALL Java_jni_JniGuiContainer_zoom(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat factor) {
    LOG_FUNCTION
    reinterpret_cast<yz::GuiContainer*>(pointer)->zoom(factor);
}

JNIEXPORT void JNICALL Java_jni_JniGuiContainer_setZ(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jshort z) {
    LOG_FUNCTION
    reinterpret_cast<yz::GuiContainer*>(pointer)->setZ(z);
}

JNIEXPORT void JNICALL Java_jni_JniGuiContainer_setMaterial(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    POINTER matPointer) {
    LOG_FUNCTION
    reinterpret_cast<yz::GuiContainer*>(pointer)->setMaterial(reinterpret_cast<yz::Material*>(matPointer));
}

JNIEXPORT void JNICALL Java_jni_JniGuiContainer_addChildrenPosition(
    JNIEnv * env,
    jobject,
    POINTER pointer,
    jint left,
    jint top) {
    LOG_FUNCTION
    reinterpret_cast<yz::GuiContainer*>(pointer)->addToChildren(left, top);
}
