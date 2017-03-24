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

import be.yildiz.common.nativeresources.Native;
import be.yildiz.common.nativeresources.NativePointer;
import be.yildiz.module.graphic.Shader;

/**
 * Ogre implementation for a shader.
 *
 * @author Grégory Van den Borre
 */
final class OgreShader extends Shader implements Native {

    /**
     * Native pointer.
     */
    private final NativePointer pointer;

    /**
     * Full constructor.
     *
     * @param name    Shader name.
     * @param path    Shader file path.
     * @param entry   Main function name.
     * @param type    Shader type.
     * @param profile Profile to set.
     */
    OgreShader(final String name, final String path, final String entry, final ShaderType type, final ShaderProfile profile) {
        super(name, type);
        this.pointer = NativePointer.create(this.createShader(name, path, type.getValue()));
        this.setParameter(this.pointer.getPointerAddress(), "entry_point", entry);
        this.setParameter(this.pointer.getPointerAddress(), "profiles", profile.getName());
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
     * Create the shader in native code.
     *
     * @param name Shader name.
     * @param path Path to the file.
     * @param type Shader type.
     * @return The pointer address of the created object.
     */
    private native long createShader(final String name, final String path, final int type);

    /**
     * Set parameter to pass to the shader, those parameters are meant to specify to the graphic engine how to load the shader(entry point, profile...), those are not meant to be used as shader
     * function parameter..
     *
     * @param pointer Native object pointer address.
     * @param name    Parameter name.
     * @param value   Parameter value.
     */
    private native void setParameter(final long pointer, final String name, final String value);
}
