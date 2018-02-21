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

package be.yildizgames.module.graphic.ogre;

import be.yildizgames.common.gameobject.Movable;
import be.yildizgames.common.geometry.Point3D;
import be.yildizgames.common.jni.Native;
import be.yildizgames.common.jni.NativePointer;
import jni.JniNode;

/**
 * @author Grégory Van den Borre
 */
public class OgreNodeMovable extends OgreNodeBase {

    /**
     * Pointer address to the associated yz::Node.
     */
    private final NativePointer pointer;

    private final JniNode nodeNative = new JniNode();

    /**
     * Full constructor.
     *
     * @param pointerAddress Address to the native object.
     */
    public OgreNodeMovable(final NativePointer pointerAddress, final Movable parent) {
        super(pointerAddress, parent);
        this.pointer = pointerAddress;
        this.parent = parent;
     }

    @Override
    public void setPosition(float posX, float posY, float posZ) {
        this.nodeNative.setPosition(this.pointer.getPointerAddress(), posX, posY, posZ);
    }

    @Override
    public void setPosition(final Point3D position) {
        this.nodeNative.setPosition(this.pointer.getPointerAddress(), position.x, position.y, position.z);
    }

    @Override
    public final void rotate(final float x, final float y, final float z, final float w) {
        this.nodeNative.rotateQuaternion(this.pointer.getPointerAddress(), x, y, z, w);
    }

    @Override
    public Point3D rotate(final float yaw, final float pitch) {
        float[] v = this.nodeNative.rotate(this.pointer.getPointerAddress(), yaw, pitch);
        return Point3D.valueOf(v[0], v[1], v[2]);
    }

    @Override
    public Point3D translate(final float moveX, final float moveY, final float moveZ) {
        float[] v = this.nodeNative.translate(this.pointer.getPointerAddress(), moveX, moveY, moveZ);
        return Point3D.valueOf(v[0], v[1], v[2]);
    }

    @Override
    public void setDirection(final float dirX, final float dirY, final float dirZ) {
        this.nodeNative.setDirection(this.pointer.getPointerAddress(), dirX, dirY, dirZ);
    }

    @Override
    public final void attachToOptional(final Movable other) {
        if(!other.equals(this.parent)) {
            this.detachFromParent();
            this.nodeNative.attachTo(this.pointer.getPointerAddress(), Native.class.cast(other.getInternal()).getPointer().getPointerAddress());
            this.parent = other;
            this.parent.addOptionalChild(this);
        }
    }

    @Override
    public final void attachTo(final Movable other) {
        if(!other.equals(this.parent)) {
            this.detachFromParent();
            this.nodeNative.attachTo(this.pointer.getPointerAddress(), Native.class.cast(other.getInternal()).getPointer().getPointerAddress());
            this.parent = other;
            this.parent.addChild(this);
        }
    }

    @Override
    public void scale(final float scaleX, final float scaleY, final float scaleZ) {
        this.nodeNative.scale(this.pointer.getPointerAddress(), scaleX, scaleY, scaleZ);
    }
}
