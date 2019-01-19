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

import be.yildizgames.module.graphic.shader.Shader;
import be.yildizgames.common.jni.Native;
import be.yildizgames.common.jni.NativePointer;
import jni.JniShader;

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

    private final JniShader jni = new JniShader();

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
        if(type == ShaderType.VERTEX) {
            this.pointer = NativePointer.create(this.jni.createVertexShader(name, path));
        } else {
            this.pointer = NativePointer.create(this.jni.createFragmentShader(name, path));
        }
        this.jni.setParameter(this.pointer.getPointerAddress(), "entry_point", entry);
        this.jni.setParameter(this.pointer.getPointerAddress(), "profiles", profile.getName());
        this.jni.load(this.pointer.getPointerAddress());
    }

    @Override
    public void delete() {
        this.jni.delete(this.pointer.getPointerAddress());
        this.pointer.delete();
    }

    @Override
    public NativePointer getPointer() {
        return pointer;
    }
}
