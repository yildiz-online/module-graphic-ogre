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

import be.yildiz.common.nativeresources.NativePointer;
import be.yildiz.common.vector.Point3D;
import be.yildiz.module.graphic.SpotLight;

/**
 * Ogre implementation for a SpotLight.
 *
 * @author Grégory Van den Borre
 */
final class OgreSpotLight extends SpotLight {

    /**
     * Pointer address to the native code yz::SpotLight.
     */
    private final NativePointer pointer;

    /**
     * Full constructor.
     *
     * @param pointerAddress Pointer address to the associated native object.
     * @param name           Light unique name.
     * @param position       Light position.
     * @param direction      Light direction.
     */
    OgreSpotLight(final NativePointer pointerAddress, final String name, final Point3D position, final Point3D direction) {
        super(name, position, direction);
        this.pointer = pointerAddress;
    }

    @Override
    protected void setDirectionImpl(final Point3D direction) {
        this.setDirection(this.pointer.getPointerAddress(), direction.x, direction.y, direction.z);
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

    /**
     * Set the light position in native code.
     *
     * @param pointerAddress Address of the native yz::SpotLight pointer.
     * @param x              New X position.
     * @param y              New Y position.
     * @param z              New Z position.
     */
    private native void setPosition(final long pointerAddress, final float x, final float y, final float z);

    /**
     * Set the light direction in native code.
     *
     * @param pointerAddress Address of the native yz::SpotLight pointer.
     * @param x              New X direction.
     * @param y              New Y direction.
     * @param z              New Z direction.
     */
    private native void setDirection(final long pointerAddress, final float x, final float y, final float z);

    /**
     * Delete light direction in native code.
     *
     * @param pointerAddress Address of the native yz::SpotLight pointer.
     */
    private native void delete(final long pointerAddress);
}
