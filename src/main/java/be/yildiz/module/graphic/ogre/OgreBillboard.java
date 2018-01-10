/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 * Copyright (c) 2017 Grégory Van den Borre
 *
 * More infos available: https://www.yildiz-games.be
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without
 * limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT  HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  SOFTWARE.
 */

package be.yildiz.module.graphic.ogre;

import be.yildiz.common.Color;
import be.yildiz.common.vector.Point3D;
import be.yildiz.module.graphic.Billboard;
import be.yildizgames.common.nativeresources.Native;
import be.yildizgames.common.nativeresources.NativePointer;

/**
 * Ogre implementation for a BillBoard.
 *
 * @author Grégory Van den Borre
 */
final class OgreBillboard extends Billboard implements Native {

    /**
     * Pointer address to the native code object.
     */
    private final NativePointer pointer;

    public OgreBillboard(NativePointer pointer) {
        super();
        this.pointer = pointer;
    }

    @Override
    protected void setSizeImpl(final float width, final float height) {
        this.setSize(this.pointer.getPointerAddress(), width, height);
    }

    @Override
    protected void setPositionImpl(final Point3D position) {
        this.setPosition(this.pointer.getPointerAddress(), position.x, position.y, position.z);
    }

    @Override
    public void setColor(final Color color) {
        this.setColor(this.pointer.getPointerAddress(), color.normalizedRed, color.normalizedGreen, color.normalizedBlue, color.normalizedAlpha);
    }

    @Override
    public void delete() {
        this.delete(this.pointer.getPointerAddress());
        this.pointer.delete();
    }

    @Override
    public NativePointer getPointer() {
        return pointer;
    }

    /**
     * Delete the object in native code.
     *
     * @param address Address of the native object.
     */
    private native void delete(final long address);

    /**
     * Set the billboard position in native code.
     *
     * @param pointerAddress Native object pointer address.
     * @param positionX      New position x value.
     * @param positionY      New position y value.
     * @param positionZ      New position z value.
     */
    private native void setPosition(final long pointerAddress, final float positionX, final float positionY, final float positionZ);

    /**
     * Set the billboard size in native code.
     *
     * @param pointerAddress Native object pointer address.
     * @param width          New billboard width value.
     * @param height         New billboard height value.
     */
    private native void setSize(final long pointerAddress, final float width, final float height);

    /**
     * Set the billboard color.
     *
     * @param pointer Ogre::Billboard* pointer address.
     * @param red     Red color value.
     * @param green   Green color value.
     * @param blue    Blue color value.
     * @param alpha   Alpha value.
     */
    private native void setColor(final long pointer, final float red, final float green, final float blue, final float alpha);

}
