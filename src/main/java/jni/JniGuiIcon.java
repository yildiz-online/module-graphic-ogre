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
public class JniGuiIcon {

    /**
     * Set the object hidden native code.
     *
     * @param pointerAddress Address to the native yz::GuiIcon*.
     */
    public native void hide(final long pointerAddress);

    /**
     * Set the object visible native code.
     *
     * @param pointerAddress Address to the native yz::GuiIcon*.
     */
    public native void show(final long pointerAddress);

    /**
     * Update the size in native code.
     *
     * @param pointerAddress Address to the native yz::GuiIcon*.
     * @param width          New object width.
     * @param height         New object height.
     */
    public native void setSize(final long pointerAddress, final float width, final float height);

    /**
     * Update the material in native code.
     *
     * @param pointerAddress Address to the native yz::GuiIcon*.
     * @param material       Material to set.
     */
    public native void setTexture(final long pointerAddress, final long material);

    /**
     * Delete the object in native code.
     *
     * @param pointerAddress Address to the native yz::GuiIcon*.
     */
    public native void delete(final long pointerAddress);

    /**
     * Set the position in native code.
     *
     * @param pointerAddress Address to the native yz::GuiIcon*.
     * @param left           X position.
     * @param top            Y position.
     */
    public native void setPosition(final long pointerAddress, final float left, final float top);

    /**
     * Build the object in native code.
     *
     * @param container Container holding the icon.
     * @param name      Name of the icon, must be unique.
     * @param material  Material to assign to the icon.
     * @param width     Width of the icon, in pixels.
     * @param height    Height of the icon, in pixels
     * @param left      Icon left position from its parent left border.
     * @param top       Icon top position from its parent top border.
     * @return A pointer to the newly built object.
     */
    public native long constructor(final long container, final String name, final long material, final float width, final float height, final float left, final float top);

    /**
     * Retrieve the Z value from native code.
     *
     * @param pointerAddress Address to the native yz::GuiIcon*.
     * @return The object Z value.
     */
    public native int getZ(final long pointerAddress);

    /**
     * Retrieve the parent container name from native code.
     *
     * @param pointerAddress Address to the native yz::GuiIcon*.
     * @return The name of the parent container.
     */
    public native String getParentName(final long pointerAddress);
}
