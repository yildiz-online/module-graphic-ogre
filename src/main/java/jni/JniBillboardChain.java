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
public class JniBillboardChain {

    /**
     * Create the object in native code.
     *
     * @param name Object unique name.
     * @param nodePointer Pointer to the yz::Node to attach wih this object.
     * @return The pointer address to the native object.
     */
    public native long constructor(final String name, final long nodePointer);

    /**
     * Add an element to the chain in native code.
     *
     * @param address      Native billboard chain pointer address.
     * @param xPosition    New element x position.
     * @param yPosition    New element y position.
     * @param zPosition    New element z position.
     * @param elementWidth New element width.
     */
    public native void addElement(final long address, final float xPosition, final float yPosition, final float zPosition, final float elementWidth);

    /**
     * Set the material in native code.
     *
     * @param pointer  Billboard chain native pointer address.
     * @param material Material to set.
     */
    public native void setMaterial(final long pointer, final long material);

    /**
     * Set the position of an element in native code.
     *
     * @param pointer      Billboard chain native pointer address.
     * @param listPosition Element position in the chain.
     * @param xPosition    Element x position.
     * @param yPosition    Element y position.
     * @param zPosition    Element z position.
     */
    public native void setElementPosition(final long pointer, final int listPosition, final float xPosition, final float yPosition, final float zPosition);

    /**
     * Delete the native object.
     *
     * @param pointer Billboard chain native pointer address.
     */
    public native void delete(final long pointer);
}
