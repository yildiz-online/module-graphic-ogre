//        This file is part of the Yildiz-Online project, licenced under the MIT License
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

#ifndef _JNI_GUI_ICON_H_
#define _JNI_GUI_ICON_H_

/**
*@author
*/
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreIcon_setPosition
  (JNIEnv *, jobject, POINTER, jfloat, jfloat);

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreIcon_constructor
  (JNIEnv *, jclass, POINTER, jstring, POINTER, jfloat w, jfloat h, jfloat x, jfloat y);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreIcon_hide
  (JNIEnv *, jobject, POINTER);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreIcon_show
  (JNIEnv *, jobject, POINTER);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreIcon_setTexture
  (JNIEnv *, jobject, POINTER, POINTER);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreIcon_delete
  (JNIEnv *, jobject, POINTER);

JNIEXPORT jint JNICALL Java_be_yildiz_module_graphic_ogre_OgreIcon_getZ
  (JNIEnv* env, jobject o, POINTER pointer);

JNIEXPORT jstring JNICALL Java_be_yildiz_module_graphic_ogre_OgreIcon_getParentName
  (JNIEnv* env, jobject o, POINTER pointer);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreIcon_setSize
  (JNIEnv *, jobject, POINTER, jfloat, jfloat);
#ifdef __cplusplus
}
#endif
#endif
