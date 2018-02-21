/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 *  Copyright (c) 2018 Grégory Van den Borre
 *
 *  More infos available: https://www.yildiz-games.be
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 *  documentation files (the "Software"), to deal in the Software without restriction, including without
 *  limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 *  of the Software, and to permit persons to whom the Software is furnished to do so,
 *  subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or substantial
 *  portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 *  WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 *  OR COPYRIGHT  HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  SOFTWARE.
 *
 */

package be.yildizgames.module.graphic.ogre;

import be.yildizgames.module.color.Color;
import be.yildizgames.module.graphic.material.MaterialPass;
import be.yildizgames.module.graphic.shader.ShaderConstantType;
import be.yildizgames.module.graphic.shader.ShaderParamColor;
import be.yildizgames.module.graphic.shader.ShaderParamFloat;
import be.yildizgames.module.graphic.shader.ShaderParamFloat2;
import be.yildizgames.module.graphic.shader.ShaderParamFloat3;
import be.yildizgames.module.graphic.shader.ShaderParamFloat4;
import be.yildizgames.module.graphic.material.TextureUnit;
import be.yildizgames.common.jni.NativePointer;
import jni.JniMaterialPass;

import java.util.List;

/**
 * Ogre implementation for a MaterialPass.
 *
 * @author Grégory Van den Borre
 */
final class OgreMaterialPass extends MaterialPass {

    /**
     * Pointer value to the native object.
     */
    private final NativePointer pointer;

    private final JniMaterialPass jni = new JniMaterialPass();

    /**
     * Full constructor.
     *
     * @param address Value for the native pointer address.
     */
    OgreMaterialPass(final long address) {
        super();
        this.pointer = NativePointer.create(address);
        this.createUnit();
    }

    /**
     * Copy constructor.
     *
     * @param pointer      Value for the native pointer address.
     * @param index        Pass index value.
     * @param unitCopyList List of units.
     */
    OgreMaterialPass(final long pointer, final int index, final List<TextureUnit> unitCopyList) {
        // FIXME invalid transparency/blend values
        super(unitCopyList, Transparency.NONE, BlendMode.NONE);
        this.pointer = NativePointer.create(pointer);
    }

    /**
     * Get a list of all units for this pass.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @return The list of unit pointers.
     */
    static native long[] getUnitList(final long pointer);

    @Override
    protected OgreTextureUnit createUnitImpl(final int index) {
        return new OgreTextureUnit(this.jni.createUnit(this.pointer.getPointerAddress()));

    }

    @Override
    protected OgreMaterialPass setTransparentCapabilityImpl(final Transparency capability) {
        if (capability == Transparency.ALPHA) {
            this.jni.setAlphaTransparency(this.pointer.getPointerAddress());
            this.jni.setDepthWrite(this.pointer.getPointerAddress(), false);
        } else if (capability == Transparency.COLOR) {
            this.jni.setColorTransparency(this.pointer.getPointerAddress());
        }
        return this;
    }

    @Override
    protected void setDiffuseImpl(final Color color) {
        this.jni.setDiffuse(this.pointer.getPointerAddress(), color.normalizedRed, color.normalizedGreen, color.normalizedBlue, color.normalizedAlpha);
    }

    @Override
    protected void setAmbientImpl(final Color color) {
        this.jni.setAmbient(this.pointer.getPointerAddress(), color.normalizedRed, color.normalizedGreen, color.normalizedBlue);
    }

    @Override
    protected void enableColorImpl(final boolean enabled) {
        if (enabled) {
            this.jni.enableColor(this.pointer.getPointerAddress());
        } else {
            this.jni.disableColor(this.pointer.getPointerAddress());
        }
    }

    @Override
    protected void disableLightImpl() {
        this.jni.disableLight(this.pointer.getPointerAddress());
    }

    @Override
    public OgreMaterialPass setFragmentShaderParameter(final ShaderParamFloat4 shaderParam) {
        this.jni.setFragmentProgramParameterFloat4(this.pointer.getPointerAddress(),
                shaderParam.name, shaderParam.value1, shaderParam.value2, shaderParam.value3, shaderParam.value4);
        return this;
    }

    @Override
    public OgreMaterialPass setFragmentShaderParameter(final ShaderParamFloat3 shaderParam) {
        this.jni.setFragmentProgramParameterFloat3(this.pointer.getPointerAddress(),
                shaderParam.name, shaderParam.value1, shaderParam.value2, shaderParam.value3);
        return this;
    }

    @Override
    public OgreMaterialPass setFragmentShaderParameter(final ShaderParamFloat2 shaderParam) {
        this.jni.setFragmentProgramParameterFloat2(this.pointer.getPointerAddress(),
                shaderParam.name, shaderParam.value1, shaderParam.value2);
        return this;
    }

    @Override
    public OgreMaterialPass setFragmentShaderParameter(final ShaderParamFloat shaderParam) {
        this.jni.setFragmentProgramParameterFloat(this.pointer.getPointerAddress(), shaderParam.name, shaderParam.value);
        return this;
    }

    @Override
    public OgreMaterialPass setFragmentShaderParameter(final ShaderParamColor shaderParam) {
        Color c = shaderParam.color;
        this.jni.setFragmentProgramParameterColor(this.pointer.getPointerAddress(), shaderParam.name, c.normalizedRed, c.normalizedGreen, c.normalizedBlue, c.normalizedAlpha);
        return this;
    }

    @Override
    public OgreMaterialPass setFragmentShaderParameterAuto(final String name, final ShaderConstantType constant) {
        this.jni.setFragmentProgramParameterAuto(this.pointer.getPointerAddress(), name, constant.getValue());
        return this;
    }

    @Override
    public OgreMaterialPass setFragmentShaderParameterAuto(final String name, final ShaderConstantType constant, final int param) {
        this.jni.setFragmentProgramParameterAutoP(this.pointer.getPointerAddress(), name, constant.getValue(), param);
        return this;
    }

    @Override
    public OgreMaterialPass setVertexShaderParameter(final ShaderParamFloat4 shaderParam) {
        this.jni.setVertexProgramParameterFloat4(this.pointer.getPointerAddress(),
                shaderParam.name, shaderParam.value1, shaderParam.value2, shaderParam.value3, shaderParam.value4);
        return this;
    }

    @Override
    public OgreMaterialPass setVertexShaderParameter(final ShaderParamFloat3 shaderParam) {
        this.jni.setVertexProgramParameterFloat3(this.pointer.getPointerAddress(),
                shaderParam.name, shaderParam.value1, shaderParam.value2, shaderParam.value3);
        return this;
    }

    @Override
    public OgreMaterialPass setVertexShaderParameter(final ShaderParamFloat2 shaderParam) {
        this.jni.setVertexProgramParameterFloat2(this.pointer.getPointerAddress(),
                shaderParam.name, shaderParam.value1, shaderParam.value2);
        return this;
    }

    @Override
    public OgreMaterialPass setVertexShaderParameter(final ShaderParamFloat shaderParam) {
        this.jni.setVertexProgramParameterFloat(this.pointer.getPointerAddress(), shaderParam.name, shaderParam.value);
        return this;
    }

    @Override
    public OgreMaterialPass setVertexShaderParameter(final ShaderParamColor shaderParam) {
        Color c = shaderParam.color;
        this.jni.setVertexProgramParameterColor(this.pointer.getPointerAddress(), shaderParam.name, c.normalizedRed, c.normalizedGreen, c.normalizedBlue, c.normalizedAlpha);
        return this;
    }

    @Override
    public OgreMaterialPass setVertexShaderParameterAuto(final String name, final ShaderConstantType auto, final int param) {
        this.jni.setVertexProgramParameterAutoP(this.pointer.getPointerAddress(), name, auto.getValue(), param);
        return this;
    }

    @Override
    public OgreMaterialPass setVertexShaderParameterAuto(final String name, final ShaderConstantType auto) {
        this.jni.setVertexProgramParameterAuto(this.pointer.getPointerAddress(), name, auto.getValue());
        return this;
    }

    @Override
    protected OgreMaterialPass setBlendModeImpl(final BlendMode mode) {
        if (mode != BlendMode.NONE) {
            this.jni.blend(this.pointer.getPointerAddress(), mode.ordinal());
        }
        return this;
    }

    @Override
    public OgreMaterialPass setSceneBlend(final SceneBlend blend1, final SceneBlend blend2) {
        if (blend1 != SceneBlend.NONE && blend2 != SceneBlend.NONE) {
            this.jni.complexBlend(this.pointer.getPointerAddress(), blend1.ordinal(), blend2.ordinal());
        }
        return this;
    }

    @Override
    public OgreMaterialPass setEmissive(final Color color) {
        this.jni.setEmissive(this.pointer.getPointerAddress(), color.normalizedRed, color.normalizedGreen, color.normalizedBlue);
        return this;
    }

    @Override
    public OgreMaterialPass setDepthWrite(final boolean b) {
        this.jni.setDepthWrite(this.pointer.getPointerAddress(), b);
        return this;
    }

    @Override
    public OgreMaterialPass setVertexShader(final String name) {
        this.jni.setVertexProgram(this.pointer.getPointerAddress(), name);
        return this;
    }

    @Override
    public OgreMaterialPass setFragmentShader(final String name) {
        this.jni.setFragmentProgram(this.pointer.getPointerAddress(), name);
        return this;
    }
}
