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
public class JniParticleSystem {

    /**
     * Create an emitter in native code.
     *
     * @param pointer Pointer address to the native object.
     * @return The emitter pointer address.
     */
    public native long createEmitter(final long pointer);

    /**
     * Create a color affector in native code.
     *
     * @param pointer Address to the native object.
     * @return The color affector pointer address.
     */
    public native long createColorAffector(final long pointer);

    /**
     * Create a force affector in native code.
     *
     * @param pointer Address to the native object.
     * @return The force affector pointer address.
     */
    public native long createForceAffector(final long pointer);

    /**
     * Create a scale affector in native code.
     *
     * @param pointer Address to the native object.
     * @return The scale affector pointer address.
     */
    public native long createScaleAffector(final long pointer);

    /**
     * Set the particle size in native code.
     *
     * @param pointer Address to the native object.
     * @param width   Particle width.
     * @param height  Particle height.
     */
    public native void setSize(final long pointer, final float width, final float height);

    /**
     * Set the particle material in native code.
     *
     * @param pointer  Address to the native object.
     * @param material Material to use.
     */
    public native void setMaterial(final long pointer, final long material);

    /**
     * Set the particle quota in native code.
     *
     * @param pointer Address to the native object.
     * @param quota   Quota to set.
     */
    public native void setQuota(final long pointer, final int quota);

    /**
     * Set the particle billboard orientation in native code.
     *
     * @param pointer         Address to the native object.
     * @param orientationType Orientation type.
     */
    public native void setParticleOrientation(final long pointer, final int orientationType);

    /**
     * Set the billboard origin.
     *
     * @param pointerAddress Address to the native object.
     * @param value          Origin enum value.
     */
    public native void setBillboardOrigin(final long pointerAddress, final int value);

    /**
     * Attach this object to a node in native code.
     *
     * @param pointer     Address to the native object.
     * @param nodePointer Address to the native node object.
     */
    public native void attachToNode(final long pointer, final long nodePointer);

    /**
     * Keep particle in local space.
     *
     * @param pointer Address to the native object.
     * @param keep    <code>true</code> to keep.
     */
    public native void keepInLocalSpace(final long pointer, final boolean keep);
}
