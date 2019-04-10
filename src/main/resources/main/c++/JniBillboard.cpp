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

#include "../includes/Billboard.hpp"
#include "../includes/JniBillboard.h"


JNIEXPORT void JNICALL Java_jni_JniBillboard_setPosition(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jfloat x,
    jfloat y,
    jfloat z) {
    LOG_FUNCTION
    try {
        reinterpret_cast<yz::Billboard*>(pointer)->setPosition(x, y, z);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT void JNICALL Java_jni_JniBillboard_setSize(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jfloat width,
    jfloat height) {
    LOG_FUNCTION
    try {
    	reinterpret_cast<yz::Billboard*>(pointer)->setDimensions(width, height);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT void JNICALL Java_jni_JniBillboard_setColor(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jfloat red,
    jfloat green,
    jfloat blue,
    jfloat alpha) {
    LOG_FUNCTION
    reinterpret_cast<yz::Billboard*>(pointer)->setColor(red, green, blue, alpha);
}
