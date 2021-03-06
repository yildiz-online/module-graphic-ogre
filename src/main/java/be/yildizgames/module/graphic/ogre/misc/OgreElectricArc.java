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

package be.yildizgames.module.graphic.ogre.misc;

import be.yildizgames.common.geometry.Point3D;
import be.yildizgames.common.jni.Native;
import be.yildizgames.common.jni.NativePointer;
import be.yildizgames.module.graphic.light.PointLight;
import be.yildizgames.module.graphic.material.Material;
import be.yildizgames.module.graphic.misc.ElectricArc;
import be.yildizgames.module.graphic.ogre.OgreMaterial;
import be.yildizgames.module.graphic.ogre.light.OgrePointLight;
import jni.JniElectricArc;

/**
 * Ogre implementation for ElectricArc.
 *
 * @author Grégory Van den Borre
 */
public final class OgreElectricArc extends ElectricArc implements Native {

    /**
     * Native pointer.
     */
    private final NativePointer pointer;

    private final JniElectricArc jni = new JniElectricArc();

    /**
     * Full constructor.
     *
     * @param pointer Native pointer.
     * @param start   Arc origin.
     * @param end     Arc end.
     */
    public OgreElectricArc(final NativePointer pointer, final Point3D start, final Point3D end) {
        super(start, end);
        this.pointer = pointer;
    }

    @Override
    public ElectricArc setMaterial(final Material material) {
        this.jni.setMaterial(this.pointer.getPointerAddress(), ((OgreMaterial) material).getPointer().getPointerAddress());
        return this;
    }

    @Override
    public ElectricArc addLight(final PointLight light) {
        this.jni.addLight(this.pointer.getPointerAddress(), ((OgrePointLight) light).getPointer().getPointerAddress());
        return this;
    }

    @Override
    public ElectricArc setCeil(final int ceil) {
        this.jni.setCeil(this.pointer.getPointerAddress(), ceil);
        return this;
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
