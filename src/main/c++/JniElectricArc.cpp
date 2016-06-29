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

#include "../includes/JniElectricArc.h"
#include "../includes/ElectricArc.hpp"

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreElectricArc_setCeil(
    JNIEnv *env,
    jobject o,
    POINTER pointer,
    jint ceil) {
	LOG_FUNCTION
	YZ::ElectricArc::get(pointer)->setCeil(ceil);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreElectricArc_addLight(
    JNIEnv *env,
    jobject o,
    POINTER pointer,
    POINTER lightPointer) {
	LOG_FUNCTION
    YZ::ElectricArc::get(pointer)->addLight(YZ::PointLight::get(lightPointer));
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreElectricArc_setMaterial(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    POINTER matPointer) {
    LOG_FUNCTION
    YZ::ElectricArc::get(pointer)->setMaterial(YZ::Material::get(matPointer));
}
