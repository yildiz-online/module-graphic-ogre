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

#include "../includes/JniGuiText.h"
#include "../includes/GuiText.hpp"

JNIEXPORT POINTER JNICALL Java_jni_JniGuiText_constructor(
    JNIEnv* env,
    jclass,
    POINTER containerPointer,
    jfloat w,
    jfloat h,
    jfloat x,
    jfloat y,
    POINTER fontPointer,
    jfloat size,
    jstring jname) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    try { 
        yz::GuiText* text = new yz::GuiText(reinterpret_cast<yz::GuiContainer*>(containerPointer), name.getValue());
        yz::Font* font = reinterpret_cast<yz::Font*>(fontPointer);
        text->setSize(w, h);
        text->setPosition(x, y);
        text->hide();
        text->setFont(font, size);
        return reinterpret_cast<POINTER>(text);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
    return INVALID_POINTER;
}

JNIEXPORT void JNICALL Java_jni_JniGuiText_setText(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jstring jtext) {
    LOG_FUNCTION
    JniStringWrapper text = JniStringWrapper(env, jtext);
    try {
        reinterpret_cast<yz::GuiText*>(pointer)->setText(text.getValue());
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT void JNICALL Java_jni_JniGuiText_hide(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    reinterpret_cast<yz::GuiText*>(pointer)->hide();
}

JNIEXPORT void JNICALL Java_jni_JniGuiText_delete(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    delete reinterpret_cast<yz::GuiText*>(pointer);
}

JNIEXPORT void JNICALL Java_jni_JniGuiText_show(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    reinterpret_cast<yz::GuiText*>(pointer)->show();
}

JNIEXPORT void JNICALL Java_jni_JniGuiText_setPosition(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat x,
    jfloat y) {
    LOG_FUNCTION
    reinterpret_cast<yz::GuiText*>(pointer)->setPosition(x, y);
}

JNIEXPORT void JNICALL Java_jni_JniGuiText_setFont(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    POINTER fontPointer,
    jfloat size) {
    LOG_FUNCTION
    try {
        yz::Font* font = reinterpret_cast<yz::Font*>(fontPointer);
        reinterpret_cast<yz::GuiText*>(pointer)->setFont(font, size);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT void JNICALL Java_jni_JniGuiText_setColor(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat red,
    jfloat green,
    jfloat blue,
    jfloat alpha) {
    LOG_FUNCTION
    reinterpret_cast<yz::GuiText*>(pointer)->setColor(red, green, blue, alpha);
}
