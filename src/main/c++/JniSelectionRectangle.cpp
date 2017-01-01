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

#include "../includes/JniSelectionRectangle.h"
#include "../includes/SelectionRectangle.hpp"

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreSelectionRectangle_constructor(
    JNIEnv* env,
    jclass,
    POINTER matPointer,
    POINTER contentMatPointer) {
    LOG_FUNCTION
    YZ::Material* mat = YZ::Material::get(matPointer);
    YZ::Material* cmat = YZ::Material::get(contentMatPointer);
    return reinterpret_cast<POINTER>(new YZ::SelectionRectangle(mat, cmat));
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreSelectionRectangle_update(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jfloat x1,
    jfloat y1,
    jfloat x2,
    jfloat y2) {
    LOG_FUNCTION
    YZ::SelectionRectangle::get(pointer)->update(x1, y1, x2, y2);
}
