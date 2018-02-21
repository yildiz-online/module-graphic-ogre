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

package jni;

/**
 * @author Grégory Van den Borre
 */
public class JniBillboard {

    /**
     * Delete the object in native code.
     *
     * @param address Address of the native object.
     */
    public native void delete(final long address);

    /**
     * Set the billboard position in native code.
     *
     * @param pointerAddress Native object pointer address.
     * @param positionX      New position x value.
     * @param positionY      New position y value.
     * @param positionZ      New position z value.
     */
    public native void setPosition(final long pointerAddress, final float positionX, final float positionY, final float positionZ);

    /**
     * Set the billboard size in native code.
     *
     * @param pointerAddress Native object pointer address.
     * @param width          New billboard width value.
     * @param height         New billboard height value.
     */
    public native void setSize(final long pointerAddress, final float width, final float height);

    /**
     * Set the billboard color.
     *
     * @param pointer Ogre::Billboard* pointer address.
     * @param red     Red color value.
     * @param green   Green color value.
     * @param blue    Blue color value.
     * @param alpha   Alpha value.
     */
    public native void setColor(final long pointer, final float red, final float green, final float blue, final float alpha);

}
