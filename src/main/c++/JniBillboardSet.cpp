/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 * Copyright (c) 2017 Grégory Van den Borre
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

#include "../includes/stdafx.h"
#include "../includes/BillboardSet.hpp"
#include "../includes/JniBillboardSet.h"
#include "../includes/Node.hpp"
#include "../includes/JniUtil.h"

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreBillboardSet_createBillboard(
    JNIEnv* env,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    try {
        YZ::BillboardSet* set = YZ::BillboardSet::get(pointer); 
        return reinterpret_cast<POINTER>(set->createBillboard());
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
    return INVALID_POINTER;
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreBillboardSet_show(
    JNIEnv *,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    YZ::BillboardSet::get(pointer)->show();
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreBillboardSet_hide(
    JNIEnv *,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    YZ::BillboardSet::get(pointer)->hide();
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreBillboardSet_setSize(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jfloat width,
    jfloat height) {
    LOG_FUNCTION
    try {
        YZ::BillboardSet::get(pointer)->setSize(width, height);
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreBillboardSet_attachToNode(
    JNIEnv*,
    jobject,
    POINTER pointer,
    POINTER nodePointer) {
    LOG_FUNCTION
    YZ::BillboardSet* set = YZ::BillboardSet::get(pointer);
    YZ::Node* node = YZ::Node::get(nodePointer);
    node->attachObject(set);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreBillboardSet_remove(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    POINTER billboardPointer) {
    LOG_FUNCTION
    try {
        YZ::BillboardSet::get(pointer)->removeBillboard(YZ::Billboard::get(billboardPointer));
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

