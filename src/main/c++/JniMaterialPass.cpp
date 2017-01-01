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

#include "../includes/JniMaterialPass.h"
#include "../includes/MaterialPass.hpp"
#include "../includes/EnumConversion.h"
#include "../includes/JniUtil.h"

JNIEXPORT jlongArray JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_getUnitList(
		JNIEnv* env, jclass,
		POINTER pointer) {
	LOG_FUNCTION
	Ogre::Pass* pass = YZ::MaterialPass::get(pointer);
	int size = pass->getNumTextureUnitStates();
	jlong* buf;
	buf = new jlong[size];
	for (int i = 0; i < size; i++) {
		buf[i] = reinterpret_cast<POINTER>(pass->getTextureUnitState(i));
	}
	jlongArray result = env->NewLongArray(size);
	env->SetLongArrayRegion(result, 0, size, buf);
	return result;
}

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_getUnit(
		JNIEnv* env, jclass,
		POINTER pointer, jint index) {
	LOG_FUNCTION
	try {
		return reinterpret_cast<POINTER>(YZ::MaterialPass::get(pointer)->getTextureUnitState(
				index));
	} catch (const std::exception& e) {
		throwException(env, e.what());
	}
	return 0L;
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_setAlphaTransparency(
		JNIEnv*, jobject,
		POINTER pointer) {
	LOG_FUNCTION
	YZ::MaterialPass::get(pointer)->setSceneBlending(
			Ogre::SBT_TRANSPARENT_ALPHA);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_setColorTransparency(
		JNIEnv*, jobject,
		POINTER pointer) {
	LOG_FUNCTION
	YZ::MaterialPass::get(pointer)->setSceneBlending(Ogre::SBT_ADD);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_setEmissive(
		JNIEnv*, jobject,
		POINTER pointer, jfloat red, jfloat green, jfloat blue) {
	LOG_FUNCTION
	YZ::MaterialPass::get(pointer)->setSelfIllumination(red, green, blue);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_disableLight(
		JNIEnv*, jobject,
		POINTER pointer) {
	LOG_FUNCTION
	YZ::MaterialPass::get(pointer)->setLightingEnabled(false);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_blend(
		JNIEnv*, jobject,
		POINTER pointer, jint blendOp) {
	LOG_FUNCTION
	Ogre::Pass* pass = YZ::MaterialPass::get(pointer);
	pass->setDepthWriteEnabled(false);
	pass->setSceneBlendingOperation(
			EnumConversion::getSceneBlendOperation(blendOp));
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_complexBlend(
		JNIEnv*, jobject,
		POINTER pointer, jint blend, jint blend2) {
	LOG_FUNCTION
	YZ::MaterialPass::get(pointer)->setSceneBlending(
			EnumConversion::getSceneBlendFactor(blend),
			EnumConversion::getSceneBlendFactor(blend2));
}

JNIEXPORT POINTER JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_createUnit(
		JNIEnv*, jobject,
		POINTER pointer) {
	LOG_FUNCTION
	return reinterpret_cast<POINTER>(YZ::MaterialPass::get(pointer)->createTextureUnitState());
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_setDiffuse(
		JNIEnv*, jobject,
		POINTER pointer, jfloat r, jfloat g, jfloat b, jfloat a) {
	LOG_FUNCTION
	YZ::MaterialPass::get(pointer)->setDiffuse(r, g, b, a);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_setAmbient(
		JNIEnv*, jobject,
		POINTER pointer, jfloat r, jfloat g, jfloat b) {
	LOG_FUNCTION
	YZ::MaterialPass::get(pointer)->setAmbient(r, g, b);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_enableColor(
		JNIEnv*, jobject,
		POINTER pointer) {
	LOG_FUNCTION
	YZ::MaterialPass::get(pointer)->setColourWriteEnabled(true);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_disableColor(
		JNIEnv*, jobject,
		POINTER pointer) {
	LOG_FUNCTION
	YZ::MaterialPass::get(pointer)->setColourWriteEnabled(false);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_setVertexProgram(
		JNIEnv* env, jobject,
		POINTER pointer, jstring jname) {
	LOG_FUNCTION
	JniStringWrapper name = JniStringWrapper(env, jname);
	YZ::MaterialPass::get(pointer)->setVertexProgram(name.getValue());
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_setFragmentProgram(
		JNIEnv* env, jobject,
		POINTER pointer, jstring jname) {
	LOG_FUNCTION
	JniStringWrapper name = JniStringWrapper(env, jname);
	YZ::MaterialPass::get(pointer)->setFragmentProgram(name.getValue());
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_setFragmentProgramParameterFloat4(
		JNIEnv* env, jobject,
		POINTER pointer, jstring jname, jfloat v1, jfloat v2, jfloat v3,
		jfloat v4) {
	LOG_FUNCTION
	JniStringWrapper name = JniStringWrapper(env, jname);
	Ogre::Vector4 vector = Ogre::Vector4(v1, v2, v3, v4);
	YZ::MaterialPass::get(pointer)->getFragmentProgramParameters()->setNamedConstant(
			name.getValue(), vector);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_setFragmentProgramParameterColor(
		JNIEnv* env, jobject,
		POINTER pointer, jstring jname, jfloat r, jfloat g, jfloat b,
		jfloat a) {
	LOG_FUNCTION
	JniStringWrapper name = JniStringWrapper(env, jname);
	Ogre::ColourValue color = Ogre::ColourValue(r, g, b, a);
	YZ::MaterialPass::get(pointer)->getFragmentProgramParameters()->setNamedConstant(
			name.getValue(), color);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_setFragmentProgramParameterFloat(
		JNIEnv* env, jobject,
		POINTER pointer, jstring jname, jfloat value) {
	LOG_FUNCTION
	JniStringWrapper name = JniStringWrapper(env, jname);
	YZ::MaterialPass::get(pointer)->getFragmentProgramParameters()->setNamedConstant(
			name.getValue(), value);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_setFragmentProgramParameterAuto(
		JNIEnv* env, jobject,
		POINTER pointer, jstring jname, jint autov) {
	LOG_FUNCTION
	JniStringWrapper name = JniStringWrapper(env, jname);
	YZ::MaterialPass::get(pointer)->getFragmentProgramParameters()->setNamedAutoConstant(
			name.getValue(), EnumConversion::getGpuProgramParameterAuto(autov));
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_setFragmentProgramParameterAutoP(
		JNIEnv* env, jobject,
		POINTER pointer, jstring jname, jint autov, jint autop) {
	LOG_FUNCTION
	JniStringWrapper name = JniStringWrapper(env, jname);
	YZ::MaterialPass::get(pointer)->getFragmentProgramParameters()->setNamedAutoConstant(
			name.getValue(), EnumConversion::getGpuProgramParameterAuto(autov),
			autop);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_setVertexProgramParameterAuto(
		JNIEnv* env, jobject,
		POINTER pointer, jstring jname, jint autov) {
	LOG_FUNCTION
	JniStringWrapper name = JniStringWrapper(env, jname);
	YZ::MaterialPass::get(pointer)->getVertexProgramParameters()->setNamedAutoConstant(
			name.getValue(), EnumConversion::getGpuProgramParameterAuto(autov));
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_setVertexProgramParameterAutoP(
		JNIEnv* env, jobject,
		POINTER pointer, jstring jname, jint autov, jint autop) {
	LOG_FUNCTION
	JniStringWrapper name = JniStringWrapper(env, jname);
	YZ::MaterialPass::get(pointer)->getVertexProgramParameters()->setNamedAutoConstant(
			name.getValue(), EnumConversion::getGpuProgramParameterAuto(autov),
			autop);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_setAlphaRejection(
		JNIEnv *, jobject,
		POINTER pointer, jint value) {
	LOG_FUNCTION
	YZ::MaterialPass::get(pointer)->setAlphaRejectValue(value);
}

JNIEXPORT void JNICALL Java_be_yildiz_module_graphic_ogre_OgreMaterialPass_setDepthWrite(
		JNIEnv* env, jobject,
		POINTER pointer, jboolean enabled) {
	LOG_FUNCTION
	YZ::MaterialPass::get(pointer)->setDepthWriteEnabled(enabled);
}
