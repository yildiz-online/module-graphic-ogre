//        This file is part of the Yildiz-Online project, licenced under the MIT License
//        (MIT)
//
//        Copyright (c) 2016 Grégory Van den Borre
//
//        More infos available: http://yildiz.bitbucket.org
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
//        of this software and associated documentation files (the "Software"), to deal
//        in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
//        furnished to do so, subject to the following conditions:
//
//        The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
//        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//        SOFTWARE.

package be.yildiz.module.graphic.ogre;

import be.yildiz.common.Color;
import be.yildiz.common.gameobject.Movable;
import be.yildiz.common.nativeresources.NativePointer;
import be.yildiz.common.vector.Point3D;
import be.yildiz.module.graphic.Font;
import be.yildiz.module.graphic.MovableText;

/**
 * Ogre implementation for a movable text.
 *
 * @author Grégory Van den Borre
 */
final class OgreMovableText extends MovableText {

    /**
     * Pointer for the native object.
     */
    private final NativePointer pointer;

    /**
     * Associated node.
     */
    private final OgreNode node;

    /**
     * Full constructor.
     *
     * @param node Associated node.
     * @param name Unique name.
     * @param text Text to print.
     * @param font Font to use.
     */
    OgreMovableText(final OgreNode node, final String name, final String text, final Font font) {
        super(node);
        this.node = node;
        long address = this.constructor(this.node.getPointer().getPointerAddress(), name, text, OgreFont.class.cast(font).getPointer().getPointerAddress(), font.size);
        this.pointer = NativePointer.create(address);
    }

    @Override
    public void setTextColor(final Color color) {
        this.setTextColor(this.pointer.getPointerAddress(), color.normalizedRed, color.normalizedGreen, color.normalizedBlue, color.normalizedAlpha);
    }

    @Override
    public void setTextOffset(final Point3D offset) {
        this.setTextOffset(this.pointer.getPointerAddress(), offset.x, offset.y, offset.z);
    }

    @Override
    public void setTextAlignement(final Horizontal h, final Vertical v) {
        // Note The enum values must be in same order as in native code.
        // FIXME do not use ordinal
        this.setTextAlignement(this.pointer.getPointerAddress(), h.ordinal(), v.ordinal());
    }

    @Override
    public void showImpl() {
        this.node.show();
    }

    @Override
    public void hideImpl() {
        this.node.hide();
    }

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
    private native long constructor(final long nodePointer, final String name, final String text, final long font, final float textSize);

    /**
     * Set the text color.
     *
     * @param address Pointer address of the native object.
     * @param red     Color red value.
     * @param green   Color green value.
     * @param blue    Color blue value.
     * @param alpha   Color alpha value.
     */
    private native void setTextColor(final long address, final float red, final float green, final float blue, final float alpha);

    /**
     * Set the text alignment.
     *
     * @param pointerAddress Pointer address of the native object.
     * @param h              Horizontal alignment.
     * @param v              Vertical alignment.
     */
    private native void setTextAlignement(final long pointerAddress, final int h, final int v);

    /**
     * Set the text offset from the node.
     *
     * @param address Pointer address of the native object.
     * @param x       Offset X value.
     * @param y       Offset Y value.
     * @param z       Offset Z value.
     */
    private native void setTextOffset(final long address, final float x, final float y, final float z);

    @Override
    public void detach(Movable other) {
        // TODO Auto-generated method stub

    }

    @Override
    public void addChild(Movable other) {
        // TODO Auto-generated method stub

    }

    @Override
    public void setAbsolutePosition(Point3D pos) {
        // TODO Auto-generated method stub

    }
}
