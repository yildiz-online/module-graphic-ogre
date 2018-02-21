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
public class JniGuiText {

    /**
     * Build a new text element in native code.
     *
     * @param container  Container holding the element.
     * @param width      Text element width.
     * @param height     Text element height.
     * @param left       Text element Left position from the container left border.
     * @param top        Text element top position from the container top border.
     * @param font       Font to use with the text.
     * @param fontHeight Size of the font to use.
     * @param name       Name of the element, must be unique.
     * @return The pointer address to the newly built object.
     */
    public native long constructor(final long container, final float width, final float height, final float left, final float top, final long font, final float fontHeight, final String name);

    /**
     * Update the text in native code.
     *
     * @param pointer Address to the native object.
     * @param text    Text to print.
     */
    public native void setText(final long pointer, final String text);

    /**
     * Show the text element in native code.
     *
     * @param pointer Address to the native object.
     */
    public native void show(final long pointer);

    /**
     * Hide the text element in native code.
     *
     * @param pointer Address to the native object.
     */
    public native void hide(final long pointer);

    /**
     * Set the text position in native code.
     *
     * @param pointer Address to the native object.
     * @param left    Text element Left position from the container left border.
     * @param top     Text element top position from the container top border.
     */
    public native void setPosition(final long pointer, final float left, final float top);

    /**
     * Set the text font in native code.
     *
     * @param pointer    Address to the native object.
     * @param font       Font to use with the text.
     * @param fontHeight Size of the font to use.
     */
    public native void setFont(final long pointer, final long font, final float fontHeight);

    /**
     * Set the text color in native code.
     *
     * @param pointerAddress Address to the native object.
     * @param red            Red value to set.
     * @param green          Green value to set.
     * @param blue           Blue value to set.
     * @param alpha          Alpha value to set.
     */
    public native void setColor(final long pointerAddress, final float red, final float green, final float blue, final float alpha);

    /**
     * Delete the object in native code.
     *
     * @param pointerAddress Address to the native object.
     */
    public native void delete(final long pointerAddress);
}
