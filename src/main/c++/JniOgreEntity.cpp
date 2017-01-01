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

#include "../includes/SceneManager.hpp"
#include "../includes/JniOgreEntity.h"
#include "../includes/JniUtil.h"

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreEntity_setMaterial(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    POINTER matPointer) {
    LOG_FUNCTION
    YZ::Entity* entity = YZ::Entity::get(pointer);
    YZ::Material* material = YZ::Material::get(matPointer);
    entity->setMaterial(material);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreEntity_setRenderingDistance(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jint distance) {
    LOG_FUNCTION
    YZ::Entity::get(pointer)->setRenderingDistance(distance);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreEntity_castShadow(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jboolean cast) {
    LOG_FUNCTION
    YZ::Entity::get(pointer)->setCastShadows(cast);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreEntity_setParameter(
    JNIEnv* env,
    jobject,
    POINTER pointer,
    jint index,
    jfloat v1, jfloat v2, jfloat v3, jfloat v4) {
    LOG_FUNCTION
    YZ::Entity::get(pointer)->setCustomParameters(index, v1, v2, v3, v4);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreEntity_setRenderQueue(
    JNIEnv*,
    jobject,
    POINTER pointer,
    jint index) {
    LOG_FUNCTION
    YZ::Entity::get(pointer)->setRenderQueueGroup(index);
}

JNIEXPORT jstring JNICALL Java_be_yildiz_module_graphic_ogre_OgreEntity_getParentSceneNode(
    JNIEnv* env,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    return env->NewStringUTF(YZ::Entity::get(pointer)->getParentSceneNode()->getName().c_str());
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreEntity_setUnpickable(
    JNIEnv*,
    jobject,
    POINTER pointer) {
    LOG_FUNCTION
    YZ::Entity::get(pointer)->setQueryFlags(Ogre::SceneManager::STATICGEOMETRY_TYPE_MASK);
}
