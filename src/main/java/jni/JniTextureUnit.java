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
public class JniTextureUnit {

    /**
     * Delete the object in native code.
     *
     * @param address Address of the native object.
     */
    public native void delete(final long address);

    /**
     * Set the texture in native code.
     *
     * @param pointerAddress Address to the native object.
     * @param path           Path to the image file.
     */
    public native void setTexture(final long pointerAddress, final String path);

    /**
     * Scale the unit in native code.
     *
     * @param pointerAddress Address to the native object.
     * @param xScale         Scale width value.
     * @param yScale         Scale height value.
     */
    public native void setScale(final long pointerAddress, final float xScale, final float yScale);

    /**
     * Set the color operation ont the unit in native code.
     *
     * @param pointerAddress Address to the native object.
     * @param ordinal        Value matching the enum.
     */
    public native void setColorOperation(final long pointerAddress, final int ordinal);

    /**
     * Set the scroll values for this unit in native code.
     *
     * @param pointerAddress Address to the native object.
     * @param x              X scroll speed.
     * @param y              Y scroll speed.
     */
    public native void scroll(final long pointerAddress, final float x, final float y);

    /**
     * Set the color operation.
     *
     * @param address   Ogre::UnitState* pointer address.
     * @param operation Operation enum value.
     * @param source1   Source type enum value.
     * @param source2   Second source type enum value.
     */
    public native void setColorOperationEx(final long address, final int operation, final int source1, final int source2);

    /**
     * Set a manual color operation.
     *
     * @param address         Ogre::UnitState* pointer address.
     * @param operation       Operation enum value.
     * @param source1         Source type enum value.
     * @param source2         Second source type enum value.
     * @param normalizedRed   Red value.
     * @param normalizedGreen Green value.
     * @param normalizedBlue  Blue value.
     */
    public native void setColorOperationExManual(final long address, final int operation, final int source1, final int source2, final float normalizedRed, final float normalizedGreen,
                                                  final float normalizedBlue);

    /**
     * Set an animated texture.
     *
     * @param pointer  Ogre::UnitState* pointer address.
     * @param path     Path of the texture file.
     * @param number   Number of frames.
     * @param duration Animation duration.
     */
    public native void setTextureAnimated(final long pointer, final String path, final int number, final int duration);

    /**
     * Set a texture filter.
     *
     * @param pointer Ogre::UnitState* pointer address.
     * @param value   Filter enum value.
     */
    public native void setTextureFilter(final long pointer, final int value);

    /**
     * Set an alpha operation.
     *
     * @param address   Ogre::UnitState* pointer address.
     * @param operation Operation enum value.
     * @param source1   Source type enum value.
     * @param source2   Second source type enum value.
     */
    public native void setAlphaOperation(final long address, final int operation, final int source1, final int source2);

    public native void setCoordinateSet(final long pointer, final int set);
}
