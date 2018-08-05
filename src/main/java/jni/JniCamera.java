/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 * Copyright (c) 2018 Grégory Van den Borre
 *
 * More infos available: https://www.yildiz-games.be
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
 * to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS  OR COPYRIGHT  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE  SOFTWARE.
 */

package jni;

/**
 * @author Grégory Van den Borre
 */
public class JniCamera {

    /**
     * Delete the object in native code.
     *
     * @param address Address of the native object.
     */
    public native void delete(final long address);

    public native void setAspectRatio(final long pointer, final float ratio);

    /**
     * Rotate the camera in native code.
     *
     * @param pointer Address to the native object.
     * @param yaw     Rotation X axis.
     * @param pitch   Rotation Y axis.
     * @return The new camera direction in an array(0 = X, 1 = Y, 2 = Z);
     */
    public native float[] rotate(final long pointer, final float yaw, final float pitch);

    /**
     * Set the camera look to a position.
     *
     * @param pointer Address to the native object.
     * @param targetX Target position X value.
     * @param targetY Target position Y value.
     * @param targetZ Target position Z value.
     * @return The new camera direction in an array(0 = X, 1 = Y, 2 = Z);
     */
    public native float[] lookAt(final long pointer, final float targetX, final float targetY, final float targetZ);

    /**
     * Set the camera direction.
     *
     * @param pointer Address to the native object.
     * @param dirX    Direction X value.
     * @param dirY    Direction Y value.
     * @param dirZ    Direction Z value.
     */
    public native void setOrientation(final long pointer, final float dirX, final float dirY, final float dirZ);

    /**
     * Check if a position in visible by the camera.
     *
     * @param pointer   Address to the native object.
     * @param xPosition Position to check X value.
     * @param yPosition Position to check Y value.
     * @param zPosition Position to check Z value.
     * @return <code>true</code> if visible, <code>false</code> otherwise.
     */
    public native boolean isVisible(final long pointer, final float xPosition, final float yPosition, final float zPosition);

    /**
     * Move the camera in native code.
     *
     * @param pointer      Address to the native object.
     * @param translationX Translation X value.
     * @param translationY Translation Y value.
     * @param translationZ Translation Z value.
     * @return The camera new position in an array(0 = X, 1 = Y, 2 = Z);
     */
    public native float[] move(final long pointer, final float translationX, final float translationY, final float translationZ);

    /**
     * Retrieve the camera direction in native code.
     *
     * @param pointer Address to the native object.
     * @return The camera direction in an array(0 = X, 1 = Y, 2 = Z);
     */
    public native float[] getDirection(final long pointer);

    /**
     * Detach from the parent node in native code.
     *
     * @param pointer Address of this yz::Camera.
     */
    public native void detachFromParent(final long pointer);

    /**
     * Use this when the camera is not moved directly(i.e. by nodes) to force listeners being updated.
     *
     * @param pointer Address to the native object.
     */
    public native void forceListenersUpdate(final long pointer);

    /**
     * Remove a listener in native code.
     *
     * @param pointer Address of this yz::Camera.
     * @param ls      Address of the listener to remove.
     */
    public native void unregisterListener(final long pointer, final long ls);

    /**
     * Activate auto tracking for a node in native code.
     *
     * @param pointer     Address of this yz::Camera.
     * @param nodePointer Address of the yz::Node to track.
     */
    public native void setAutotrack(final long pointer, final long nodePointer);

    /**
     * Deactivate auto tracking in native code.
     *
     * @param pointer Address of this yz::Camera.
     */
    public native void stopAutotrack(final long pointer);

    /**
     * Enable the rendering distance.
     *
     * @param pointer Pointer to the native object.
     */
    public native void enableRenderingDistance(final long pointer);

    /**
     * Set the far clip distance.
     *
     * @param pointer  Pointer to the native object.
     * @param distance Far clip distance.
     */
    public native void setFarClip(final long pointer, final int distance);

    /**
     * Set the near clip distance.
     *
     * @param pointer  Pointer to the native object.
     * @param distance Near clip distance.
     */
    public native void setNearClip(final long pointer, final int distance);

    /**
     * Throw a plane ray in native code to retrieve the movable in the plane.
     *
     * @param pointerAddress Address to the native yz::Camera*.
     * @param left           Plane left value.
     * @param top            Plane top value.
     * @param right          Plane right value.
     * @param bottom         Plane bottom value.
     * @return An array with the movable pointer addresses.
     */
    public native long[] throwPlaneRay(final long pointerAddress, final float left, final float top, final float right, final float bottom);

    /**
     * Throw a ray to retrieve an entity in native code.
     *
     * @param pointerAddress Address to the native yz::Camera*.
     * @param screenX        Screen X position to throw the ray.
     * @param screenY        Screen Y position to throw the ray.
     * @param poly           <code>true</code> to make selection with polygon precision, false to use bounding box.
     * @return The pointer value of the found movable object, if none, 0.
     */
    public native long throwRay(final long pointerAddress, final float screenX, final float screenY, final boolean poly);

    /**
     * Compute the intersection point between the mouse position and the invisible ground associated to the camera.
     *
     * @param pointerAddress Address to the native yz::Camera*.
     * @param screenX        Mouse x position.
     * @param screenY        Mouse y position.
     * @return The intersection point.
     */
    public native float[] computeMoveDestinationGroundIntersect(final long pointerAddress, final float screenX, final float screenY);

    public native void attachToNode(final long pointerAddress, final long nodeAddress);
}
