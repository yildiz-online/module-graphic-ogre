/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 *  Copyright (c) 2019 Grégory Van den Borre
 *
 *  More infos available: https://engine.yildiz-games.be
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

import be.yildizgames.common.jni.Native;
import be.yildizgames.common.jni.NativePointer;
import be.yildizgames.module.color.Color;
import be.yildizgames.module.graphic.Font;
import jni.JniFont;

import java.util.Objects;

/**
 * Ogre implementation for a font.
 *
 * @author Grégory Van Den Borre
 */
final class OgreFont extends Font implements Native {

    /**
     * Pointer address to the native object.
     */
    private final NativePointer pointer;

    private final JniFont jni = new JniFont();

    /**
     * Full constructor.
     *
     * @param name Font name, must be unique.
     * @param path Path to the file to load the font.
     * @param size Font height.
     */
    OgreFont(final String name, final String path, final int size, final Color color) {
        super(name, size, color);
        this.pointer = NativePointer.create(this.jni.createFont(this.getName(), path, this.size));
    }

    /**
     * Get the char width value from the native code and set it to the object.
     */
    @Override
    protected void loadImpl() {
        float[] widthArray = this.jni.computeCharSize(this.pointer.getPointerAddress());
        widthArray[32] = widthArray[32] * 0.5f;
        this.setCharWidth(widthArray);
    }

    @Override
    public void delete() {
        this.jni.delete(this.pointer.getPointerAddress());
        this.pointer.delete();
        this.unregister();
    }

    @Override
    public NativePointer getPointer() {
        return this.pointer;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        if (!super.equals(o)) {
            return false;
        }
        OgreFont ogreFont = (OgreFont) o;
        return pointer.equals(ogreFont.pointer);
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), pointer);
    }
}
