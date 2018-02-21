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
public class JniBillboardSet {

    /**
     * Create a new Billboard in native code.
     *
     * @param pointer The billboard set native object pointer address.
     * @return The newly built billboard native object pointer address.
     */
    public native long createBillboard(final long pointer);

    /**
     * Set the default size in native code.
     *
     * @param address The Ogre::BillboardSet pointer address.
     * @param width   New default width in pixel.
     * @param height  New default height in pixels.
     */
    public native void setSize(final long address, final float width, final float height);

    /**
     * Remove a billboard from the set.
     *
     * @param pointer          The Ogre::BillboardSet pointer address.
     * @param billboardPointer The Ogre::Billboard to remove pointer address.
     */
    public native void remove(final long pointer, final long billboardPointer);

    /**
     * Attach the set to a node.
     *
     * @param pointer     Set pointer address.
     * @param nodePointer Node address.
     */
    public native void attachToNode(final long pointer, final long nodePointer);

    /**
     * Set the set visible.
     *
     * @param pointerAddress Set pointer address.
     */
    public native void show(final long pointerAddress);

    /**
     * Set the set invisible.
     *
     * @param pointerAddress Set pointer address.
     */
    public native void hide(final long pointerAddress);
}
