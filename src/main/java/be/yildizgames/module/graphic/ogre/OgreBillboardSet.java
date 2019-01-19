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

import be.yildizgames.common.gameobject.Movable;
import be.yildizgames.common.geometry.Point3D;
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
public final class OgreBillboardSet implements BillboardSet, Native {

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
        super();
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
        this.jni.remove(this.pointer.getPointerAddress(), OgreBillboard.class.cast(b).getPointer().getPointerAddress());
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
    public void detachFromParent() {
        this.node.detachFromParent();
    }

    @Override
    public void setPosition(float posX, float posY, float posZ) {
        this.node.setPosition(posX, posY, posZ);
    }

    @Override
    public void setDirection(float dirX, float dirY, float dirZ) {
        this.node.setDirection(dirX, dirY, dirZ);
    }

    @Override
    public void addOptionalChild(Movable child) {
        this.node.addOptionalChild(child);
    }

    @Override
    public void addChild(Movable child) {
        this.node.addChild(child);
    }

    @Override
    public void removeChild(Movable child) {
        this.node.removeChild(child);
    }

    @Override
    public Movable getInternal() {
        return this.node;
    }

    @Override
    public final void attachTo(final Movable other) {
        this.node.attachTo(other);
    }

    @Override
    public final void attachToOptional(final Movable other) {
        this.node.attachToOptional(other);
    }

    @Override
    public final Point3D getPosition() {
        return this.node.getPosition();
    }

    @Override
    public final void setPosition(final Point3D position) {
        this.node.setPosition(position);
    }

    @Override
    public final Point3D getAbsolutePosition() {
        return this.node.getAbsolutePosition();
    }

    @Override
    public final Point3D getDirection() {
        return this.node.getDirection();
    }

    @Override
    public final void setDirection(final Point3D direction) {
        this.node.setDirection(direction);
    }

    @Override
    public final Point3D getAbsoluteDirection() {
        return this.node.getAbsoluteDirection();
    }

    @Override
    public final void delete() {
        this.node.delete();
    }

    //public final Node getNode() {
    //    return node;
    //}

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
