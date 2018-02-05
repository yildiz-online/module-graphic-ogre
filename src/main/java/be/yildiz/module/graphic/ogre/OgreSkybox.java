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

import be.yildiz.module.graphic.Skybox;
import be.yildizgames.common.nativeresources.NativePointer;

/**
 * Ogre skybox implementation.
 *
 * @author Grégory Van Den Borre
 */
final class OgreSkybox extends Skybox {

    /**
     * Pointer address to the native object.
     */
    private final NativePointer pointer;

    /**
     * Full constructor.
     *
     * @param name Sky box name, must be unique.
     * @param path Path to the resource to load.
     */
    OgreSkybox(final String name, final String path) {
        super(name, path);
        final long address = this.createSkybox(name, path);
        this.pointer = NativePointer.create(address);
    }

    @Override
    protected void loadImpl() {
    }

    /**
     * Create the native object.
     *
     * @param name Skybox unique name.
     * @param path Files to use.
     * @return The native object pointer address.
     */
    private native long createSkybox(final String name, final String path);
}
