/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 * Copyright (c) 2019 Grégory Van den Borre
 *
 * More infos available: https://engine.yildiz-games.be
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

    public native void attachToNode(final long pointerAddress, final long nodeAddress);
}
