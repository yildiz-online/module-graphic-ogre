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

#include "../includes/JniLensFlare.h"
#include "../includes/Lensflare.hpp"

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreLensFlare_setPosition(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat x,
    jfloat y,
    jfloat z) {
    LOG_FUNCTION
    yz::LensFlare::get(pointer)->setPosition(x, y, z);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreLensFlare_setLightSize(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat w,
    jfloat h) {
    LOG_FUNCTION
    yz::LensFlare::get(pointer)->setLightSize(w, h);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreLensFlare_setStreakSize(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat w,
    jfloat h) {
    LOG_FUNCTION
    yz::LensFlare::get(pointer)->setStreakSize(w, h);
}
