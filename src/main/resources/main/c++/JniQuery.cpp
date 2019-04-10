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

#include "../includes/Query.hpp"
#include "../includes/JniQuery.h"

JNIEXPORT POINTER JNICALL Java_jni_JniQuery_throwRay(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jfloat x,
    jfloat y,
    jboolean poly) {
    LOG_FUNCTION
    return reinterpret_cast<yz::Query*>(pointer)->throwRay(x, y, poly)->value();
}

JNIEXPORT jlongArray JNICALL Java_jni_JniQuery_throwPlaneRay(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jfloat left,
    jfloat top,
    jfloat right,
    jfloat bottom) {
    LOG_FUNCTION
    try {
        std::vector<yz::Id*> list = reinterpret_cast<yz::Query*>(pointer)->throwPlaneRay(left, right, top, bottom);

        if (list.empty()) {
            jlong buf[1];
            jlongArray result = env->NewLongArray(0);
            env->SetLongArrayRegion(result, 0, 0, buf);
            return result;
        }
        const int size = list.size();

        jlong* buf;
        buf = new jlong[size];
        for (int i = 0; i < size; i++) {
            buf[i] = list[i]->value();
        }
        jlongArray result = env->NewLongArray(size);
        env->SetLongArrayRegion(result, 0, size, buf);
        return result;
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
    return env->NewLongArray(1);
}
