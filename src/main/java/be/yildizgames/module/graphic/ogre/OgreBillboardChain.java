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

import be.yildizgames.common.geometry.Point3D;
import be.yildizgames.common.jni.Native;
import be.yildizgames.common.jni.NativePointer;
import be.yildizgames.module.graphic.billboard.BillboardChain;
import be.yildizgames.module.graphic.material.Material;
import jni.JniBillboardChain;

/**
 * Ogre implementation for a BillboardChain.
 *
 * @author Grégory Van den Borre
 */
public final class OgreBillboardChain implements BillboardChain, Native {

    /**
     * Pointer address to the native code object.
     */
    private final NativePointer pointer;

    /**
     * Node used to move the chain.
     */
    private final OgreNode node;

    private final JniBillboardChain jni = new JniBillboardChain();

    /**
     * Full constructor.
     *
     * @param node Associated movable object.
     */
    public OgreBillboardChain(final OgreNode node) {
        super();
        this.pointer = NativePointer.create(this.jni.constructor(node.getName(), node.getPointer().getPointerAddress()));
        this.node = node;
    }

    @Override
    public void addElement(final Point3D pos, final float elementWidth) {
        this.jni.addElement(this.pointer.getPointerAddress(), pos.x, pos.y, pos.z, elementWidth);
    }

    @Override
    public void setElementPosition(final int listPosition, final Point3D pos) {
        this.jni.setElementPosition(this.pointer.getPointerAddress(), listPosition, pos.x, pos.y, pos.z);
    }

    @Override
    public void setMaterial(final Material material) {
        this.jni.setMaterial(this.pointer.getPointerAddress(), OgreMaterial.class.cast(material).getPointer().getPointerAddress());
    }

    @Override
    public void setPosition(final Point3D position) {
        this.node.setPosition(position);
    }

    @Override
    public void setPosition(final Point3D start, final Point3D end) {
        // FIXME implements

    }

    @Override
    public void delete() {
        this.jni.delete(this.pointer.getPointerAddress());
        this.pointer.delete();
    }

    @Override
    public void stop() {
        // TODO Auto-generated method stub
    }

    @Override
    public void start() {
        // TODO Auto-generated method stub
    }

    @Override
    public NativePointer getPointer() {
        return pointer;
    }
}
