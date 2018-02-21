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

package jni;

/**
 * @author Grégory Van den Borre
 */
public class JniFont {

    /**
     * Delete the object in native code.
     *
     * @param address Address of the native object.
     */
    public native void delete(final long address);

    /**
     * Create a font in the native code.
     *
     * @param name Font name, must be unique.
     * @param path Font file path.
     * @param size Font height.
     * @return The pointer address to the native object.
     */
    public native long createFont(final String name, final String path, final float size);

    /**
     * Compute the width, in pixel for each char.
     *
     * @param pointerAddress Address value to the native object.
     * @return An array containing the char width, the place of the char in the array is its ASCII value.(i.e. width of 'A' is array[65]);
     */
    public native float[] computeCharSize(final long pointerAddress);
}
