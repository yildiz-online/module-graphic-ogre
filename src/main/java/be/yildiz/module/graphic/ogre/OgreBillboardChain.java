//        This file is part of the Yildiz-Online project, licenced under the MIT License
//        (MIT)
//
//        Copyright (c) 2016 Grégory Van den Borre
//
//        More infos available: http://yildiz.bitbucket.org
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
//        of this software and associated documentation files (the "Software"), to deal
//        in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
//        furnished to do so, subject to the following conditions:
//
//        The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
//        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//        SOFTWARE.

package be.yildiz.module.graphic.ogre;

import be.yildiz.common.nativeresources.Native;
import be.yildiz.common.nativeresources.NativePointer;
import be.yildiz.common.vector.Point3D;
import be.yildiz.module.graphic.BillboardChain;
import be.yildiz.module.graphic.Material;
import lombok.Getter;

/**
 * Ogre implementation for a BillboardChain.
 *
 * @author Grégory Van den Borre
 */
final class OgreBillboardChain implements BillboardChain, Native {

    /**
     * Pointer address to the native code object.
     */
    @Getter
    private final NativePointer pointer;

    /**
     * Node used to move the chain.
     */
    private final OgreNode node;

    /**
     * Full constructor.
     *
     * @param node Associated movable object.
     */
    OgreBillboardChain(final OgreNode node) {
        super();
        this.pointer = NativePointer.create(this.constructor(node.getName(), node.getPointer().getPointerAddress()));
        this.node = node;
    }

    @Override
    public void addElement(final Point3D pos, final float elementWidth) {
        this.addElement(this.pointer.getPointerAddress(), pos.x, pos.y, pos.z, elementWidth);
    }

    @Override
    public void setElementPosition(final int listPosition, final Point3D pos) {
        this.setElementPosition(this.pointer.getPointerAddress(), listPosition, pos.x, pos.y, pos.z);
    }

    @Override
    public void setMaterial(final Material material) {
        this.setMaterial(this.pointer.getPointerAddress(), OgreMaterial.class.cast(material).getPointer().getPointerAddress());
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
        this.delete(this.pointer.getPointerAddress());
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

    /**
     * Create the object in native code.
     *
     * @param nodePointer Pointer to the YZ::Node to attach wih this object.
     * @return The pointer address to the native object.
     */
    private native long constructor(final String name, final long nodePointer);

    /**
     * Add an element to the chain in native code.
     *
     * @param address      Native billboard chain pointer address.
     * @param xPosition    New element x position.
     * @param yPosition    New element y position.
     * @param zPosition    New element z position.
     * @param elementWidth New element width.
     */
    private native void addElement(final long address, final float xPosition, final float yPosition, final float zPosition, final float elementWidth);

    /**
     * Set the material in native code.
     *
     * @param pointer  Billboard chain native pointer address.
     * @param material Material to set.
     */
    private native void setMaterial(final long pointer, final long material);

    /**
     * Set the position of an element in native code.
     *
     * @param pointer      Billboard chain native pointer address.
     * @param listPosition Element position in the chain.
     * @param xPosition    Element x position.
     * @param yPosition    Element y position.
     * @param zPosition    Element z position.
     */
    private native void setElementPosition(final long pointer, final int listPosition, final float xPosition, final float yPosition, final float zPosition);

    /**
     * Delete the native object.
     *
     * @param pointer Billboard chain native pointer address.
     */
    private native void delete(final long pointer);
}
