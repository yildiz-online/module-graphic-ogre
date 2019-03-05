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
#include "../includes/GuiContainer.hpp"
#include "../includes/GuiIcon.hpp"
#include "../includes/JniGuiIcon.h"
#include "../includes/JniUtil.h"

JNIEXPORT POINTER JNICALL Java_jni_JniGuiIcon_constructor(
    JNIEnv* env,
    jclass,
    POINTER containerPointer,
    jstring jname,
    POINTER matPointer,
    jfloat w,
    jfloat h,
    jfloat x,
    jfloat y) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    yz::Material* material = yz::Material::get(matPointer);
    yz::GuiContainer* container = yz::GuiContainer::get(containerPointer);
    yz::GuiIcon* icon = new yz::GuiIcon(container, name.getValue(), material, w, h);
    icon->setPosition(x, y);
    return reinterpret_cast<POINTER>(icon);
}

JNIEXPORT void JNICALL Java_jni_JniGuiIcon_setTexture(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    POINTER matPointer) {
    LOG_FUNCTION
    try {
        yz::GuiIcon::get(pointer)->setMaterial(yz::Material::get(matPointer));
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT void JNICALL Java_jni_JniGuiIcon_setPosition(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat x,
    jfloat y) {
    LOG_FUNCTION
    yz::GuiIcon::get(pointer)->setPosition(x, y);
}

JNIEXPORT void JNICALL Java_jni_JniGuiIcon_hide(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    yz::GuiIcon::get(pointer)->hide();
}

JNIEXPORT void JNICALL Java_jni_JniGuiIcon_show(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    yz::GuiIcon::get(pointer)->show();
}

JNIEXPORT void JNICALL Java_jni_JniGuiIcon_delete(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    delete yz::GuiIcon::get(pointer);
}

JNIEXPORT jint JNICALL Java_jni_JniGuiIcon_getZ(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    return yz::GuiIcon::get(pointer)->getZ();
}

JNIEXPORT jstring JNICALL Java_jni_JniGuiIcon_getParentName(
    JNIEnv* env,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    return env->NewStringUTF(yz::GuiIcon::get(pointer)->getParent().c_str());
}

JNIEXPORT void JNICALL Java_jni_JniGuiIcon_setSize(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat w,
    jfloat h) {
    LOG_FUNCTION
    yz::GuiIcon::get(pointer)->setSize(w, h);
}
