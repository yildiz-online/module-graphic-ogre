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

package be.yildizgames.module.graphic.ogre;

import be.yildizgames.common.jni.Native;
import be.yildizgames.common.jni.NativePointer;
import be.yildizgames.module.coordinate.BaseCoordinate;
import be.yildizgames.module.graphic.gui.container.Container;
import be.yildizgames.module.graphic.gui.element.AbstractIconElement;
import be.yildizgames.module.graphic.gui.internal.Element;
import be.yildizgames.module.graphic.material.Material;
import jni.JniGuiIcon;

/**
 * Ogre implementation for an icon element.
 *
 * @author Grégory Van Den Borre
 */
final class OgreIcon extends AbstractIconElement implements Native {

    /**
     * Pointer address to the associated yz::GuiIcon*.
     */
    private final NativePointer pointer;

    private final JniGuiIcon jni = new JniGuiIcon();

    /**
     * Full constructor.
     *
     * @param name        Object name, must be unique.
     * @param coordinates Object size and position.
     * @param material    Material to assign.
     * @param container   Container containing this object.
     */
    OgreIcon(final String name, final BaseCoordinate coordinates, final Material material, final Container container) {
        super(name, coordinates, material);
        this.pointer = NativePointer.create(this.jni.constructor(OgreGuiContainer.class.cast(container).getPointer().getPointerAddress(), name, ((OgreMaterial) material).getPointer().getPointerAddress(), coordinates.width,
                coordinates.height, coordinates.left, coordinates.top));
    }

    @Override
    protected int getZ() {
        return this.jni.getZ(this.pointer.getPointerAddress());
    }

    @Override
    public String getParentName() {
        return this.jni.getParentName(this.pointer.getPointerAddress());
    }

    @Override
    public void rotateRadian(final float value) {
        // FIXME uncomment
        // this.rotateRadian(this.pointer.address, value);
    }

    @Override
    public void delete() {
        this.jni.delete(this.pointer.getPointerAddress());
        this.pointer.delete();
        this.removeFromRegisterer();
    }

    @Override
    protected void hideImpl() {
        this.jni.hide(this.pointer.getPointerAddress());
    }

    @Override
    protected Element setPositionImpl(final int xPosition, final int yPosition) {
        this.jni.setPosition(this.pointer.getPointerAddress(), xPosition, yPosition);
        return this;
    }

    @Override
    protected void showImpl() {
        this.jni.show(this.pointer.getPointerAddress());
    }

    @Override
    protected void setSizeImpl(final int width, final int height) {
        this.jni.setSize(this.pointer.getPointerAddress(), width, height);
    }

    @Override
    protected void setMaterialImpl(final Material material) {
        this.jni.setTexture(this.pointer.getPointerAddress(), OgreMaterial.class.cast(material).getPointer().getPointerAddress());
    }

    @Override
    public NativePointer getPointer() {
        return pointer;
    }

}
