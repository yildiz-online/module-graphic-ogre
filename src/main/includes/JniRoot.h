/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 * Copyright (c) 2018 Grégory Van den Borre
 *
 * More infos available: https://www.yildiz-games.be
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

#include <jni.h>

#ifndef JNI_ROOT_H
#define JNI_ROOT_H

/**
*@author Grégory Van den Borre
*/
#ifdef __cplusplus
extern "C" {
#endif
/**
 * Build a new yz::Root object.
 * @param env JNI environment.
 * @param object Current java object making the call.
 * @return A jlong value representing the address to the object, to cast as yz::Root* to be used.
 */
JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_Root_constructor(
    JNIEnv* env,
    jobject object);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_Root_initPhysFS(
    JNIEnv *env,
    jobject);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_Root_loadPlugin(
    JNIEnv* env,
    jobject object,
    jstring plugin);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_Root_loadRenderer(
    JNIEnv* env,
    jobject object,
    jstring renderer);
JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_Root_createSceneManager(
    JNIEnv* env,
    jobject object,
    jstring jname);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_Root_createRenderWindow(
    JNIEnv* env,
    jobject object,
    jint width,
    jint height,
    jlong handle);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_Root_createRenderWindowGlContext(
    JNIEnv* env,
    jobject object,
    jint width,
    jint heigth);

/**
 * @param type: 0 = file system, 1 = zip, 2 = physfs.
 */
 JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_Root_addResourcePath(
    JNIEnv* env,
    jobject object,
    jstring jname,
    jstring mediaPath,
    jint type);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_Root_renderOneFrame(
    JNIEnv* env,
    jobject object);

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_Root_close(
    JNIEnv* env,
    jobject object);

#ifdef __cplusplus
}
#endif

#endif
