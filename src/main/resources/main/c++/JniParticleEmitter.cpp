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

#include "../includes/JniParticleEmitter.h"
#include "../includes/ParticleEmitter.hpp"

JNIEXPORT void JNICALL Java_jni_JniParticleEmitter_setMinSpeed(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat speed) {
    LOG_FUNCTION
    reinterpret_cast<yz::ParticleEmitter*>(pointer)->setMinSpeed(speed);
}

JNIEXPORT void JNICALL Java_jni_JniParticleEmitter_setMaxSpeed(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat speed) {
    LOG_FUNCTION
    reinterpret_cast<yz::ParticleEmitter*>(pointer)->setMaxSpeed(speed);
}

JNIEXPORT void JNICALL Java_jni_JniParticleEmitter_setStartColor(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat r,
    jfloat g,
    jfloat b,
    jfloat a) {
    LOG_FUNCTION
    reinterpret_cast<yz::ParticleEmitter*>(pointer)->setStartColor(r, g, b, a);
}

JNIEXPORT void JNICALL Java_jni_JniParticleEmitter_setEndColor(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat r,
    jfloat g,
    jfloat b,
    jfloat a) {
    LOG_FUNCTION
    reinterpret_cast<yz::ParticleEmitter*>(pointer)->setEndColor(r, g, b, a);
}

JNIEXPORT void JNICALL Java_jni_JniParticleEmitter_setAngle(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat angle) {
    LOG_FUNCTION
    reinterpret_cast<yz::ParticleEmitter*>(pointer)->setAngle(angle);
}

JNIEXPORT void JNICALL Java_jni_JniParticleEmitter_setRate(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat rate) {
    LOG_FUNCTION
    reinterpret_cast<yz::ParticleEmitter*>(pointer)->setRate(rate);
}

JNIEXPORT void JNICALL Java_jni_JniParticleEmitter_setLifeTime(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat life) {
    LOG_FUNCTION
    reinterpret_cast<yz::ParticleEmitter*>(pointer)->setLifeTime(life);
}

JNIEXPORT void JNICALL Java_jni_JniParticleEmitter_setDuration(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat duration) {
    LOG_FUNCTION
    reinterpret_cast<yz::ParticleEmitter*>(pointer)->setDuration(duration);
}

JNIEXPORT void JNICALL Java_jni_JniParticleEmitter_setRepeatDelay(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat delay) {
    LOG_FUNCTION
    reinterpret_cast<yz::ParticleEmitter*>(pointer)->setRepeatDelay(delay);
}

JNIEXPORT void JNICALL Java_jni_JniParticleEmitter_setDirection(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat x,
    jfloat y,
    jfloat z) {
    LOG_FUNCTION
    reinterpret_cast<yz::ParticleEmitter*>(pointer)->setDirection(x, y, z);
}

