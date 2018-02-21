/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 * Copyright (c) 2018 Grégory Van den Borre
 *
 * More infos available: https://www.yildiz-games.be
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
public class JniShader {

    /**
     * Delete the object in native code.
     *
     * @param address Address of the native object.
     */
    public native void delete(final long address);

    /**
     * Create the shader in native code.
     *
     * @param name Shader name.
     * @param path Path to the file.
     * @return The pointer address of the created object.
     */
    public native long createFragmentShader(final String name, final String path);

    /**
     * Create the shader in native code.
     *
     * @param name Shader name.
     * @param path Path to the file.
     * @return The pointer address of the created object.
     */
    public native long createVertexShader(final String name, final String path);

    /**
     * Set parameter to pass to the shader, those parameters are meant to specify to the graphic engine how to load the shader(entry point, profile...), those are not meant to be used as shader
     * function parameter..
     *
     * @param pointer Native object pointer address.
     * @param name    Parameter name.
     * @param value   Parameter value.
     */
    public native void setParameter(final long pointer, final String name, final String value);

    public native void load(final long pointer);
}
