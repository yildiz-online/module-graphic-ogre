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

package be.yildizgames.module.graphic.ogre.misc;

import be.yildizgames.common.jni.NativePointer;
import be.yildizgames.module.graphic.material.Material;
import be.yildizgames.module.graphic.misc.Line;
import be.yildizgames.module.graphic.ogre.OgreMaterial;
import be.yildizgames.module.graphic.ogre.OgreNode;

/**
 * Ogre Line implementation.
 *
 * @author Grégory Van den Borre
 */
public final class OgreLine extends Line {

    /**
     * Address to the associated native object.
     */
    private final NativePointer pointer;

    /**
     * Full constructor.
     *
     * @param node Node to attach the created line.
     */
    OgreLine(final OgreNode node) {
        super();
        this.pointer = NativePointer.create(this.constructor(node.getPointer().getPointerAddress()));
    }

    @Override
    protected void update(final float beginX, final float beginY, final float beginZ, final float endX, final float endY, final float endZ) {
        this.update(this.pointer.getPointerAddress(), beginX, beginY, beginZ, endX, endY, endZ);
    }

    @Override
    protected void hideImpl() {
        this.hide(this.pointer.getPointerAddress());
    }

    @Override
    protected void showImpl() {
        this.show(this.pointer.getPointerAddress());
    }

    @Override
    protected void setMaterialImpl(final Material material) {
        this.setMaterial(this.pointer.getPointerAddress(), OgreMaterial.class.cast(material).getPointer().getPointerAddress());
    }

    /**
     * Build the line in native code.
     *
     * @param nodePointer Address of the Ogre::SceneNode to attach the created line.
     * @return A pointer address to the newly created line.
     */
    private native long constructor(final long nodePointer);

    /**
     * Update the line in native code.
     *
     * @param pointerAddress Address of the native object.
     * @param beginX         First point X coordinate.
     * @param beginY         First point Y coordinate.
     * @param beginZ         First point Z coordinate.
     * @param endX           Last point X coordinate.
     * @param endY           Last point Y coordinate.
     * @param endZ           Last point Z coordinate.
     */
    private native void update(final long pointerAddress, final float beginX, final float beginY, final float beginZ, final float endX, final float endY, final float endZ);

    /**
     * Set the line visible in native code.
     *
     * @param pointerAddress Address to the native object.
     */
    private native void show(final long pointerAddress);

    /**
     * Set the line invisible in native code.
     *
     * @param pointerAddress Address to the native object.
     */
    private native void hide(final long pointerAddress);

    /**
     * Set the line material in native code.
     *
     * @param pointerAddress Address to the native object.
     * @param material       Material.
     */
    private native void setMaterial(final long pointerAddress, final long material);

}
