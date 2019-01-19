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

package jni;

/**
 * @author Grégory Van den Borre
 */
public class JniNode {

    /**
     * Retrieve the node name in native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     * @return The result of Ogre::SceneNode::getName()
     */
    public native String getName(final long pointerAddress);

    /**
     * Set the object visible in native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     */
    public native void show(final long pointerAddress);

    /**
     * Set the object invisible in native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     */
    public native void hide(final long pointerAddress);

    /**
     * Retrieve the object position in native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     * @return An array (0 = X, 1 = Y, 2 = Z).
     */
    public native float[] getPosition(final long pointerAddress);

    /**
     * Set the object position in native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     * @param posX           Position X value.
     * @param posY           Position Y value.
     * @param posZ           Position Z value.
     */
    public native void setPosition(final long pointerAddress, final float posX, final float posY, final float posZ);

    /**
     * Retrieve the current direction from native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     * @return An array containing X, Y and Z direction coordinates.
     */
    public native float[] getDirection(final long pointerAddress);

    /**
     * Set the object direction in native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     * @param dirX           Direction X value.
     * @param dirY           Direction Y value.
     * @param dirZ           Direction Z value.
     */
    public native void setDirection(final long pointerAddress, final float dirX, final float dirY, final float dirZ);

    /**
     * Retrieve the current orientation from native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     * @return An array containing W, X, Y and Z orientation coordinates.
     */
    public native float[] getOrientation(final long pointerAddress);

    /**
     * Translate the object in native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     * @param moveX          Translation X value.
     * @param moveY          Translation Y value.
     * @param moveZ          Translation Z value.
     * @return The new object position.
     */
    public native float[] translate(final long pointerAddress, final float moveX, final float moveY, final float moveZ);

    /**
     * Rotate the object in native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     * @param yaw            Rotation X value.
     * @param pitch          Rotation Y value.
     * @return The new node direction value.
     */
    public native float[] rotate(final long pointerAddress, final float yaw, final float pitch);

    /**
     * Rotate the object in native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     * @param quatX          Rotation X value.
     * @param quatY          Rotation Y value.
     * @param quatZ          Rotation Z value.
     * @param quatW          Rotation W value.
     */
    public native void rotateQuaternion(final long pointerAddress, final float quatX, final float quatY, final float quatZ, final float quatW);

    /**
     * Scale the object in native code.
     *
     * @param pointerAddress Address to the native object.
     * @param scaleX         Width scale factor.
     * @param scaleY         Height scale factor.
     * @param scaleZ         Depth scale factor.
     */
    public native void scale(final long pointerAddress, final float scaleX, final float scaleY, final float scaleZ);

    /**
     * Attach this node to another movable in native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     * @param other          Address to the other native yz::Movable.
     */
    public native void attachTo(final long pointerAddress, final long other);

    public native void detachFromParent(final long pointerAddress, final long parentPointer);

    /**
     * Delete the object in native code.
     *
     * @param pointerAddress Address to the native yz::Node.
     */
    public native void delete(final long pointerAddress);

    public native float[] getAbsoluteDirection(long pointerAddress);

    public native float[] getAbsolutePosition(long pointerAddress);
}
