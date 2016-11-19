﻿//        This file is part of the Yildiz-Online project, licenced under the MIT License
//        (MIT)
//
//        Copyright (c) 2016 Grégory Van den Borre
//
//        More infos available: http://yildiz.bitbucket.org
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
//        of this software and associated documentation files (the "Software"), to deal
//        in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
//        furnished to do so, subject to the following conditions:
//
//        The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
//        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//        SOFTWARE.

#include <jni.h>
#include "stdafx.h"

#ifndef JNI_TEXTURE_UNIT_H
#define JNI_TEXTURE_UNIT_H

/**
*@author Grégory Van den Borre
*/
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreTextureUnit_setTextureFilter(
        JNIEnv* env,
        jobject,
        POINTER pointer,
        jint filter);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreTextureUnit_setCoordinateSet(
        JNIEnv* env,
        jobject,
        POINTER pointer,
        jint set);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreTextureUnit_setColorOperationExManual(
        JNIEnv* env,
        jobject o,
        POINTER pointer,
        jint operation,
        jint src,
        jint src2,
        jfloat r,
        jfloat g,
        jfloat b);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreTextureUnit_setAlphaOperation(
        JNIEnv* env,
        jobject o,
        POINTER pointer,
        jint operation,
        jint src,
        jint src2);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreTextureUnit_setTexture(
        JNIEnv *,
        jobject,
        POINTER,
        jstring);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreTextureUnit_setTextureAnimated(
        JNIEnv *,
        jobject,
        POINTER,
        jstring,
        jint,
        jint);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreTextureUnit_setScale(
        JNIEnv *,
        jobject,
        POINTER,
        jfloat,
        jfloat);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreTextureUnit_setColorOperation(
        JNIEnv* env,
        jobject o,
        POINTER unitPointer,
        jint operation);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreTextureUnit_setColorOperationEx(
        JNIEnv* env,
        jobject o,
        POINTER unitPointer,
        jint operation,
        jint src,
        jint src2);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreTextureUnit_scroll(
        JNIEnv* env,
        jobject o,
        POINTER unitPointer,
        jfloat x,
        jfloat y);

#ifdef __cplusplus
}
#endif

#endif // TEXTURE_H
