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

package be.yildizgames.module.graphic.ogre;

import be.yildizgames.common.jni.Native;
import be.yildizgames.common.jni.NativePointer;
import be.yildizgames.module.coordinate.BaseCoordinate;
import be.yildizgames.module.graphic.gui.Zorder;
import be.yildizgames.module.graphic.gui.container.Container;
import be.yildizgames.module.graphic.gui.internal.Element;
import be.yildizgames.module.graphic.gui.internal.impl.SimpleContainer;
import be.yildizgames.module.graphic.material.Material;
import jni.JniGuiContainer;

/**
 * Ogre implementation for a GuiContainer.
 *
 * @author Grégory Van Den Borre
 */
final class OgreGuiContainer extends SimpleContainer implements Native {

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

    private final JniGuiContainer jni = new JniGuiContainer();

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
        super(name, coordinate, material, widget);
        this.screenHeight = screenHeight;
        this.screenWidth = screenWidth;
        this.pointer = NativePointer.create(this.jni.constructor(((OgreMaterial) material).getPointer().getPointerAddress(), name, coordinate.width, coordinate.height));
        this.setPosition(coordinate.left, coordinate.top);
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
    OgreGuiContainer(final String name, final Material material, final BaseCoordinate coordinate, final Container parent, final int screenWidth, final int screenHeight, final boolean widget) {
        super(name, coordinate, material, (OgreGuiContainer) parent, widget);
        this.screenHeight = screenHeight;
        this.screenWidth = screenWidth;
        this.pointer = NativePointer.create(this.jni.constructorParent(((OgreMaterial) material).getPointer().getPointerAddress(), name, coordinate.width, coordinate.height,
                ((OgreGuiContainer) parent).getPointer().getPointerAddress()));
        this.setPosition(coordinate.left, coordinate.top);
        this.show();
        if (!widget) {
            this.setZ(parent.getZ().add(1));
        }
    }

    @Override
    public String getElementName(final int x, final int y) {
        final float left = (float) x / (float) this.screenWidth;
        final float top = (float) y / (float) this.screenHeight;
        return this.jni.getElement(this.pointer.getPointerAddress(), left, top);
    }

    @Override
    protected void showImpl() {
        this.jni.show(this.pointer.getPointerAddress());
    }

    @Override
    protected void hideImpl() {
        this.jni.hide(this.pointer.getPointerAddress());
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
        this.jni.zoom(this.pointer.getPointerAddress(), factor);
    }

    @Override
    protected void setSizeImpl(final int width, final int height) {
        this.jni.setSize(this.pointer.getPointerAddress(), width, height);
    }

    @Override
    protected Element setPositionImpl(final int left, final int top) {
        this.jni.setPosition(this.pointer.getPointerAddress(), left, top);
        return this;
    }

    @Override
    protected void addChildrenPositionImpl(final int left, final int top) {
        this.jni.addChildrenPosition(this.pointer.getPointerAddress(), left, top);
    }

    @Override
    protected void setMaterialImpl(final Material material) {
        this.jni.setMaterial(this.pointer.getPointerAddress(), ((OgreMaterial) material).getPointer().getPointerAddress());
    }

    @Override
    protected void setZImpl(final Zorder z) {
        this.jni.setZ(this.pointer.getPointerAddress(), (short) z.getValue());
    }

}
