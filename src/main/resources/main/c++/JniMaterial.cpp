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

#include "../includes/JniMaterial.h"
#include "../includes/Material.hpp"
#include "../includes/EnumConversion.h"
#include "../includes/JniUtil.h"

JNIEXPORT POINTER JNICALL Java_jni_JniMaterial_createTexture(
    JNIEnv* env,
    jobject,
    jstring jname) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    yz::Material* mat = new yz::Material(name.getValue());
    return reinterpret_cast<POINTER>(mat);
}

JNIEXPORT POINTER JNICALL Java_jni_JniMaterial_copy(
    JNIEnv* env, jobject, POINTER pointer, jstring jname) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    yz::Material* material = reinterpret_cast<yz::Material*>(pointer);
    yz::Material* copy = material->clone(name.getValue());
    return reinterpret_cast<POINTER>(copy);
}

JNIEXPORT void JNICALL Java_jni_JniMaterial_loadTexture(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    yz::Material* material =  reinterpret_cast<yz::Material*>(pointer);
    material->compile();
    material->load();
}

JNIEXPORT jlongArray JNICALL Java_jni_JniMaterial_getTechniqueList(
    JNIEnv* env,
    jclass,
    POINTER pointer) {
    LOG_FUNCTION
    yz::Material* material = reinterpret_cast<yz::Material*>(pointer);
    int size = material->getNumTechniques();
    POINTER* buf;
    buf = new jlong[size];
    for (int i = 0; i < size; i++) {
        buf[i] = reinterpret_cast<POINTER>(material->getTechnique(i));
    }
    jlongArray result = env->NewLongArray(size);
    env->SetLongArrayRegion(result, 0, size, buf);
    return result;
}

JNIEXPORT POINTER JNICALL Java_jni_JniMaterial_getTechnique(
    JNIEnv* env, jobject, POINTER pointer, jint index) {
    LOG_FUNCTION
    try {
        yz::Material* mat = reinterpret_cast<yz::Material*>(pointer);
        return reinterpret_cast<POINTER>(mat->getTechnique(index));
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
    return INVALID_POINTER;
}

JNIEXPORT POINTER JNICALL Java_jni_JniMaterial_createTechnique(
    JNIEnv*, jobject, POINTER pointer) {
    LOG_FUNCTION
    return reinterpret_cast<POINTER>(reinterpret_cast<yz::Material*>(pointer)->createTechnique());
}

JNIEXPORT void JNICALL Java_jni_JniMaterial_receiveShadow(
    JNIEnv* env,
    jobject o,
    POINTER pointer,
    jboolean receive) {
    LOG_FUNCTION
    reinterpret_cast<yz::Material*>(pointer)->setReceiveShadows(receive);
}
