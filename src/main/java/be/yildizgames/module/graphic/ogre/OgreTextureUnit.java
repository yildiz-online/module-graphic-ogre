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

package be.yildizgames.module.graphic.ogre;

import be.yildizgames.module.color.Color;
import be.yildizgames.module.graphic.material.TextureUnit;
import be.yildizgames.common.jni.Native;
import be.yildizgames.common.jni.NativePointer;

/**
 * Ogre implementation for a texture unit.
 *
 * @author Grégory Van den Borre
 */
final class OgreTextureUnit extends TextureUnit implements Native {

    /**
     * Pointer for the native object.
     */
    private final NativePointer pointer;

    /**
     * Full constructor.
     *
     * @param address Address to the associated native object.
     */
    OgreTextureUnit(final long address) {
        super();
        this.pointer = NativePointer.create(address);
        this.setTextureFilter(this.pointer.getPointerAddress(), TextureFilter.ANISOTROPIC.getValue());
    }

    @Override
    public void scroll(final float x, final float y) {
        this.scroll(this.pointer.getPointerAddress(), x, y);
    }

    @Override
    public void setColorOperation(final ColorOperation op) {
        this.setColorOperation(this.pointer.getPointerAddress(), op.ordinal());
    }

    @Override
    public void setColorOperationEx(final LayerBlendOperationEx op, final LayerBlendSource src1, final LayerBlendSource src2) {
        this.setColorOperationEx(this.pointer.getPointerAddress(), op.ordinal(), src1.ordinal(), src2.ordinal());
    }

    @Override
    public void setAlphaOperation(final LayerBlendOperationEx source1, final LayerBlendSource texture, final LayerBlendSource texture2) {
        this.setAlphaOperation(this.pointer.getPointerAddress(), source1.ordinal(), texture.ordinal(), texture2.ordinal());

    }

    @Override
    public void setColorOperationEx(final LayerBlendOperationEx source1, final LayerBlendSource manual, final LayerBlendSource current, final Color color) {
        this.setColorOperationExManual(this.pointer.getPointerAddress(), source1.ordinal(), manual.ordinal(), current.ordinal(), color.normalizedRed, color.normalizedGreen, color.normalizedBlue);
    }

    @Override
    public TextureUnit setTextureAnimated(final String basePath, final int numberOfFrames, final int duration) {
        this.setTextureAnimated(this.pointer.getPointerAddress(), basePath, numberOfFrames, duration);
        return this;
    }

    @Override
    protected void setTextureImpl(final String path) {
        this.setTexture(this.pointer.getPointerAddress(), path);
    }

    @Override
    protected void setScaleImpl(final float xScale, final float yScale) {
        this.setScale(this.pointer.getPointerAddress(), xScale, yScale);
    }

    @Override
    public void setCoordinateSet(final int set) {
        this.setCoordinateSet(this.pointer.getPointerAddress(), set);
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
     * Set the texture in native code.
     *
     * @param pointerAddress Address to the native object.
     * @param path           Path to the image file.
     */
    private native void setTexture(final long pointerAddress, final String path);

    /**
     * Scale the unit in native code.
     *
     * @param pointerAddress Address to the native object.
     * @param xScale         Scale width value.
     * @param yScale         Scale height value.
     */
    private native void setScale(final long pointerAddress, final float xScale, final float yScale);

    /**
     * Set the color operation ont the unit in native code.
     *
     * @param pointerAddress Address to the native object.
     * @param ordinal        Value matching the enum.
     */
    private native void setColorOperation(final long pointerAddress, final int ordinal);

    /**
     * Set the scroll values for this unit in native code.
     *
     * @param pointerAddress Address to the native object.
     * @param x              X scroll speed.
     * @param y              Y scroll speed.
     */
    private native void scroll(final long pointerAddress, final float x, final float y);

    /**
     * Set the color operation.
     *
     * @param address   Ogre::UnitState* pointer address.
     * @param operation Operation enum value.
     * @param source1   Source type enum value.
     * @param source2   Second source type enum value.
     */
    private native void setColorOperationEx(final long address, final int operation, final int source1, final int source2);

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
    private native void setColorOperationExManual(final long address, final int operation, final int source1, final int source2, final float normalizedRed, final float normalizedGreen,
                                                  final float normalizedBlue);

    /**
     * Set an animated texture.
     *
     * @param pointer  Ogre::UnitState* pointer address.
     * @param path     Path of the texture file.
     * @param number   Number of frames.
     * @param duration Animation duration.
     */
    private native void setTextureAnimated(final long pointer, final String path, final int number, final int duration);

    /**
     * Set a texture filter.
     *
     * @param pointer Ogre::UnitState* pointer address.
     * @param value   Filter enum value.
     */
    private native void setTextureFilter(final long pointer, final int value);

    /**
     * Set an alpha operation.
     *
     * @param address   Ogre::UnitState* pointer address.
     * @param operation Operation enum value.
     * @param source1   Source type enum value.
     * @param source2   Second source type enum value.
     */
    private native void setAlphaOperation(final long address, final int operation, final int source1, final int source2);

    private native void setCoordinateSet(final long pointer, final int set);

}
