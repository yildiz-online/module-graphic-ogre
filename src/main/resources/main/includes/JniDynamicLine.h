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

#include "JniUtil.h"

#ifndef JNI_DYNAMIC_LINE_H
#define JNI_DYNAMIC_LINE_H

/**
*@author Grégory Van den Borre
*/
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT POINTER JNICALL Java_jni_JniDynamicLine_constructor
(JNIEnv* env, jobject o, POINTER nodePointer);

JNIEXPORT void JNICALL Java_jni_JniDynamicLine_setMaterial
  (JNIEnv* env, jobject o, POINTER pointer, POINTER matPointer);

JNIEXPORT void JNICALL Java_jni_JniDynamicLine_show
  (JNIEnv* env, jobject o, POINTER pointer);

JNIEXPORT void JNICALL Java_jni_JniDynamicLine_hide
  (JNIEnv* env, jobject o, POINTER pointer);

JNIEXPORT void JNICALL Java_jni_JniDynamicLine_update
(JNIEnv* env, jobject o, POINTER pointer, jfloat beginX, jfloat beginY, jfloat beginZ, jfloat endX, jfloat endY, jfloat endZ);





#ifdef __cplusplus
}
#endif
#endif
