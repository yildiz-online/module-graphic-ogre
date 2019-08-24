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

import be.yildizgames.common.jni.Native;
import be.yildizgames.common.jni.NativePointer;
import be.yildizgames.module.graphic.billboard.Billboard;
import be.yildizgames.module.graphic.billboard.BillboardSet;
import jni.JniBillboardSet;

/**
 * Ogre implementation for a BillBoardSet.
 *
 * @author Grégory Van den Borre
 */
public final class OgreBillboardSet extends OgreMovableObject implements BillboardSet, Native {

    /**
     * Pointer address to the native code object.
     */
    private final NativePointer pointer;

    /**
     * Associated node.
     */
    private final OgreNode node;

    private final JniBillboardSet jni = new JniBillboardSet();

    private boolean visible;

    /**
     * Full constructor.
     *
     * @param pointer Pointer address to the associated native object.
     * @param node    Associated node.
     */
    public OgreBillboardSet(final NativePointer pointer, final OgreNode node) {
        super(node);
        this.pointer = pointer;
        this.visible = true;
        this.node = node;
        this.jni.attachToNode(this.pointer.getPointerAddress(), node.getPointer().getPointerAddress());
    }

    @Override
    public OgreBillboard createBillboard() {
        return new OgreBillboard(NativePointer.create(this.jni.createBillboard(this.pointer.getPointerAddress())));
    }

    @Override
    public void removeBillboard(final Billboard b) {
        this.jni.remove(this.pointer.getPointerAddress(), ((OgreBillboard) b).getPointer().getPointerAddress());
    }

    @Override
    public void setSize(final float width, final float height) {
        this.jni.setSize(this.pointer.getPointerAddress(), width, height);
    }

    @Override
    public NativePointer getPointer() {
        return pointer;
    }

    @Override
    public final void delete() {
        this.node.delete();
    }

    /**
     * Set the object visible.
     */
    public final void show() {
        if (!this.visible) {
            this.jni.show(this.pointer.getPointerAddress());
            this.visible = true;
        }
    }

    /**
     * Set the object invisible.
     */
    public final void hide() {
        if (this.visible) {
            this.jni.hide(this.pointer.getPointerAddress());
            this.visible = false;
        }
    }

    /**
     * @return <code>true</code> if object is currently visible.
     */
    public final boolean isVisible() {
        return this.visible;
    }
}
