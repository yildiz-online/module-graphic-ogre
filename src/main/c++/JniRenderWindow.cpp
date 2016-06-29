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

/**
*@author Grégory Van den Borre
*/

#include "../includes/JniRenderWindow.h"
#include "../includes/JniUtil.h"
#include "../includes/RenderWindow.hpp"
#include "../includes/Camera.hpp"
#include "../includes/PFXSSAO.h"

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_RenderWindow_createViewport(
    JNIEnv*,
    jobject,
    POINTER camPointer) {
    LOG_FUNCTION
    YZ::RenderWindow* rw = YZ::RenderWindow::get();
    YZ::Camera* cam = YZ::Camera::get(camPointer);
    YZ::Viewport* vp = rw->addViewport(cam);
    return reinterpret_cast<POINTER> (vp);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_RenderWindow_printScreen(
    JNIEnv* env,
    jobject,
    jstring jname) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    YZ::RenderWindow::get()->printScreen(name.getValue());
}

JNIEXPORT jfloat JNICALL Java_be_yildiz_module_graphic_ogre_RenderWindow_getFps(
    JNIEnv*,
    jobject) {
    LOG_FUNCTION
    return YZ::RenderWindow::get()->getFps();
}
