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

import be.yildiz.common.nativeresources.NativePointer;
import be.yildiz.module.graphic.MaterialPass;
import be.yildiz.module.graphic.MaterialTechnique;

import java.util.List;

/**
 * Ogre implementation for a MaterialTechnique.
 *
 * @author Grégory Van den Borre
 */
final class OgreMaterialTechnique extends MaterialTechnique {

    /**
     * Pointer to the native object.
     */
    private final NativePointer pointer;

    /**
     * Full constructor.
     *
     * @param address Address of the native pointer.
     * @param index   Index value.
     */
    OgreMaterialTechnique(final long address, final int index) {
        super(index);
        this.pointer = NativePointer.create(address);
        this.createTexturePass();
    }

    /**
     * Copy constructor.
     *
     * @param address Address of the native pointer.
     * @param index   Index value.
     * @param list    List of contained pass.
     */
    OgreMaterialTechnique(final long address, final int index, final List<MaterialPass> list) {
        super(index, list);
        this.pointer = NativePointer.create(address);
    }

    /**
     * Retrieve the list of all passes contained in this technique.
     *
     * @param pointerAddress Address to the native object.
     * @return The list of pass pointer addresses.
     */
    static native long[] getPassList(final long pointerAddress);

    @Override
    protected MaterialPass createPassImpl(final int index) {
        if (index == 0) {
            return new OgreMaterialPass(this.getPass(this.pointer.getPointerAddress(), 0));
        }
        return new OgreMaterialPass(this.createPass(this.pointer.getPointerAddress()));

    }

    @Override
    protected void setGlowImpl() {
        this.setGlow(this.pointer.getPointerAddress());

    }

    /**
     * Create a new pass for this technique.
     *
     * @param pointerAddress Address to the native object.
     * @return The address to the pass native object.
     */
    private native long createPass(final long pointerAddress);

    /**
     * Activate the glow for this technique.
     *
     * @param pointerAddress Address to the native object.
     */
    private native void setGlow(final long pointerAddress);

    /**
     * Get a pass from its index.
     *
     * @param pointerAddress Address to the native object.
     * @param index          Pass index.
     * @return The pass pointer address.
     */
    private native long getPass(final long pointerAddress, final int index);
}
