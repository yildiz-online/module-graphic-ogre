/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *  
 * Copyright (c) 2018 Grégory Van den Borre
 *
 * More infos available: https://www.yildiz-games.be
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
public class JniPointLight {

    /**
     * Set light color in native code.
     *
     * @param address Address of the native yz::PointLight pointer.
     * @param r       Red value.
     * @param g       Green value.
     * @param b       Blue value.
     */
    public native void setColor(final long address, final float r, final float g, final float b);

    /**
     * Set the light position in native code.
     *
     * @param pointerAddress Address of the native yz::PointLight pointer.
     * @param x              New X position.
     * @param y              New Y position.
     * @param z              New Z position.
     */
    public native void setPosition(final long pointerAddress, final float x, final float y, final float z);

    /**
     * Delete the object in native code.
     *
     * @param pointerAddress Address of the native yz::PointLight pointer.
     */
    public native void delete(final long pointerAddress);

    /**
     * Set the light attenuation in native code.
     *
     * @param pointerAddress Address of the native yz::PointLight pointer.
     * @param range          Light range.
     * @param constant       Constant value.
     * @param linear         Linear value.
     * @param quadratic      Quadratic value.
     */
    public native void setAttenuation(final long pointerAddress, final float range, final float constant, final float linear,
                                       final float quadratic);

    /**
     * Enable debug display in native code.
     *
     * @param pointerAddress Address of the native yz::PointLight pointer.
     */
    public native void setDebug(final long pointerAddress);
}
