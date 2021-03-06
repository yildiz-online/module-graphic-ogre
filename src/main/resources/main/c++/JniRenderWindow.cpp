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

#include "../includes/JniRenderWindow.h"
#include "../includes/RenderWindow.hpp"
#include "../includes/Camera.hpp"
#include "../includes/PFXSSAO.h"

JNIEXPORT POINTER JNICALL Java_jni_JniRenderWindow_createViewport(
    JNIEnv*,
    jobject,
    POINTER camPointer) {
    LOG_FUNCTION
    yz::RenderWindow* rw = yz::RenderWindow::get();
    yz::Camera* cam = reinterpret_cast<yz::Camera*>(camPointer);
    yz::Viewport* vp = rw->addViewport(cam);
    return reinterpret_cast<POINTER> (vp);
}

JNIEXPORT void JNICALL Java_jni_JniRenderWindow_printScreen(
    JNIEnv* env,
    jobject,
    jstring jname) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    yz::RenderWindow::get()->printScreen(name.getValue());
}

JNIEXPORT jfloat JNICALL Java_jni_JniRenderWindow_getFps(
    JNIEnv*,
    jobject) {
    LOG_FUNCTION
    return yz::RenderWindow::get()->getFps();
}
