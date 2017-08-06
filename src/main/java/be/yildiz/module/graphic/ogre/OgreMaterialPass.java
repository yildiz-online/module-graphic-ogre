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

package be.yildiz.module.graphic.ogre;

import be.yildiz.common.Color;
import be.yildiz.common.nativeresources.NativePointer;
import be.yildiz.module.graphic.*;

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
        return new OgreTextureUnit(this.createUnit(this.pointer.getPointerAddress()));

    }

    @Override
    protected void setTransparentCapabilityImpl(final Transparency capability) {
        if (capability == Transparency.ALPHA) {
            this.setAlphaTransparency(this.pointer.getPointerAddress());
            this.setDepthWrite(this.pointer.getPointerAddress(), false);
        } else if (capability == Transparency.COLOR) {
            this.setColorTransparency(this.pointer.getPointerAddress());
        }
    }

    @Override
    protected void setDiffuseImpl(final Color color) {
        this.setDiffuse(this.pointer.getPointerAddress(), color.normalizedRed, color.normalizedGreen, color.normalizedBlue, color.normalizedAlpha);
    }

    @Override
    protected void setAmbientImpl(final Color color) {
        this.setAmbient(this.pointer.getPointerAddress(), color.normalizedRed, color.normalizedGreen, color.normalizedBlue);
    }

    @Override
    protected void enableColorImpl(final boolean enabled) {
        if (enabled) {
            this.enableColor(this.pointer.getPointerAddress());
        } else {
            this.disableColor(this.pointer.getPointerAddress());
        }
    }

    @Override
    protected void disableLightImpl() {
        this.disableLight(this.pointer.getPointerAddress());
    }

    @Override
    public void setFragmentProgramParameter(final ShaderParamFloat4 shaderParam) {
        this.setFragmentProgramParameterFloat4(this.pointer.getPointerAddress(),
                shaderParam.name, shaderParam.value1, shaderParam.value2, shaderParam.value3, shaderParam.value4);
    }

    @Override
    public void setFragmentProgramParameter(final ShaderParamFloat3 shaderParam) {
        this.setFragmentProgramParameterFloat3(this.pointer.getPointerAddress(),
                shaderParam.name, shaderParam.value1, shaderParam.value2, shaderParam.value3);
    }

    @Override
    public void setFragmentProgramParameter(final ShaderParamFloat2 shaderParam) {
        this.setFragmentProgramParameterFloat2(this.pointer.getPointerAddress(),
                shaderParam.name, shaderParam.value1, shaderParam.value2);
    }

    @Override
    public void setFragmentProgramParameter(final ShaderParamFloat shaderParam) {
        this.setFragmentProgramParameterFloat(this.pointer.getPointerAddress(), shaderParam.name, shaderParam.value);
    }

    @Override
    public void setFragmentProgramParameter(final ShaderParamColor shaderParam) {
        Color c = shaderParam.color;
        this.setFragmentProgramParameterColor(this.pointer.getPointerAddress(), shaderParam.name, c.normalizedRed, c.normalizedGreen, c.normalizedBlue, c.normalizedAlpha);
    }

    @Override
    public void setFragmentProgramParameterAuto(final String name, final ShaderConstantType constant) {
        this.setFragmentProgramParameterAuto(this.pointer.getPointerAddress(), name, constant.getValue());
    }

    @Override
    public void setFragmentProgramParameterAuto(final String name, final ShaderConstantType constant, final int param) {
        this.setFragmentProgramParameterAutoP(this.pointer.getPointerAddress(), name, constant.getValue(), param);
    }

    @Override
    public void setVertexProgramParameter(final ShaderParamFloat4 shaderParam) {
        this.setVertexProgramParameterFloat4(this.pointer.getPointerAddress(),
                shaderParam.name, shaderParam.value1, shaderParam.value2, shaderParam.value3, shaderParam.value4);
    }

    @Override
    public void setVertexProgramParameter(final ShaderParamFloat3 shaderParam) {
        this.setVertexProgramParameterFloat3(this.pointer.getPointerAddress(),
                shaderParam.name, shaderParam.value1, shaderParam.value2, shaderParam.value3);
    }

    @Override
    public void setVertexProgramParameter(final ShaderParamFloat2 shaderParam) {
        this.setVertexProgramParameterFloat2(this.pointer.getPointerAddress(),
                shaderParam.name, shaderParam.value1, shaderParam.value2);
    }

    @Override
    public void setVertexProgramParameter(final ShaderParamFloat shaderParam) {
        this.setVertexProgramParameterFloat(this.pointer.getPointerAddress(), shaderParam.name, shaderParam.value);
    }

    @Override
    public void setVertexProgramParameter(final ShaderParamColor shaderParam) {
        Color c = shaderParam.color;
        this.setVertexProgramParameterColor(this.pointer.getPointerAddress(), shaderParam.name, c.normalizedRed, c.normalizedGreen, c.normalizedBlue, c.normalizedAlpha);
    }

    @Override
    public void setVertexProgramParameterAuto(final String name, final ShaderConstantType auto, final int param) {
        this.setVertexProgramParameterAutoP(this.pointer.getPointerAddress(), name, auto.getValue(), param);
    }

    @Override
    public void setVertexProgramParameterAuto(final String name, final ShaderConstantType auto) {
        this.setVertexProgramParameterAuto(this.pointer.getPointerAddress(), name, auto.getValue());
    }

    @Override
    protected void setBlendModeImpl(final BlendMode mode) {
        if (mode != BlendMode.NONE) {
            this.blend(this.pointer.getPointerAddress(), mode.ordinal());
        }
    }

    @Override
    public MaterialPass setSceneBlend(final SceneBlend blend1, final SceneBlend blend2) {
        if (blend1 != SceneBlend.NONE && blend2 != SceneBlend.NONE) {
            this.complexBlend(this.pointer.getPointerAddress(), blend1.ordinal(), blend2.ordinal());
        }
        return this;
    }

    @Override
    public MaterialPass setEmissive(final Color color) {
        this.setEmissive(this.pointer.getPointerAddress(), color.normalizedRed, color.normalizedGreen, color.normalizedBlue);
        return this;
    }

    @Override
    public MaterialPass setDepthWrite(final boolean b) {
        this.setDepthWrite(this.pointer.getPointerAddress(), b);
        return this;
    }

    @Override
    public MaterialPass setVertexProgram(final String name) {
        this.setVertexProgram(this.pointer.getPointerAddress(), name);
        return this;
    }

    @Override
    public MaterialPass setFragmentProgram(final String name) {
        this.setFragmentProgram(this.pointer.getPointerAddress(), name);
        return this;
    }

    /**
     * Call to native code to enable color.
     *
     * @param pointer Native pointer value.
     */
    private native void enableColor(final long pointer);

    /**
     * Call to native code to disable color.
     *
     * @param pointer Native pointer value.
     */
    private native void disableColor(final long pointer);

    /**
     * Call to native code to create a new unit.
     *
     * @param pointer Native pointer value.
     * @return The new unit pointer value.
     */
    private native long createUnit(final long pointer);

    /**
     * Call to native code to enable alpha transparency.
     *
     * @param pointer Native pointer value.
     */
    private native void setAlphaTransparency(final long pointer);

    /**
     * Call to native code to enable color transparency.
     *
     * @param pointer Native pointer value.
     */
    private native void setColorTransparency(final long pointer);

    /**
     * Call to native code to set the diffuse color.
     *
     * @param pointer Native pointer value.
     * @param red     Red value.
     * @param green   Green value.
     * @param blue    Blue value.
     * @param alpha   Alpha value.
     */
    private native void setDiffuse(final long pointer, final float red, final float green, final float blue, final float alpha);

    /**
     * Call to native code to set the ambient color.
     *
     * @param pointer Native pointer value.
     * @param red     Red value.
     * @param green   Green value.
     * @param blue    Blue value.
     */
    private native void setAmbient(final long pointer, final float red, final float green, final float blue);

    /**
     * Call to native code to disable lights affecting this material pass.
     *
     * @param pointer Native pointer value.
     */
    private native void disableLight(final long pointer);

    /**
     * Set the blend operation to apply to this pass.
     *
     * @param pointer        Native pointer value.
     * @param blendOperation 0 is add, 1 subtract, 2 reverse subtract, 3 min, 4 max.
     */
    private native void blend(final long pointer, final int blendOperation);

    /**
     * Set the emissive color in native code.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param red     Emissive red value.
     * @param green   Emissive green value.
     * @param blue    Emissive blue value.
     */
    private native void setEmissive(final long pointer, final float red, final float green, final float blue);

    /**
     * Set a complex blend effect.
     *
     * @param pointerAddress Pointer address to the native Ogre::Pass.
     * @param blend1         First blend effect to apply.
     * @param blend2         Second blend effect to apply.
     */
    private native void complexBlend(final long pointerAddress, final int blend1, final int blend2);

    /**
     * Enable or disable depth write.
     *
     * @param address Pointer address to the native Ogre::Pass.
     * @param enabled <code>true</code> to enable, <code>false</code> to disable.
     */
    private native void setDepthWrite(final long address, final boolean enabled);

    /**
     * Set the alpha rejection.
     *
     * @param address Pointer address to the native Ogre::Pass.
     * @param value   Alpha value for pixel, between 0 and 255 but for hardware compatibility, max should be 128.
     */
    private native void setAlphaRejection(final long address, final int value);

    /**
     * Get a unit from its index.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param index   Unit index.
     * @return The found unit pointer.
     */
    private native long getUnit(final long pointer, final int index);

    /**
     * Set a shader vertex program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Vertex program name.
     */
    private native void setVertexProgram(final long pointer, final String name);

    /**
     * Set a shader fragment program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Fragment program name.
     */
    private native void setFragmentProgram(final long pointer, final String name);

    /**
     * Set a parameter to a fragment program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Parameter name.
     */
    private native void setFragmentProgramParameterColor(final long pointer, final String name, final float v1, final float v2, final float v3, final float v4);

    /**
     * Set a parameter to a fragment program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Parameter name.
     * @param value  Parameter value.
     */
    private native void setFragmentProgramParameterFloat(final long pointer, final String name, final float value);

    /**
     * Set a parameter to a fragment program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Parameter name.
     */
    private native void setFragmentProgramParameterFloat2(final long pointer, final String name, final float v1, final float v2);


    /**
     * Set a parameter to a fragment program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Parameter name.
     */
    private native void setFragmentProgramParameterFloat3(final long pointer, final String name, final float v1, final float v2, final float v3);


    /**
     * Set a parameter to a fragment program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Parameter name.
     */
    private native void setFragmentProgramParameterFloat4(final long pointer, final String name, final float v1, final float v2, final float v3, final float v4);

    /**
     * Set an automatic parameter to a fragment program.
     *
     * @param pointerAddress Pointer address to the native Ogre::Pass.
     * @param name           Parameter name.
     * @param constant       Automatic parameter enum value.
     */
    private native void setFragmentProgramParameterAuto(final long pointerAddress, final String name, final int constant);

    /**
     * Set an automatic parameter to a fragment program.
     *
     * @param pointerAddress Pointer address to the native Ogre::Pass.
     * @param name           Parameter name.
     * @param constant       Automatic parameter enum value.
     * @param param          Additional parameter.
     */
    private native void setFragmentProgramParameterAutoP(final long pointerAddress, final String name, final int constant, final int param);

    /**
     * Set a parameter to a vertex program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Parameter name.
     */
    private native void setVertexProgramParameterColor(final long pointer, final String name, final float v1, final float v2, final float v3, final float v4);

    /**
     * Set a parameter to a vertex program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Parameter name.
     * @param value  Parameter value.
     */
    private native void setVertexProgramParameterFloat(final long pointer, final String name, final float value);

    /**
     * Set a parameter to a vertex program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Parameter name.
     */
    private native void setVertexProgramParameterFloat2(final long pointer, final String name, final float v1, final float v2);


    /**
     * Set a parameter to a vertex program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Parameter name.
     */
    private native void setVertexProgramParameterFloat3(final long pointer, final String name, final float v1, final float v2, final float v3);


    /**
     * Set a parameter to a vertex program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Parameter name.
     */
    private native void setVertexProgramParameterFloat4(final long pointer, final String name, final float v1, final float v2, final float v3, final float v4);


    /**
     * Set an automatic parameter to a vertex program.
     *
     * @param pointerAddress Pointer address to the native Ogre::Pass.
     * @param name           Parameter name.
     * @param constant       Automatic parameter enum value.
     */
    private native void setVertexProgramParameterAuto(final long pointerAddress, final String name, final int constant);

    /**
     * Set an automatic parameter to a vertex program.
     *
     * @param pointerAddress Pointer address to the native Ogre::Pass.
     * @param name           Parameter name.
     * @param constant       Automatic parameter enum value.
     * @param param          Additional parameter.
     */
    private native void setVertexProgramParameterAutoP(final long pointerAddress, final String name, final int constant, final int param);

}
