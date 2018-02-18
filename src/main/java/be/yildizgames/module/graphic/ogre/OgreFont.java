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
import be.yildizgames.module.graphic.Font;
import be.yildizgames.common.jni.Native;
import be.yildizgames.common.jni.NativePointer;

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

    /**
     * Full constructor.
     *
     * @param name Font name, must be unique.
     * @param path Path to the file to load the font.
     * @param size Font height.
     */
    OgreFont(final String name, final String path, final int size, final Color color) {
        super(name, size, color);
        this.pointer = NativePointer.create(this.createFont(this.getName(), path, this.size));
    }

    /**
     * Get the char width value from the native code and set it to the object.
     */
    @Override
    protected void loadImpl() {
        float[] widthArray = this.computeCharSize(this.pointer.getPointerAddress());
        widthArray[32] = widthArray[32] * 0.5f;
        this.setCharWidth(widthArray);
    }

    @Override
    public void delete() {
        this.delete(this.pointer.getPointerAddress());
        this.pointer.delete();
        // FIXME remove from registerer
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
     * Create a font in the native code.
     *
     * @param name Font name, must be unique.
     * @param path Font file path.
     * @param size Font height.
     * @return The pointer address to the native object.
     */
    private native long createFont(final String name, final String path, final float size);

    /**
     * Compute the width, in pixel for each char.
     *
     * @param pointerAddress Address value to the native object.
     * @return An array containing the char width, the place of the char in the array is its ASCII value.(i.e. width of 'A' is array[65]);
     */
    private native float[] computeCharSize(final long pointerAddress);
}
