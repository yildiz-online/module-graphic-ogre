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
public class JniLensFlare {

    /**
     * Delete the object in native code.
     *
     * @param address Address of the native object.
     */
    public native void delete(final long address);

    /**
     * Set the lens flare position in native code.
     *
     * @param pointerAddress Address of the native yz::LensFlare pointer.
     * @param x              New X position.
     * @param y              New Y position.
     * @param z              New Z position.
     */
    public native void setPosition(final long pointerAddress, final float x, final float y, final float z);

    /**
     * Set streak billboard size.
     *
     * @param pointerAddress Address of the native yz::LensFlare pointer.
     * @param w              Width in pixel.
     * @param h              Height in pixel.
     */
    public native void setStreakSize(final long pointerAddress, final float w, final float h);

    /**
     * Set light billboard size.
     *
     * @param pointerAddress Address of the native yz::LensFlare pointer.
     * @param w              Width in pixel.
     * @param h              Height in pixel.
     */
    public native void setLightSize(final long pointerAddress, final float w, final float h);
}
