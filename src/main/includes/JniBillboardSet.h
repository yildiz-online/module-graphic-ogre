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

#ifndef JNI_BILLBOARD_SET_H
#define JNI_BILLBOARD_SET_H

/**
*@author Grégory Van den Borre
*/
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreBillboardSet_createBillboard
  (JNIEnv *, jobject, POINTER);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreBillboardSet_show
  (JNIEnv *, jobject, POINTER);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreBillboardSet_hide
  (JNIEnv *, jobject, POINTER);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreBillboardSet_setSize
(JNIEnv*, jobject, POINTER pointer, jfloat width, jfloat height);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreBillboardSet_attachToNode
(JNIEnv* env, jobject o,POINTER pointer, POINTER nodePointer);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreBillboardSet_remove(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    POINTER bbPointer);


#ifdef __cplusplus
}
#endif
#endif
