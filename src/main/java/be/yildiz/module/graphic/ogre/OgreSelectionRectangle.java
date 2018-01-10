/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 * Copyright (c) 2017 Grégory Van den Borre
 *
 * More infos available: https://www.yildiz-games.be
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without
 * limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT  HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  SOFTWARE.
 */

package be.yildiz.module.graphic.ogre;

import be.yildiz.common.Rectangle;
import be.yildiz.module.graphic.Material;
import be.yildiz.module.graphic.SelectionRectangle;
import be.yildizgames.common.nativeresources.NativePointer;

/**
 * Ogre implementation for the selection rectangle.
 *
 * @author Grégory Van Den Borre
 */
final class OgreSelectionRectangle extends SelectionRectangle {

    /**
     * Pointer for the native object.
     */
    private final NativePointer pointer;

    /**
     * Full constructor.
     *
     * @param material  Material to set around the rectangle.
     * @param material2 Material to set inside the rectangle.
     */
    OgreSelectionRectangle(final Material material, final Material material2) {
        super();
        this.pointer = NativePointer.create(this.constructor(OgreMaterial.class.cast(material).getPointer().getPointerAddress(),
                OgreMaterial.class.cast(material2).getPointer().getPointerAddress()));
    }

    @Override
    public void update(final Rectangle rectangle) {
        this.update(this.pointer.getPointerAddress(), rectangle.getLeft(), rectangle.getTop(), rectangle.getRight(), rectangle.getBottom());
    }

    /**
     * Build the rectangle in native code.
     *
     * @param material  Material to use around the rectangle.
     * @param material2 Material to use inside the rectangle.
     * @return The pointer address to the native object.
     */
    private native long constructor(final long material, final long material2);

    /**
     * Redraw the rectangle in native code.
     *
     * @param pointer Address to the native object.
     * @param left    Left border value.
     * @param top     Top border value.
     * @param right   Right border value.
     * @param bottom  Bottom border value.
     */
    private native void update(final long pointer, final float left, final float top, final float right, final float bottom);

}
