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

#include "../includes/JniShader.h"
#include "../includes/JniUtil.h"

JNIEXPORT jlong JNICALL Java_be_yildiz_module_graphic_ogre_OgreShader_createFragmentShader(
    JNIEnv* env, jobject o, jstring jname, jstring jpath) {
    try {
        JniStringWrapper name = JniStringWrapper(env, jname);
        JniStringWrapper path = JniStringWrapper(env, jpath);
        Ogre::GpuProgram* shader = Ogre::HighLevelGpuProgramManager::getSingleton().createProgram(
            name.getValue(),
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            "glsl",
            Ogre::GPT_FRAGMENT_PROGRAM).get();
        shader->setSourceFile(path.getValue());
        return reinterpret_cast<jlong>(shader);
    } catch (std::exception& e) {
        throwException(env, e.what());
        return -1L;
    }
}

JNIEXPORT jlong JNICALL Java_be_yildiz_module_graphic_ogre_OgreShader_createVertexShader(
    JNIEnv* env, jobject o, jstring jname, jstring jpath) {
    try {
        JniStringWrapper name = JniStringWrapper(env, jname);
        JniStringWrapper path = JniStringWrapper(env, jpath);
        Ogre::GpuProgram* shader = Ogre::HighLevelGpuProgramManager::getSingleton().createProgram(
            name.getValue(),
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            "glsl",
            Ogre::GPT_VERTEX_PROGRAM).get();
        shader->setSourceFile(path.getValue());
        return reinterpret_cast<jlong>(shader);
    } catch (std::exception& e) {
        throwException(env, e.what());
        return -1L;
    }
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreShader_setParameter(
    JNIEnv* env, jobject o, jlong pointer, jstring jname, jstring jvalue) {
    try {
        JniStringWrapper name = JniStringWrapper(env, jname);
        JniStringWrapper value = JniStringWrapper(env, jvalue);
        Ogre::GpuProgram* shader = reinterpret_cast<Ogre::GpuProgram*>(pointer);
        shader->setParameter(name.getValue(), value.getValue());
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreShader_load(
    JNIEnv* env, jobject o, jlong pointer) {
    try {
        reinterpret_cast<Ogre::GpuProgram*>(pointer)->load();
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

