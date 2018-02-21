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

import be.yildizgames.common.jni.NativePointer;
import be.yildizgames.module.color.Color;
import be.yildizgames.module.coordinate.BaseCoordinate;
import be.yildizgames.module.graphic.Font;
import be.yildizgames.module.graphic.gui.container.Container;
import be.yildizgames.module.graphic.gui.element.AbstractTextElement;
import be.yildizgames.module.graphic.gui.internal.Element;
import jni.JniGuiText;

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

    private final JniGuiText jni = new JniGuiText();

    /**
     * Full constructor.
     *
     * @param coordinates Text size and position.
     * @param font        Text font.
     * @param container   Container holding the text.
     */
    OgreText(final BaseCoordinate coordinates, final Font font, final Container container) {
        super(coordinates, font);
        this.pointer = NativePointer.create(this.jni.constructor(OgreGuiContainer.class.cast(container).getPointer().getPointerAddress(), coordinates.width, coordinates.height, coordinates.left, coordinates.top,
                OgreFont.class.cast(font).getPointer().getPointerAddress(), font.size, this.getName()));
        this.setColor(font.color);
        this.hide();
        this.show();
    }

    @Override
    public void setColor(final Color color) {
        if (!color.equals(this.color)) {
            this.jni.setColor(this.pointer.getPointerAddress(), color.normalizedRed, color.normalizedGreen, color.normalizedBlue, color.normalizedAlpha);
            this.color = color;
        }
    }

    @Override
    protected void setTextImpl(final String text) {
        this.jni.setText(this.pointer.getPointerAddress(), text);
    }

    @Override
    protected void hideImpl() {
        this.jni.hide(this.pointer.getPointerAddress());
    }

    @Override
    protected void showImpl() {
        this.jni.show(this.pointer.getPointerAddress());
    }

    @Override
    protected Element setPositionImpl(final int left, final int top) {
        this.jni.setPosition(this.pointer.getPointerAddress(), left, top);
        return this;
    }

    @Override
    protected void setSizeImpl(final int width, final int height) {
    }

    @Override
    protected void setFontImpl(final Font font) {
        this.jni.setFont(this.pointer.getPointerAddress(), OgreFont.class.cast(font).getPointer().getPointerAddress(), font.size);
    }

    @Override
    public void delete() {
        this.jni.delete(this.pointer.getPointerAddress());
        this.pointer.delete();
        this.removeFromRegisterer();
    }
}
