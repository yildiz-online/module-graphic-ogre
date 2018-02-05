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

import be.yildiz.module.graphic.DirectionalLight;
import be.yildizgames.common.geometry.Point3D;
import be.yildizgames.common.nativeresources.Native;
import be.yildizgames.common.nativeresources.NativePointer;

/**
 * Ogre implementation for directional light.
 *
 * @author Grégory Van den Borre
 */
final class OgreDirectionalLight extends DirectionalLight implements Native {

    /**
     * Pointer address to the native code object.
     */
    private final NativePointer pointer;

    /**
     * Full constructor.
     *
     * @param pointer   Pointer to the native object.
     * @param name      Light name, must be unique.
     * @param direction Light direction.
     */
    OgreDirectionalLight(final NativePointer pointer, final String name, final Point3D direction) {
        super(name, direction);
        this.pointer = pointer;
    }

    @Override
    protected void setPositionImpl(final Point3D position) {
        this.setPosition(this.pointer.getPointerAddress(), position.x, position.y, position.z);
    }

    @Override
    protected void deleteImpl() {
        this.delete(this.pointer.getPointerAddress());
        this.pointer.delete();
    }

    @Override
    public NativePointer getPointer() {
        return pointer;
    }

    /**
     * Set the light position in native code.
     *
     * @param pointer Address of the native yz::DirectionalLight pointer.
     * @param x       New X position.
     * @param y       New Y position.
     * @param z       New Z position.
     */
    private native void setPosition(final long pointer, final float x, final float y, final float z);

    /**
     * Delete the object in native code.
     *
     * @param pointerAddress Address of the native yz::DirectionalLight pointer.
     */
    private native void delete(final long pointerAddress);

}
