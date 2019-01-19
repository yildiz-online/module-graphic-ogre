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
public class JniQuery {

    /**
     * Throw a plane ray in native code to retrieve the movable in the plane.
     *
     * @param pointerAddress Address to the native yz::Query*.
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
     * @param pointerAddress Address to the native yz::Query*.
     * @param screenX        Screen X position to throw the ray.
     * @param screenY        Screen Y position to throw the ray.
     * @param poly           <code>true</code> to make selection with polygon precision, false to use bounding box.
     * @return The pointer value of the found movable object, if none, 0.
     */
    public native long throwRay(final long pointerAddress, final float screenX, final float screenY, final boolean poly);
}
