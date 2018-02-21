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

/**
*@author Grégory Van den Borre
*/

#include "../includes/Root.hpp"
#include "../includes/EnumConversion.h"
#include "../includes/JniRoot.h"
#include "../includes/JniUtil.h"

JNIEXPORT void JNICALL Java_jni_OgreRootNative_constructor(
    JNIEnv *env,
    jobject) {
    LOG_FUNCTION
    try {
        yz::Root::create();
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT void JNICALL Java_jni_OgreRootNative_initPhysFS(
    JNIEnv *env,
    jobject) {
    LOG_FUNCTION
    yz::Root::get()->initPhysFS();
}

JNIEXPORT void JNICALL Java_jni_OgreRootNative_loadPlugin(
    JNIEnv* env,
    jobject,
    jstring jplugin) {
    LOG_FUNCTION
    JniStringWrapper plugin = JniStringWrapper(env, jplugin);
    try {
        yz::Root::get()->loadPlugin(plugin.getValue());
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT void JNICALL Java_jni_OgreRootNative_loadRenderer(
    JNIEnv *env,
    jobject,
    jstring jrenderer) {
    LOG_FUNCTION
    JniStringWrapper renderer = JniStringWrapper(env, jrenderer);
    try {
        yz::Root::get()->initialise(renderer.getValue());
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT POINTER JNICALL Java_jni_OgreRootNative_createSceneManager(
    JNIEnv* env,
    jobject,
    jstring jname) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    try {
        return reinterpret_cast<POINTER>(yz::Root::get()->createSceneManager(name.getValue()));
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
    return INVALID_POINTER;
}

JNIEXPORT void JNICALL Java_jni_OgreRootNative_createRenderWindow(
    JNIEnv* env,
    jobject,
    jint width,
    jint height,
    jlong handle) {
    LOG_FUNCTION
    try {
        yz::Root::get()->createRenderWindow(width, height, handle);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT void JNICALL Java_jni_OgreRootNative_createRenderWindowGlContext(
    JNIEnv* env,
    jobject,
    jint width,
    jint height) {
    LOG_FUNCTION
    try {
        yz::Root::get()->createRenderWindow(width, height);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT void JNICALL Java_jni_OgreRootNative_addResourcePath(
    JNIEnv* env,
    jobject,
    jstring jname,
    jstring jpath,
    jint type) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    JniStringWrapper path = JniStringWrapper(env, jpath);
    try {
        yz::Root::get()->addResourcePath(name.getValue(), path.getValue(), type);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT void JNICALL Java_jni_OgreRootNative_renderOneFrame(
    JNIEnv* env,
    jobject) {
    LOG_FUNCTION
    try {
        yz::Root::get()->renderOneFrame();
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT void JNICALL Java_jni_OgreRootNative_close(
    JNIEnv* env,
    jobject) {
    LOG_FUNCTION
    try {
        yz::Root::get()->close();
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}
