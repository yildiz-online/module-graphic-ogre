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
import jni.JniDynamicLine;

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

    private final JniDynamicLine jni = new JniDynamicLine();

    /**
     * Full constructor.
     *
     * @param node Node to attach the created line.
     */
    public OgreLine(final OgreNode node) {
        super();
        this.pointer = NativePointer.create(this.jni.constructor(node.getPointer().getPointerAddress()));
    }

    @Override
    protected void update(final float beginX, final float beginY, final float beginZ, final float endX, final float endY, final float endZ) {
        this.jni.update(this.pointer.getPointerAddress(), beginX, beginY, beginZ, endX, endY, endZ);
    }

    @Override
    protected void hideImpl() {
        this.jni.hide(this.pointer.getPointerAddress());
    }

    @Override
    protected void showImpl() {
        this.jni.show(this.pointer.getPointerAddress());
    }

    @Override
    protected void setMaterialImpl(final Material material) {
        this.jni.setMaterial(this.pointer.getPointerAddress(), OgreMaterial.class.cast(material).getPointer().getPointerAddress());
    }

}
