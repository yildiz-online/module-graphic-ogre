//        This file is part of the Yildiz-Online project, licenced under the MIT License
//        (MIT)
//
//        Copyright (c) 2016 Grégory Van den Borre
//
//        More infos available: http://yildiz.bitbucket.org
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
//        of this software and associated documentation files (the "Software"), to deal
//        in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
//        furnished to do so, subject to the following conditions:
//
//        The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
//        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//        SOFTWARE.

package be.yildiz.module.graphic.ogre;

import be.yildiz.common.BaseCoordinate;
import be.yildiz.common.nativeresources.Native;
import be.yildiz.common.nativeresources.NativePointer;
import be.yildiz.module.graphic.Material;
import be.yildiz.module.graphic.gui.Element;
import be.yildiz.module.graphic.gui.GuiContainer;
import be.yildiz.module.graphic.gui.Zorder;

import java.util.Optional;

/**
 * Ogre implementation for a GuiContainer.
 *
 * @author Grégory Van Den Borre
 */
final class OgreGuiContainer extends GuiContainer implements Native {

    /**
     * Pointer for the native object.
     */
    private final NativePointer pointer;

    /**
     * Screen height.
     */
    private final int screenHeight;

    /**
     * Screen width.
     */
    private final int screenWidth;

    /**
     * Full constructor, initialize the container in the native code with a name, material and size and z depth.
     *
     * @param name         Container name, must be unique.
     * @param material     Container background.
     * @param coordinate   Container size and position.
     * @param screenWidth  Screen width in pixels.
     * @param screenHeight Screen height in pixels.
     */
    OgreGuiContainer(final String name, final Material material, final BaseCoordinate coordinate, final int screenWidth, final int screenHeight, final boolean widget) {
        super(name, coordinate, material, Optional.empty(), widget);
        this.screenHeight = screenHeight;
        this.screenWidth = screenWidth;
        this.pointer = NativePointer.create(this.constructor(OgreMaterial.class.cast(material).getPointer().getPointerAddress(), name, coordinate.width, coordinate.height));
        this.setPosition(coordinate.left, coordinate.top);
        if (!widget && parent.isPresent()) {
            this.setZ(parent.get().getZ().add(1));
        }
    }

    /**
     * Full constructor, initialize the container in the native code with a name, material and size.
     *
     * @param name         Container name, must be unique.
     * @param material     Container background.
     * @param coordinate   Container size and position.
     * @param parent       Container holding this container.
     * @param screenWidth  Screen width in pixels.
     * @param screenHeight Screen height in pixels.
     */
    OgreGuiContainer(final String name, final Material material, final BaseCoordinate coordinate, final GuiContainer parent, final int screenWidth, final int screenHeight, final boolean widget) {
        super(name, coordinate, material, Optional.of(parent), widget);
        this.screenHeight = screenHeight;
        this.screenWidth = screenWidth;
        this.pointer = NativePointer.create(this.constructorParent(OgreMaterial.class.cast(material).getPointer().getPointerAddress(), name, coordinate.width, coordinate.height,
                OgreGuiContainer.class.cast(parent).getPointer().getPointerAddress()));
        this.setPosition(coordinate.left, coordinate.top);
        this.show();
    }

    @Override
    public String getElementName(final int x, final int y) {
        final float left = (float) x / (float) this.screenWidth;
        final float top = (float) y / (float) this.screenHeight;
        return this.getElement(this.pointer.getPointerAddress(), left, top);
    }

    @Override
    protected void showImpl() {
        this.show(this.pointer.getPointerAddress());
    }

    @Override
    protected void hideImpl() {
        this.hide(this.pointer.getPointerAddress());
    }

    @Override
    public NativePointer getPointer() {
        return this.pointer;
    }

    @Override
    public void delete() {
        this.pointer.delete();
        // FIXME implements
    }

    @Override
    protected void zoomImpl(final float factor) {
        this.zoom(this.pointer.getPointerAddress(), factor);
    }

    @Override
    protected void setSizeImpl(final int width, final int height) {
        this.setSize(this.pointer.getPointerAddress(), width, height);
    }

    @Override
    protected Element setPositionImpl(final int left, final int top) {
        this.setPosition(this.pointer.getPointerAddress(), left, top);
        return this;
    }

    @Override
    protected void addChildrenPositionImpl(final int left, final int top) {
        this.addChildrenPosition(this.pointer.getPointerAddress(), left, top);
    }

    @Override
    protected void setMaterialImpl(final Material material) {
        this.setMaterial(this.pointer.getPointerAddress(), OgreMaterial.class.cast(material).getPointer().getPointerAddress());
    }

    @Override
    protected void setZImpl(final Zorder z) {
        this.setZ(this.pointer.getPointerAddress(), (short) z.getValue());
    }

    /**
     * Build the object in native code.
     *
     * @param material Material to use as background.
     * @param name     Container name, must be unique.
     * @param width    Container width value.
     * @param height   Container height value.
     * @return The native address of the newly built object.
     */
    private native long constructor(final long material, final String name, final float width, final float height);

    /**
     * Build the object in native code.
     *
     * @param material      Name of the material to use as background.
     * @param name          Container name, must be unique.
     * @param width         Container width value.
     * @param height        Container height value.
     * @param parentAddress Parent GUI container pointer.
     * @return The native address of the newly built object.
     */
    private native long constructorParent(final long material, final String name, final float width, final float height, final long parentAddress);

    /**
     * Set the container size in native code.
     *
     * @param pointer Address to the native object.
     * @param width   New container width.
     * @param height  New container height.
     */
    private native void setSize(final long pointer, final float width, final float height);

    /**
     * Zoom the container in native code.
     *
     * @param pointer Address to the native object.
     * @param factor  Zoom factor.
     */
    private native void zoom(final long pointer, final float factor);

    /**
     * Retrieve an element from a position in native code.
     *
     * @param pointer Address to the native object.
     * @param posX    Position to check X value.
     * @param posY    Position to check Y value.
     * @return The name of the found element.
     */
    public native String getElement(final long pointer, final float posX, final float posY);

    /**
     * Show the container in native code.
     *
     * @param pointer Address to the native object.
     */
    private native void show(final long pointer);

    /**
     * Hide the container system in native code.
     *
     * @param pointer Address to the native object.
     */
    private native void hide(final long pointer);

    /**
     * Set the container position in native code.
     *
     * @param pointer Address to the native object.
     * @param posX    container X position.
     * @param posY    container Y position.
     */
    private native void setPosition(final long pointer, final float posX, final float posY);

    /**
     * Set the container depth position in native code.
     *
     * @param pointer Address to the native object.
     * @param depth   Depth value(Must be under 650).
     */
    private native void setZ(final long pointer, final short depth);

    /**
     * Set a background material to the container in native code.
     *
     * @param address  Address to the native object.
     * @param material Material.
     */
    private native void setMaterial(final long address, final long material);

    /**
     * Translate this container children.
     *
     * @param pointerAdress Address to the native object.
     * @param left          Horizontal translation, in pixels.
     * @param top           Vertical translation, in pixels.
     */
    private native void addChildrenPosition(final long pointerAdress, final int left, final int top);
}
