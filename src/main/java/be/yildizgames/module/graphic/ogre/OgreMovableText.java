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

import be.yildizgames.common.gameobject.Movable;
import be.yildizgames.common.geometry.Point3D;
import be.yildizgames.common.jni.NativePointer;
import be.yildizgames.module.color.Color;
import be.yildizgames.module.graphic.Font;
import be.yildizgames.module.graphic.misc.MovableText;
import jni.JniMovableText;

/**
 * Ogre implementation for a movable text.
 *
 * @author Grégory Van den Borre
 */
public final class OgreMovableText extends MovableText {

    /**
     * Pointer for the native object.
     */
    private final NativePointer pointer;

    /**
     * Associated node.
     */
    private final OgreNodeBase node;

    private final JniMovableText jni = new JniMovableText();

    /**
     * Full constructor.
     *
     * @param node Associated node.
     * @param name Unique name.
     * @param text Text to print.
     * @param font Font to use.
     */
    public OgreMovableText(final OgreNodeBase node, final String name, final String text, final Font font) {
        super(node);
        this.node = node;
        long address = this.jni.constructor(this.node.getPointer().getPointerAddress(), name, text, OgreFont.class.cast(font).getPointer().getPointerAddress(), font.size);
        this.pointer = NativePointer.create(address);
    }

    @Override
    public void setTextColor(final Color color) {
        this.jni.setTextColor(this.pointer.getPointerAddress(), color.normalizedRed, color.normalizedGreen, color.normalizedBlue, color.normalizedAlpha);
    }

    @Override
    public void setTextOffset(final Point3D offset) {
        this.jni.setTextOffset(this.pointer.getPointerAddress(), offset.x, offset.y, offset.z);
    }

    @Override
    public void setTextAlignement(final Horizontal h, final Vertical v) {
        // Note The enum values must be in same order as in native code.
        // FIXME do not use ordinal
        this.jni.setTextAlignement(this.pointer.getPointerAddress(), h.ordinal(), v.ordinal());
    }

    @Override
    public void setPosition(float posX, float posY, float posZ) {
        this.node.setPosition(posX, posY, posZ);
    }

    @Override
    public void setDirection(float dirX, float dirY, float dirZ) {
        this.node.setDirection(dirX, dirY, dirZ);
    }

    @Override
    public void showImpl() {
        this.node.show();
    }

    @Override
    public void hideImpl() {
        this.node.hide();
    }

    @Override
    public void detachFromParent() {
        this.node.detachFromParent();
    }

    @Override
    public void addOptionalChild(Movable child) {
        this.node.addOptionalChild(child);
    }

    @Override
    public void addChild(Movable child) {
        this.node.addChild(child);
    }

    @Override
    public void removeChild(Movable child) {
        this.node.removeChild(child);
    }

    @Override
    public Movable getInternal() {
        return this.node;
    }
}
