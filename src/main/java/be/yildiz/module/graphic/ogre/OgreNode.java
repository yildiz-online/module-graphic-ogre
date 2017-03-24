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

import be.yildiz.common.id.EntityId;
import be.yildiz.common.nativeresources.Native;
import be.yildiz.common.nativeresources.NativePointer;
import be.yildiz.common.vector.Point3D;
import be.yildiz.common.vector.Quaternion;
import be.yildiz.module.graphic.Node;

/**
 * Java part for the yz::Node.
 *
 * @author Grégory Van den Borre
 */
public final class OgreNode extends Node implements Native {

    /**
     * Pointer address to the associated yz::Node.
     */
    private final NativePointer pointer;

    /**
     * Name specified in native code.
     */
    private final String name;

    /**
     * Full constructor.
     *
     * @param pointerAddress Address to the native object.
     */
    OgreNode(final NativePointer pointerAddress, final OgreNode parent) {
        super(parent);
        this.pointer = pointerAddress;
        this.name = this.getName(this.pointer.getPointerAddress());
    }

    /**
     * Full constructor.
     *
     * @param pointerAddress Address to the native object.
     */
    OgreNode(final NativePointer pointerAddress, final EntityId id, final OgreNode parent) {
        super(id, parent);
        this.pointer = pointerAddress;
        this.name = this.getName(this.pointer.getPointerAddress());
    }

    /**
     * Delete the node and free its resources.
     */
    protected void deleteImpl() {
        this.delete(this.pointer.getPointerAddress());
        this.pointer.delete();
    }

    /**
     * @return The current object position from the native code.
     */
    @Override
    public Point3D getPosition() {
        return Point3D.xyz(this.getPosition(this.pointer.getPointerAddress()));
    }

    @Override
    public void setPosition(final Point3D position) {
        this.setPosition(this.pointer.getPointerAddress(), position.x, position.y, position.z);
    }

    @Override
    public void scale(final float scale) {
        this.scale(this.pointer.getPointerAddress(), scale, scale, scale);
    }

    @Override
    public void scale(final float scaleX, final float scaleY, final float scaleZ) {
        this.scale(this.pointer.getPointerAddress(), scaleX, scaleY, scaleZ);
    }

    @Override
    public Point3D translate(final float moveX, final float moveY, final float moveZ) {
        return Point3D.xyz(this.translate(this.pointer.getPointerAddress(), moveX, moveY, moveZ));
    }

    @Override
    public void setDirection(final float dirX, final float dirY, final float dirZ) {
        this.setDirection(this.pointer.getPointerAddress(), dirX, dirY, dirZ);
    }

    @Override
    public Point3D getDirection() {
        return Point3D.xyz(this.getDirection(this.pointer.getPointerAddress()));
    }

    @Override
    public Point3D getWorldDirection() {
        return Point3D.xyz(this.getWorldDirection(this.pointer.getPointerAddress()));
    }

    @Override
    public void show() {
        this.show(this.pointer.getPointerAddress());
    }

    @Override
    public void hide() {
        this.hide(this.pointer.getPointerAddress());
    }

    @Override
    public Point3D rotate(final float yaw, final float pitch) {
        float[] v = this.rotate(this.pointer.getPointerAddress(), yaw, pitch);
        return Point3D.xyz(v);
    }

    @Override
    public void rotate(final float x, final float y, final float z, final float w) {
        this.rotateQuaternion(this.pointer.getPointerAddress(), x, y, z, w);
    }

    /**
     * Create a new node child of this one.
     *
     * @return A node attached to this node, its position and direction will be relative to this node direction and position..
     */
    public OgreNode createChild() {
        final long address = this.createChild(this.pointer.getPointerAddress());
        return new OgreNode(NativePointer.create(address), this);
    }

    @Override
    public Quaternion getOrientation() {
        float[] v = this.getOrientation(this.pointer.getPointerAddress());
        return new Quaternion(v[0], v[1], v[2], v[3]);
    }

    @Override
    public NativePointer getPointer() {
        return pointer;
    }

    public String getName() {
        return name;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + ((this.name == null) ? 0 : this.name.hashCode());
        result = prime * result + ((this.pointer == null) ? 0 : this.pointer.hashCode());
        return result;
    }

    @Override
    public boolean equals(final Object obj) {
        if (this == obj) {
            return true;
        }
        if (!(obj instanceof OgreNode)) {
            return false;
        }
        OgreNode other = (OgreNode) obj;
        if (!this.name.equals(other.name)) {
            return false;
        }
        return this.pointer.equals(other.pointer);
    }

    @Override
    public String toString() {
        return "Ogre node: pointer:" + this.pointer;
    }

    /**
     * Set the object visible in native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     */
    private native void show(final long pointerAddress);

    /**
     * Set the object invisible in native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     */
    private native void hide(final long pointerAddress);

    /**
     * Rotate the object in native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     * @param yaw            Rotation X value.
     * @param pitch          Rotation Y value.
     * @return The new node direction value.
     */
    private native float[] rotate(final long pointerAddress, final float yaw, final float pitch);

    /**
     * Rotate the object in native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     * @param quatX          Rotation X value.
     * @param quatY          Rotation Y value.
     * @param quatZ          Rotation Z value.
     * @param quatW          Rotation W value.
     */
    private native void rotateQuaternion(final long pointerAddress, final float quatX, final float quatY, final float quatZ, final float quatW);

    /**
     * Delete the object in native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     */
    private native void delete(final long pointerAddress);

    /**
     * Set the object position in native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     * @param posX           Position X value.
     * @param posY           Position Y value.
     * @param posZ           Position Z value.
     */
    private native void setPosition(final long pointerAddress, final float posX, final float posY, final float posZ);

    /**
     * Retrieve the object position in native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     * @return An array (0 = X, 1 = Y, 2 = Z).
     */
    private native float[] getPosition(final long pointerAddress);

    /**
     * Translate the object in native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     * @param moveX          Translation X value.
     * @param moveY          Translation Y value.
     * @param moveZ          Translation Z value.
     * @return The new object position.
     */
    private native float[] translate(final long pointerAddress, final float moveX, final float moveY, final float moveZ);

    /**
     * Set the object direction in native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     * @param dirX           Direction X value.
     * @param dirY           Direction Y value.
     * @param dirZ           Direction Z value.
     */
    private native void setDirection(final long pointerAddress, final float dirX, final float dirY, final float dirZ);

    /**
     * Create a Movable object child in native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     * @return Address to the native child yz::Node.
     */
    private native long createChild(final long pointerAddress);

    /**
     * Scale the object in native code.
     *
     * @param pointerAddress Address to the native object.
     * @param scaleX         Width scale factor.
     * @param scaleY         Height scale factor.
     * @param scaleZ         Depth scale factor.
     */
    private native void scale(final long pointerAddress, final float scaleX, final float scaleY, final float scaleZ);

    /**
     * Attach this node to an other in native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     * @param other          Address to the other native yz::Node.
     */
    private native void attachToNode(final long pointerAddress, final long other);

    /**
     * Retrieve the node name in native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     * @return The result of Ogre::SceneNode::getName()
     */
    private native String getName(final long pointerAddress);

    /**
     * Retrieve the current direction from native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     * @return An array containing X, Y and Z direction coordinates.
     */
    private native float[] getDirection(final long pointerAddress);

    /**
     * Retrieve the current direction associated to the parents from native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     * @return An array containing X, Y and Z direction coordinates.
     */
    private native float[] getWorldDirection(final long pointerAddress);

    /**
     * Retrieve the current orientation from native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     * @return An array containing W, X, Y and Z orientation coordinates.
     */
    private native float[] getOrientation(final long pointerAddress);

    @Override
    protected void attachToImpl(final Node other) {
        this.attachToNode(this.pointer.getPointerAddress(), ((OgreNode) other).pointer.getPointerAddress());
    }

    @Override
    protected void detachFromParent() {
        this.detachFromParent(this.pointer.getPointerAddress());
    }

    private native void detachFromParent(final long pointerAddress);
}
