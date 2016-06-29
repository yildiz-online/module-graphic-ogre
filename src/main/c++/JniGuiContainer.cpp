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

#include "../includes/JniGuiContainer.h"
#include "../includes/GuiContainer.hpp"
#include "../includes/JniUtil.h"

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreGuiContainer_constructor(
    JNIEnv* env,
    jclass,
    POINTER matPointer,
    jstring jname,
    jfloat width,
    jfloat height) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    YZ::Material* material = YZ::Material::get(matPointer);
    return reinterpret_cast<POINTER>(new YZ::GuiContainer(name.getValue(), material, width, height));
}

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreGuiContainer_constructorParent(
    JNIEnv* env,
    jclass,
    POINTER matPointer,
    jstring jname,
    jfloat width,
    jfloat height,
    POINTER parentPointer) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    YZ::GuiContainer* parent = YZ::GuiContainer::get(parentPointer);
    YZ::Material* material = YZ::Material::get(matPointer);
    return reinterpret_cast<POINTER>(new YZ::GuiContainer(name.getValue(), material, width, height, parent));
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreGuiContainer_setPosition(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat x,
    jfloat y) {
    LOG_FUNCTION
    YZ::GuiContainer::get(pointer)->setPosition(x, y);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreGuiContainer_show(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    YZ::GuiContainer::get(pointer)->show();
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreGuiContainer_hide(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    YZ::GuiContainer::get(pointer)->hide();
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreGuiContainer_setSize(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat width,
    jfloat height) {
    LOG_FUNCTION
    YZ::GuiContainer::get(pointer)->setSize(width, height);
}

JNIEXPORT jstring JNICALL Java_be_yildiz_module_graphic_ogre_OgreGuiContainer_getElement(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jfloat x,
    jfloat y) {
    LOG_FUNCTION
    try {
        return env->NewStringUTF(
        		YZ::GuiContainer::get(pointer)->getElementAt(x, y).c_str());
    } catch (const std::exception& e) {
        return env->NewStringUTF("world");
        //FIXME do something.
    }
    return env->NewStringUTF("world");
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreGuiContainer_zoom(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat factor) {
    LOG_FUNCTION
    YZ::GuiContainer::get(pointer)->zoom(factor);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreGuiContainer_setZ(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jshort z) {
    LOG_FUNCTION
    YZ::GuiContainer::get(pointer)->setZ(z);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreGuiContainer_setMaterial(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    POINTER matPointer) {
    LOG_FUNCTION
    YZ::GuiContainer::get(pointer)->setMaterial(YZ::Material::get(matPointer));
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreGuiContainer_addChildrenPosition(
    JNIEnv * env,
    jobject,
    POINTER pointer,
    jint left,
    jint top) {
    LOG_FUNCTION
    YZ::GuiContainer::get(pointer)->addToChildren(left, top);
}
