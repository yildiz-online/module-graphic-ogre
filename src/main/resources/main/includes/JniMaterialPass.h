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

#ifndef JNI_MATERIAL_PASS_H
#define JNI_MATERIAL_PASS_H

/**
*@author Grégory Van den Borre
*/
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_setEmissive(
		JNIEnv* env, jobject o,
		POINTER pointer, jfloat red, jfloat green, jfloat blue);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_setFragmentProgramParameterFloat4(
    JNIEnv* env, jobject o, POINTER pointer, jstring jname, jfloat v1, jfloat v2, jfloat v3, jfloat v4);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_setFragmentProgramParameterFloat3(
    JNIEnv* env, jobject o, POINTER pointer, jstring jname, jfloat v1, jfloat v2, jfloat v3);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_setFragmentProgramParameterFloat2(
    JNIEnv* env, jobject o, POINTER pointer, jstring jname, jfloat v1, jfloat v2, jfloat v3);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_setFragmentProgramParameterFloat(
    JNIEnv* env, jobject o, POINTER pointer, jstring jname, jfloat value);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_setFragmentProgramParameterColor(
    JNIEnv* env, jobject o, POINTER pointer, jstring jname, jfloat v1, jfloat v2, jfloat v3, jfloat v4);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_setVertexProgramParameterFloat4(
    JNIEnv* env, jobject o, POINTER pointer, jstring jname, jfloat v1, jfloat v2, jfloat v3, jfloat v4);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_setVertexProgramParameterFloat3(
    JNIEnv* env, jobject o, POINTER pointer, jstring jname, jfloat v1, jfloat v2, jfloat v3);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_setVertexProgramParameterFloat2(
    JNIEnv* env, jobject o, POINTER pointer, jstring jname, jfloat v1, jfloat v2);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_setVertexProgramParameterFloat(
    JNIEnv* env, jobject o, POINTER pointer, jstring jname, jfloat value);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_setVertexProgramParameterColor(
    JNIEnv* env, jobject o, POINTER pointer, jstring jname, jfloat v1, jfloat v2, jfloat v3, jfloat v4);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_complexBlend(
		JNIEnv* env, jobject o,
		POINTER pointer, jint blend, jint blend2);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_setVertexProgram(
		JNIEnv* env, jobject o,
		POINTER pointer, jstring jname);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_setFragmentProgram(
		JNIEnv* env, jobject o,
		POINTER pointer, jstring jname);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_setFragmentProgramParameterAuto(
		JNIEnv* env, jobject o,
		POINTER pointer, jstring jname, jint autov);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_setFragmentProgramParameterAutoP(
		JNIEnv* env, jobject o,
		POINTER pointer, jstring jname, jint autov, jint autop);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_setVertexProgramParameterAuto(
		JNIEnv* env, jobject o,
		POINTER pointer, jstring jname, jint autov);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_setVertexProgramParameterAutoP(
		JNIEnv* env, jobject o,
		POINTER pointer, jstring jname, jint autov, jint autop);

JNIEXPORT POINTER JNICALL Java_jni_JniMaterialPass_createUnit(
		JNIEnv* env, jobject o,
		POINTER pointer);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_setAlphaTransparency(
		JNIEnv* env, jobject o,
		POINTER pointer);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_setAlphaRejection(
		JNIEnv* env, jobject o,
		POINTER pointer, jint value);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_blend(
		JNIEnv* env, jobject o,
		POINTER pointer, jint blendOp);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_setColorTransparency(
		JNIEnv* env, jobject o,
		POINTER pointer);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_setDiffuse(
		JNIEnv* env, jobject o,
		POINTER passPointer, jfloat r, jfloat g, jfloat b, jfloat a);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_setAmbient(
		JNIEnv* env, jobject o,
		POINTER passPointer, jfloat r, jfloat g, jfloat b);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_enableColor(
		JNIEnv* env, jobject o,
		POINTER passPointer);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_disableLight(
		JNIEnv* env, jobject o,
		POINTER passPointer);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_disableColor(
		JNIEnv* env, jobject o,
		POINTER passPointer);

JNIEXPORT jlongArray JNICALL Java_jni_JniMaterialPass_getUnitList(
		JNIEnv* env, jclass c,
		POINTER passPointer);

JNIEXPORT POINTER JNICALL Java_jni_JniMaterialPass_getUnit(
		JNIEnv* env, jclass c,
		POINTER passPointer, jint index);

JNIEXPORT void JNICALL Java_jni_JniMaterialPass_setDepthWrite(
		JNIEnv* env, jobject o,
		POINTER pointer, jboolean enabled);

#ifdef __cplusplus
}
#endif

#endif
