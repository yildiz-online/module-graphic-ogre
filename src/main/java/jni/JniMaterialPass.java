/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *  
 * Copyright (c) 2019 Grégory Van den Borre
 *
 * More infos available: https://engine.yildiz-games.be
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this 
 * software and associated documentation files (the "Software"), to deal in the Software 
 * without restriction, including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons 
 * to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or 
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS  OR COPYRIGHT  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE  SOFTWARE.
 */

package jni;

/**
 * @author Grégory Van den Borre
 */
public class JniMaterialPass {

    /**
     * Call to native code to enable color.
     *
     * @param pointer Native pointer value.
     */
    public native void enableColor(final long pointer);

    /**
     * Call to native code to disable color.
     *
     * @param pointer Native pointer value.
     */
    public native void disableColor(final long pointer);

    /**
     * Call to native code to create a new unit.
     *
     * @param pointer Native pointer value.
     * @return The new unit pointer value.
     */
    public native long createUnit(final long pointer);

    /**
     * Call to native code to enable alpha transparency.
     *
     * @param pointer Native pointer value.
     */
    public native void setAlphaTransparency(final long pointer);

    /**
     * Call to native code to enable color transparency.
     *
     * @param pointer Native pointer value.
     */
    public native void setColorTransparency(final long pointer);

    /**
     * Call to native code to set the diffuse color.
     *
     * @param pointer Native pointer value.
     * @param red     Red value.
     * @param green   Green value.
     * @param blue    Blue value.
     * @param alpha   Alpha value.
     */
    public native void setDiffuse(final long pointer, final float red, final float green, final float blue, final float alpha);

    /**
     * Call to native code to set the ambient color.
     *
     * @param pointer Native pointer value.
     * @param red     Red value.
     * @param green   Green value.
     * @param blue    Blue value.
     */
    public native void setAmbient(final long pointer, final float red, final float green, final float blue);

    /**
     * Call to native code to disable lights affecting this material pass.
     *
     * @param pointer Native pointer value.
     */
    public native void disableLight(final long pointer);

    /**
     * Set the blend operation to apply to this pass.
     *
     * @param pointer        Native pointer value.
     * @param blendOperation 0 is add, 1 subtract, 2 reverse subtract, 3 min, 4 max.
     */
    public native void blend(final long pointer, final int blendOperation);

    /**
     * Set the emissive color in native code.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param red     Emissive red value.
     * @param green   Emissive green value.
     * @param blue    Emissive blue value.
     */
    public native void setEmissive(final long pointer, final float red, final float green, final float blue);

    /**
     * Set a complex blend effect.
     *
     * @param pointerAddress Pointer address to the native Ogre::Pass.
     * @param blend1         First blend effect to apply.
     * @param blend2         Second blend effect to apply.
     */
    public native void complexBlend(final long pointerAddress, final int blend1, final int blend2);

    /**
     * Enable or disable depth write.
     *
     * @param address Pointer address to the native Ogre::Pass.
     * @param enabled <code>true</code> to enable, <code>false</code> to disable.
     */
    public native void setDepthWrite(final long address, final boolean enabled);

    /**
     * Set the alpha rejection.
     *
     * @param address Pointer address to the native Ogre::Pass.
     * @param value   Alpha value for pixel, between 0 and 255 but for hardware compatibility, max should be 128.
     */
    public native void setAlphaRejection(final long address, final int value);

    /**
     * Get a unit from its index.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param index   Unit index.
     * @return The found unit pointer.
     */
    public native long getUnit(final long pointer, final int index);

    /**
     * Set a shader vertex program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Vertex program name.
     */
    public native void setVertexProgram(final long pointer, final String name);

    /**
     * Set a shader fragment program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Fragment program name.
     */
    public native void setFragmentProgram(final long pointer, final String name);

    /**
     * Set a parameter to a fragment program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Parameter name.
     * @param v1 Parameter red.
     * @param v2 Parameter green.
     * @param v3 Parameter blue.
     * @param v4 Parameter alpha.
     */
    public native void setFragmentProgramParameterColor(final long pointer, final String name, final float v1, final float v2, final float v3, final float v4);

    /**
     * Set a parameter to a fragment program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Parameter name.
     * @param value  Parameter value.
     */
    public native void setFragmentProgramParameterFloat(final long pointer, final String name, final float value);

    /**
     * Set a parameter to a fragment program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Parameter name.
     * @param v1 Parameter value 1.
     * @param v2 Parameter value 2.
     */
    public native void setFragmentProgramParameterFloat2(final long pointer, final String name, final float v1, final float v2);


    /**
     * Set a parameter to a fragment program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Parameter name.
     * @param v1 Parameter value 1.
     * @param v2 Parameter value 2.
     * @param v3 Parameter value 3.
     */
    public native void setFragmentProgramParameterFloat3(final long pointer, final String name, final float v1, final float v2, final float v3);


    /**
     * Set a parameter to a fragment program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Parameter name.
     * @param v1 Parameter value 1.
     * @param v2 Parameter value 2.
     * @param v3 Parameter value 3.
     * @param v4 Parameter value 4.
     */
    public native void setFragmentProgramParameterFloat4(final long pointer, final String name, final float v1, final float v2, final float v3, final float v4);

    /**
     * Set an automatic parameter to a fragment program.
     *
     * @param pointerAddress Pointer address to the native Ogre::Pass.
     * @param name           Parameter name.
     * @param constant       Automatic parameter enum value.
     */
    public native void setFragmentProgramParameterAuto(final long pointerAddress, final String name, final int constant);

    /**
     * Set an automatic parameter to a fragment program.
     *
     * @param pointerAddress Pointer address to the native Ogre::Pass.
     * @param name           Parameter name.
     * @param constant       Automatic parameter enum value.
     * @param param          Additional parameter.
     */
    public native void setFragmentProgramParameterAutoP(final long pointerAddress, final String name, final int constant, final int param);

    /**
     * Set a parameter to a vertex program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Parameter name.
     * @param v1 Parameter red.
     * @param v2 Parameter green.
     * @param v3 Parameter blue.
     * @param v4 Parameter alpha.
     */
    public native void setVertexProgramParameterColor(final long pointer, final String name, final float v1, final float v2, final float v3, final float v4);

    /**
     * Set a parameter to a vertex program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Parameter name.
     * @param value  Parameter value.
     */
    public native void setVertexProgramParameterFloat(final long pointer, final String name, final float value);

    /**
     * Set a parameter to a vertex program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Parameter name.
     * @param v1 Parameter value 1.
     * @param v2 Parameter value 2.
     */
    public native void setVertexProgramParameterFloat2(final long pointer, final String name, final float v1, final float v2);


    /**
     * Set a parameter to a vertex program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Parameter name.
     * @param v1 Parameter value 1.
     * @param v2 Parameter value 2.
     * @param v3 Parameter value 3.
     */
    public native void setVertexProgramParameterFloat3(final long pointer, final String name, final float v1, final float v2, final float v3);


    /**
     * Set a parameter to a vertex program.
     *
     * @param pointer Pointer address to the native Ogre::Pass.
     * @param name    Parameter name.
     * @param v1 Parameter value 1.
     * @param v2 Parameter value 2.
     * @param v3 Parameter value 3.
     * @param v4 Parameter value 4.
     */
    public native void setVertexProgramParameterFloat4(final long pointer, final String name, final float v1, final float v2, final float v3, final float v4);


    /**
     * Set an automatic parameter to a vertex program.
     *
     * @param pointerAddress Pointer address to the native Ogre::Pass.
     * @param name           Parameter name.
     * @param constant       Automatic parameter enum value.
     */
    public native void setVertexProgramParameterAuto(final long pointerAddress, final String name, final int constant);

    /**
     * Set an automatic parameter to a vertex program.
     *
     * @param pointerAddress Pointer address to the native Ogre::Pass.
     * @param name           Parameter name.
     * @param constant       Automatic parameter enum value.
     * @param param          Additional parameter.
     */
    public native void setVertexProgramParameterAutoP(final long pointerAddress, final String name, final int constant, final int param);

}
