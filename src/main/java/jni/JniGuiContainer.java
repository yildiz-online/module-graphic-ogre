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
public class JniGuiContainer {

    /**
     * Build the object in native code.
     *
     * @param material Material to use as background.
     * @param name     Container name, must be unique.
     * @param width    Container width value.
     * @param height   Container height value.
     * @return The native address of the newly built object.
     */
    public native long constructor(final long material, final String name, final float width, final float height);

    /**
     * Build the object in native code.
     *
     * @param material      Name of the material to use as background.
     * @param name          Container name, must be unique.
     * @param width         Container width value.
     * @param height        Container height value.
     * @param parentAddress Parent GUI container pointer.
     * @return The native address of the newly built object.
     */
    public native long constructorParent(final long material, final String name, final float width, final float height, final long parentAddress);

    /**
     * Set the container size in native code.
     *
     * @param pointer Address to the native object.
     * @param width   New container width.
     * @param height  New container height.
     */
    public native void setSize(final long pointer, final float width, final float height);

    /**
     * Zoom the container in native code.
     *
     * @param pointer Address to the native object.
     * @param factor  Zoom factor.
     */
    public native void zoom(final long pointer, final float factor);

    /**
     * Retrieve an element from a position in native code.
     *
     * @param pointer Address to the native object.
     * @param posX    Position to check X value.
     * @param posY    Position to check Y value.
     * @return The name of the found element.
     */
    public native String getElement(final long pointer, final float posX, final float posY);

    /**
     * Show the container in native code.
     *
     * @param pointer Address to the native object.
     */
    public native void show(final long pointer);

    /**
     * Hide the container system in native code.
     *
     * @param pointer Address to the native object.
     */
    public native void hide(final long pointer);

    /**
     * Set the container position in native code.
     *
     * @param pointer Address to the native object.
     * @param posX    container X position.
     * @param posY    container Y position.
     */
    public native void setPosition(final long pointer, final float posX, final float posY);

    /**
     * Set the container depth position in native code.
     *
     * @param pointer Address to the native object.
     * @param depth   Depth value(Must be under 650).
     */
    public native void setZ(final long pointer, final short depth);

    /**
     * Set a background material to the container in native code.
     *
     * @param address  Address to the native object.
     * @param material Material.
     */
    public native void setMaterial(final long address, final long material);

    /**
     * Translate this container children.
     *
     * @param pointerAddress Address to the native object.
     * @param left          Horizontal translation, in pixels.
     * @param top           Vertical translation, in pixels.
     */
    public native void addChildrenPosition(final long pointerAddress, final int left, final int top);
}
