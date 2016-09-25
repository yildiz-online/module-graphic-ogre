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

import be.yildiz.common.gameobject.Movable;
import be.yildiz.common.nativeresources.Native;
import be.yildiz.common.nativeresources.NativePointer;
import be.yildiz.common.vector.Point3D;
import be.yildiz.module.graphic.Billboard;
import be.yildiz.module.graphic.BillboardSet;
import lombok.Getter;

/**
 * Ogre implementation for a BillBoardSet.
 *
 * @author Grégory Van den Borre
 */
final class OgreBillboardSet extends BillboardSet implements Native {

    /**
     * Pointer address to the native code object.
     */
    @Getter
    private final NativePointer pointer;

    /**
     * Associated node.
     */
    private OgreNode node;

    /**
     * Full constructor.
     *
     * @param pointer Pointer address to the associated native object.
     * @param node    Associated node.
     */
    OgreBillboardSet(final NativePointer pointer, final OgreNode node) {
        super(node);
        this.pointer = pointer;
        this.node = node;
        this.attachToNode(this.pointer.getPointerAddress(), node.getPointer().getPointerAddress());
    }

    @Override
    public OgreBillboard createBillboard() {
        return new OgreBillboard(NativePointer.create(this.createBillboard(this.pointer.getPointerAddress())));
    }

    @Override
    public void removeBillboard(final Billboard b) {
        this.remove(this.pointer.getPointerAddress(), OgreBillboard.class.cast(b).getPointer().getPointerAddress());
    }

    @Override
    public void setSize(final float width, final float height) {
        this.setSize(this.pointer.getPointerAddress(), width, height);
    }

    @Override
    protected void hideImpl() {
        this.hide(this.pointer.getPointerAddress());
    }

    @Override
    protected void showImpl() {
        this.show(this.pointer.getPointerAddress());
    }

    /**
     * Create a new Billboard in native code.
     *
     * @param pointer The billboard set native object pointer address.
     * @return The newly built billboard native object pointer address.
     */
    private native long createBillboard(final long pointer);

    /**
     * Set the default size in native code.
     *
     * @param address The Ogre::BillboardSet pointer address.
     * @param width   New default width in pixel.
     * @param height  New default height in pixels.
     */
    private native void setSize(final long address, final float width, final float height);

    /**
     * Remove a billboard from the set.
     *
     * @param pointer          The Ogre::BillboardSet pointer address.
     * @param billboardPointer The Ogre::Billboard to remove pointer address.
     */
    private native void remove(final long pointer, final long billboardPointer);

    /**
     * Attach the set to a node.
     *
     * @param pointer     Set pointer address.
     * @param nodePointer Node address.
     */
    private native void attachToNode(final long pointer, final long nodePointer);

    /**
     * Set the set visible.
     *
     * @param pointerAddress Set pointer address.
     */
    private native void show(final long pointerAddress);

    /**
     * Set the set invisible.
     *
     * @param pointerAddress Set pointer address.
     */
    private native void hide(final long pointerAddress);

    @Override
    public void detach(Movable other) {
        // TODO Auto-generated method stub

    }

    @Override
    public void addChild(Movable other) {
        // TODO Auto-generated method stub

    }

    @Override
    public void setAbsolutePosition(Point3D pos) {
        // TODO Auto-generated method stub

    }
}
