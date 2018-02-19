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
        this.pointer = NativePointer.create(this.constructor(OgreGuiContainer.class.cast(container).getPointer().getPointerAddress(), name, ((OgreMaterial) material).getPointer().getPointerAddress(), coordinates.width,
                coordinates.height, coordinates.left, coordinates.top));
    }

    @Override
    protected int getZ() {
        return this.getZ(this.pointer.getPointerAddress());
    }

    @Override
    protected String getParentName() {
        return this.getParentName(this.pointer.getPointerAddress());
    }

    @Override
    protected void rotateRadian(final float value) {
        // FIXME uncomment
        // this.rotateRadian(this.pointer.address, value);
    }

    @Override
    public void delete() {
        this.delete(this.pointer.getPointerAddress());
        this.pointer.delete();
        this.removeFromRegisterer();
    }

    @Override
    protected void hideImpl() {
        this.hide(this.pointer.getPointerAddress());
    }

    @Override
    protected Element setPositionImpl(final int xPosition, final int yPosition) {
        this.setPosition(this.pointer.getPointerAddress(), xPosition, yPosition);
        return this;
    }

    @Override
    protected void showImpl() {
        this.show(this.pointer.getPointerAddress());
    }

    @Override
    protected void setSizeImpl(final int width, final int height) {
        this.setSize(this.pointer.getPointerAddress(), width, height);
    }

    @Override
    protected void setMaterialImpl(final Material material) {
        this.setTexture(this.pointer.getPointerAddress(), OgreMaterial.class.cast(material).getPointer().getPointerAddress());
    }

    @Override
    public NativePointer getPointer() {
        return pointer;
    }

    /**
     * Set the object hidden native code.
     *
     * @param pointerAddress Address to the native yz::GuiIcon*.
     */
    private native void hide(final long pointerAddress);

    /**
     * Set the object visible native code.
     *
     * @param pointerAddress Address to the native yz::GuiIcon*.
     */
    private native void show(final long pointerAddress);

    /**
     * Update the size in native code.
     *
     * @param pointerAddress Address to the native yz::GuiIcon*.
     * @param width          New object width.
     * @param height         New object height.
     */
    private native void setSize(final long pointerAddress, final float width, final float height);

    /**
     * Update the material in native code.
     *
     * @param pointerAddress Address to the native yz::GuiIcon*.
     * @param material       Material to set.
     */
    private native void setTexture(final long pointerAddress, final long material);

    /**
     * Delete the object in native code.
     *
     * @param pointerAddress Address to the native yz::GuiIcon*.
     */
    private native void delete(final long pointerAddress);

    /**
     * Set the position in native code.
     *
     * @param pointerAddress Address to the native yz::GuiIcon*.
     * @param left           X position.
     * @param top            Y position.
     */
    private native void setPosition(final long pointerAddress, final float left, final float top);

    /**
     * Build the object in native code.
     *
     * @param container Container holding the icon.
     * @param name      Name of the icon, must be unique.
     * @param material  Material to assign to the icon.
     * @param width     Width of the icon, in pixels.
     * @param height    Height of the icon, in pixels
     * @param left      Icon left position from its parent left border.
     * @param top       Icon top position from its parent top border.
     * @return A pointer to the newly built object.
     */
    private native long constructor(final long container, final String name, final long material, final float width, final float height, final float left, final float top);

    // FIXME use int and check for other method using floats.

    /**
     * Retrieve the Z value from native code.
     *
     * @param pointerAddress Address to the native yz::GuiIcon*.
     * @return The object Z value.
     */
    private native int getZ(final long pointerAddress);

    /**
     * Retrieve the parent container name from native code.
     *
     * @param pointerAddress Address to the native yz::GuiIcon*.
     * @return The name of the parent container.
     */
    private native String getParentName(final long pointerAddress);

}
