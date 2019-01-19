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
public class JniEntity {

    /**
     * Delete the object in native code.
     *
     * @param address Address of the native object.
     */
    public native void delete(final long address);

    /**
     * Get the parent scene node name.
     *
     * @param pointerAddress Address of the native Ogre::Entity pointer.
     * @return Ogre::Entity::getParentSceneNode().getName().
     */
    public native String getParentSceneNode(final long pointerAddress);

    /**
     * Set the Ogre::Entity casts shadows.
     *
     * @param pointerAddress Address of the native Ogre::Entity pointer.
     * @param cast           <code>true</code> to cast shadow, <code>false</code> to stop casting.
     */
    public native void castShadow(final long pointerAddress, final boolean cast);

    /**
     * Set a Material on this object.
     *
     * @param pointerAddress Address of the native Ogre::Entity pointer.
     * @param material       Material to set.
     */
    public native void setMaterial(final long pointerAddress, final long material);

    /**
     * Set the Ogre::Entity to be ignored by ray picking.
     *
     * @param pointerAddress Address of the native Ogre::Entity pointer.
     */
    public native void setUnpickable(final long pointerAddress);

    /**
     * Set a GPU program parameter.
     *
     * @param pointerAddress Address of the native Ogre::Entity pointer.
     * @param index          Parameter index.
     * @param v1 Parameter value 1.
     * @param v2 Parameter value 2.
     * @param v3 Parameter value 3.
     * @param v4 Parameter value 4.
     *
     */
    public native void setParameter(final long pointerAddress, final int index, final float v1, final float v2, final float v3, final float v4);

    /**
     * Set the maximum distance from where the entity will no longer be rendered.
     *
     * @param pointer  Address of the native Entity pointer.
     * @param distance Maximum rendering distance.
     */
    public native void setRenderingDistance(final long pointer, final int distance);

    /**
     * Set the object to be rendered behind the other.
     *
     * @param pointer Address of the native Entity pointer.
     * @param index   Z position(0 = background, 105 = max).
     */
    public native void setRenderQueue(final long pointer, final int index);
}
