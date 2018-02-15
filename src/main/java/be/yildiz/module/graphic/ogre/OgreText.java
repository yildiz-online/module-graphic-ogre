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

package be.yildiz.module.graphic.ogre;

import be.yildiz.module.color.Color;
import be.yildiz.module.coordinate.BaseCoordinate;
import be.yildiz.module.graphic.Font;
import be.yildiz.module.graphic.gui.AbstractTextElement;
import be.yildiz.module.graphic.gui.Element;
import be.yildiz.module.graphic.gui.GuiContainer;
import be.yildizgames.common.jni.NativePointer;

/**
 * Ogre implementation for a text element.
 *
 * @author Grégory Van Den Borre
 */
final class OgreText extends AbstractTextElement {

    /**
     * Pointer for the native object.
     */
    private final NativePointer pointer;

    /**
     * Current text color.
     */
    private Color color;

    /**
     * Full constructor.
     *
     * @param coordinates Text size and position.
     * @param font        Text font.
     * @param container   Container holding the text.
     */
    OgreText(final BaseCoordinate coordinates, final Font font, final GuiContainer container) {
        super(coordinates, font);
        this.pointer = NativePointer.create(this.constructor(OgreGuiContainer.class.cast(container).getPointer().getPointerAddress(), coordinates.width, coordinates.height, coordinates.left, coordinates.top,
                OgreFont.class.cast(font).getPointer().getPointerAddress(), font.size, this.getName()));
        this.setColor(font.color);
        this.hide();
        this.show();
    }

    @Override
    protected void setColor(final Color color) {
        if (!color.equals(this.color)) {
            this.setColor(this.pointer.getPointerAddress(), color.normalizedRed, color.normalizedGreen, color.normalizedBlue, color.normalizedAlpha);
            this.color = color;
        }
    }

    @Override
    protected void setTextImpl(final String text) {
        this.setText(this.pointer.getPointerAddress(), text);
    }

    @Override
    protected void hideImpl() {
        this.hide(this.pointer.getPointerAddress());
    }

    @Override
    protected void showImpl() {
        this.show(this.pointer.getPointerAddress());
    }

    @Override
    protected Element setPositionImpl(final int left, final int top) {
        this.setPosition(this.pointer.getPointerAddress(), left, top);
        return this;
    }

    @Override
    protected void setSizeImpl(final int width, final int height) {
    }

    @Override
    protected void setFontImpl(final Font font) {
        this.setFont(this.pointer.getPointerAddress(), OgreFont.class.cast(font).getPointer().getPointerAddress(), font.size);
    }

    @Override
    protected void delete() {
        this.delete(this.pointer.getPointerAddress());
        this.pointer.delete();
        this.removeFromRegisterer();
    }

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
    private native long constructor(final long container, final float width, final float height, final float left, final float top, final long font, final float fontHeight, final String name);

    /**
     * Update the text in native code.
     *
     * @param pointer Address to the native object.
     * @param text    Text to print.
     */
    private native void setText(final long pointer, final String text);

    /**
     * Show the text element in native code.
     *
     * @param pointer Address to the native object.
     */
    private native void show(final long pointer);

    /**
     * Hide the text element in native code.
     *
     * @param pointer Address to the native object.
     */
    private native void hide(final long pointer);

    /**
     * Set the text position in native code.
     *
     * @param pointer Address to the native object.
     * @param left    Text element Left position from the container left border.
     * @param top     Text element top position from the container top border.
     */
    private native void setPosition(final long pointer, final float left, final float top);

    /**
     * Set the text font in native code.
     *
     * @param pointer    Address to the native object.
     * @param font       Font to use with the text.
     * @param fontHeight Size of the font to use.
     */
    private native void setFont(final long pointer, final long font, final float fontHeight);

    /**
     * Set the text color in native code.
     *
     * @param pointerAddress Address to the native object.
     * @param red            Red value to set.
     * @param green          Green value to set.
     * @param blue           Blue value to set.
     * @param alpha          Alpha value to set.
     */
    private native void setColor(final long pointerAddress, final float red, final float green, final float blue, final float alpha);

    /**
     * Delete the object in native code.
     *
     * @param pointerAddress Address to the native object.
     */
    private native void delete(final long pointerAddress);
}
