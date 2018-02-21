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
public class JniMovableText {

    /**
     * Create the object.
     *
     * @param nodePointer Pointer for the associated node.
     * @param name        Object unique name.
     * @param text        Object text to display.
     * @param font        Object text font.
     * @param textSize    Font size.
     * @return The pointer address of the created object.
     */
    public native long constructor(final long nodePointer, final String name, final String text, final long font, final float textSize);

    /**
     * Set the text color.
     *
     * @param address Pointer address of the native object.
     * @param red     Color red value.
     * @param green   Color green value.
     * @param blue    Color blue value.
     * @param alpha   Color alpha value.
     */
    public native void setTextColor(final long address, final float red, final float green, final float blue, final float alpha);

    /**
     * Set the text alignment.
     *
     * @param pointerAddress Pointer address of the native object.
     * @param h              Horizontal alignment.
     * @param v              Vertical alignment.
     */
    public native void setTextAlignement(final long pointerAddress, final int h, final int v);

    /**
     * Set the text offset from the node.
     *
     * @param address Pointer address of the native object.
     * @param x       Offset X value.
     * @param y       Offset Y value.
     * @param z       Offset Z value.
     */
    public native void setTextOffset(final long address, final float x, final float y, final float z);


}
