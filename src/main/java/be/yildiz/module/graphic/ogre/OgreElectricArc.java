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

import be.yildiz.module.graphic.ElectricArc;
import be.yildiz.module.graphic.Material;
import be.yildiz.module.graphic.PointLight;
import be.yildizgames.common.geometry.Point3D;
import be.yildizgames.common.nativeresources.Native;
import be.yildizgames.common.nativeresources.NativePointer;

/**
 * Ogre implementation for ElectricArc.
 *
 * @author Grégory Van den Borre
 */
final class OgreElectricArc extends ElectricArc implements Native {

    /**
     * Native pointer.
     */
    private final NativePointer pointer;

    /**
     * Full constructor.
     *
     * @param pointer Native pointer.
     * @param start   Arc origin.
     * @param end     Arc end.
     */
    OgreElectricArc(final NativePointer pointer, final Point3D start, final Point3D end) {
        super(start, end);
        this.pointer = pointer;
    }

    @Override
    public ElectricArc setMaterial(final Material material) {
        this.setMaterial(this.pointer.getPointerAddress(), OgreMaterial.class.cast(material).getPointer().getPointerAddress());
        return this;
    }

    @Override
    public ElectricArc addLight(final PointLight light) {
        this.addLight(this.pointer.getPointerAddress(), OgrePointLight.class.cast(light).getPointer().getPointerAddress());
        return this;
    }

    @Override
    public ElectricArc setCeil(final int ceil) {
        this.setCeil(this.pointer.getPointerAddress(), ceil);
        return this;
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
     * Set the material in native code.
     *
     * @param pointer  Native pointer address.
     * @param material Material to set.
     */
    private native void setMaterial(final long pointer, final long material);

    /**
     * Set the ceil in native code.
     *
     * @param pointer Native pointer address.
     * @param ceil    Ceil value.
     */
    private native void setCeil(final long pointer, final int ceil);

    /**
     * Add a blinking light.
     *
     * @param pointer      Native pointer address.
     * @param lightPointer Native light pointer address.
     */
    private native void addLight(final long pointer, final long lightPointer);

}
