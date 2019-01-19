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
public class JniMaterial {

    /**
     * Delete the object in native code.
     *
     * @param address Address of the native object.
     */
    public native void delete(final long address);

    /**
     * Create a new Ogre::Material in native code.
     *
     * @param name Material name, must be unique.
     * @return A pointer address to the newly created Ogre::Material.
     */
    public native long createTexture(final String name);

    /**
     * Copy this material.
     *
     * @param pointerAddress Address to the native Ogre::Material*.
     * @param name           Copied object name, must be unique.
     * @return A pointer address to the newly created Ogre::Material.
     */
    public native long copy(final long pointerAddress, final String name);

    /**
     * Load the material in native code.
     *
     * @param pointerAddress Address to the native Ogre::Material*.
     */
    public native void loadTexture(final long pointerAddress);

    /**
     * Create a new technique for this material.
     *
     * @param pointerAddress Address to the native Ogre::Material*.
     * @return A pointer address to the newly created Ogre::Technique.
     */
    public native long createTechnique(final long pointerAddress);

    /**
     * Retrieve a technique in native from its index.
     *
     * @param pointerAddress Address to the native Ogre::Material*.
     * @param index          Index of the technique to retrieve.
     * @return A pointer address to the retrieved Ogre::Technique.
     */
    public native long getTechnique(final long pointerAddress, final int index);

    /**
     * Get all techniques for this material.
     *
     * @param pointerAddress Address to the native Ogre::Material*.
     * @return A list pointer addresses to the retrieved Ogre::Technique.
     */
    public native long[] getTechniqueList(final long pointerAddress);

    /**
     * Set the material receive or not shadows.
     *
     * @param pointerAddress Address to the native Ogre::Material*.
     * @param receive        <code>true</code> to receive shadows.
     */
    public native void receiveShadow(final long pointerAddress, final boolean receive);
}
