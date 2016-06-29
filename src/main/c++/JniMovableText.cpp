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

#include "../includes/JniMovableText.h"
#include "../includes/MovableText.hpp"
#include "../includes/Font.hpp"
#include "../includes/Node.hpp"
#include "../includes/JniUtil.h"

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreMovableText_constructor(
    JNIEnv* env,
    jobject,
    POINTER nodePointer,
    jstring jname,
    jstring jtext,
    POINTER fontPointer,
    jfloat size) {
    LOG_FUNCTION
    JniStringWrapper name = JniStringWrapper(env, jname);
    JniStringWrapper text = JniStringWrapper(env, jtext);
    YZ::Node* node = YZ::Node::get(nodePointer);
    YZ::Font* font = YZ::Font::get(fontPointer);
    MOVABLETEXT* movableText = new MOVABLETEXT(name.getValue(), text.getValue(), font, size);
    node->addManualMovable(movableText);
    return reinterpret_cast<POINTER>(movableText);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMovableText_setTextColor(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jfloat red,
    jfloat green,
    jfloat blue,
    jfloat alpha) {
    LOG_FUNCTION
    reinterpret_cast<MOVABLETEXT*>(pointer)->setColor(red, green, blue, alpha);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMovableText_setTextAlignement(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jint h,
    jint v) {
    LOG_FUNCTION
    reinterpret_cast<MOVABLETEXT*>(pointer)->setTextAlignment((MOVABLETEXT::HorizontalAlignment)h, (MOVABLETEXT::VerticalAlignment)v);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMovableText_setTextOffset(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jfloat x,
    jfloat y,
    jfloat z) {
    LOG_FUNCTION
    reinterpret_cast<MOVABLETEXT*>(pointer)->setGlobalTranslation(Ogre::Vector3(x, y, z));
}
