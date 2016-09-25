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

import be.yildiz.common.nativeresources.Native;
import be.yildiz.common.nativeresources.NativePointer;
import be.yildiz.common.vector.Point3D;
import be.yildiz.module.graphic.LensFlare;
import lombok.Getter;

/**
 * Ogre implementation for a LensFalre.
 *
 * @author Grégory Van den Borre
 */
final class OgreLensFlare extends LensFlare implements Native {

    /**
     * Pointer address to the native code YZ::LensFlare.
     */
    @Getter
    private final NativePointer pointer;

    /**
     * Full constructor.
     *
     * @param pointerAddress Pointer address to the associated native object.
     * @param position       lens flare position.
     */
    OgreLensFlare(final NativePointer pointerAddress, final Point3D position) {
        super(position);
        this.pointer = pointerAddress;
    }

    @Override
    protected void setPositionImpl(final Point3D position) {
        this.setPosition(this.pointer.getPointerAddress(), position.x, position.y, position.z);
    }

    @Override
    public void setStreakSize(final float w, final float h) {
        this.setStreakSize(this.pointer.getPointerAddress(), w, h);
    }

    @Override
    public void setLightSize(final float w, final float h) {
        this.setLightSize(this.pointer.getPointerAddress(), w, h);
    }

    @Override
    public void delete() {
        this.delete(this.pointer.getPointerAddress());
        this.pointer.delete();
    }

    /**
     * Delete the object in native code.
     *
     * @param address Address of the native object.
     */
    private native void delete(final long address);

    /**
     * Set the lens flare position in native code.
     *
     * @param pointerAddress Address of the native YZ::LensFlare pointer.
     * @param x              New X position.
     * @param y              New Y position.
     * @param z              New Z position.
     */
    private native void setPosition(final long pointerAddress, final float x, final float y, final float z);

    /**
     * Set streak billboard size.
     *
     * @param pointerAddress Address of the native YZ::LensFlare pointer.
     * @param w              Width in pixel.
     * @param h              Height in pixel.
     */
    private native void setStreakSize(final long pointerAddress, final float w, final float h);

    /**
     * Set light billboard size.
     *
     * @param pointerAddress Address of the native YZ::LensFlare pointer.
     * @param w              Width in pixel.
     * @param h              Height in pixel.
     */
    private native void setLightSize(final long pointerAddress, final float w, final float h);

}
