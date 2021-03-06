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

#include "../includes/JniFont.h"
#include "../includes/Font.hpp"

JNIEXPORT POINTER JNICALL Java_jni_JniFont_createFont(
    JNIEnv* env,
    jobject,
    jstring jname,
    jstring jpath,
    jfloat size) {
    LOG_FUNCTION
    try {
        JniStringWrapper name = JniStringWrapper(env, jname);
        JniStringWrapper path = JniStringWrapper(env, jpath);
        yz::Font* font =  new yz::Font(name.getValue(), path.getValue(), size);
        return reinterpret_cast<POINTER>(font);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
    return INVALID_POINTER;
}

JNIEXPORT jfloatArray JNICALL Java_jni_JniFont_computeCharSize(JNIEnv* env, jobject, POINTER pointer) {

    LOG_FUNCTION
    yz::Font* font = reinterpret_cast<yz::Font*>(pointer);
    font->load();
    Ogre::Real size = font->getTrueTypeSize();
    jfloat buf[256];
    for (int c = 0; c < 256; c++) {
        buf[c] = font->getGlyphAspectRatio(c) * size;
    }
    jfloatArray result = env->NewFloatArray(256);
    env->SetFloatArrayRegion(result, 0, 256, buf);
    return result;
}

JNIEXPORT void JNICALL Java_jni_JniFont_delete(
    JNIEnv* env,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    yz::Font* font = reinterpret_cast<yz::Font*>(pointer);
    delete font;
}
