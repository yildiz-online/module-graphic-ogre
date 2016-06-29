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

#ifndef _JNI_DYNAMIC_LINE_H_
#define _JNI_DYNAMIC_LINE_H_

/**
*@author Grégory Van den Borre
*/
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreLine_constructor
(JNIEnv* env, jobject o, POINTER nodePointer);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreLine_setMaterial
  (JNIEnv *, jobject, POINTER pointer, POINTER matPointer);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreLine_show
  (JNIEnv *, jobject,POINTER pointer);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreLine_hide
  (JNIEnv *, jobject,POINTER pointer);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreLine_update
(JNIEnv* env, jobject o,POINTER pointer, jfloat beginX, jfloat beginY, jfloat beginZ, jfloat endX, jfloat endY, jfloat endZ);





#ifdef __cplusplus
}
#endif
#endif
