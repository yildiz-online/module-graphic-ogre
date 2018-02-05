/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 * Copyright (c) 2018 Grégory Van den Borre
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

#include "../includes/JniGuiText.h"
#include "../includes/JniUtil.h"
#include "../includes/GuiText.hpp"

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreText_constructor(
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
        yz::GuiText* text = new yz::GuiText(yz::GuiContainer::get(containerPointer), name.getValue());
        yz::Font* font = yz::Font::get(fontPointer);
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

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreText_setText(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jstring jtext) {
    LOG_FUNCTION
    JniStringWrapper text = JniStringWrapper(env, jtext);
    try {
        yz::GuiText::get(pointer)->setText(text.getValue());
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreText_hide(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    yz::GuiText::get(pointer)->hide();
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreText_delete(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    delete yz::GuiText::get(pointer);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreText_show(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    yz::GuiText::get(pointer)->show();
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreText_setPosition(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat x,
    jfloat y) {
    LOG_FUNCTION
    yz::GuiText::get(pointer)->setPosition(x, y);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreText_setFont(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    POINTER fontPointer,
    jfloat size) {
    LOG_FUNCTION
    try {
        yz::Font* font = yz::Font::get(fontPointer);
        yz::GuiText::get(pointer)->setFont(font, size);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreText_setColor(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat red,
    jfloat green,
    jfloat blue,
    jfloat alpha) {
    LOG_FUNCTION
    yz::GuiText::get(pointer)->setColor(red, green, blue, alpha);
}
