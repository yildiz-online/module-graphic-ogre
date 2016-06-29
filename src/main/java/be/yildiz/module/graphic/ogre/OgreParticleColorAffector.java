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
import be.yildiz.module.graphic.ParticleColorAffector;

/**
 * Ogre implementation for the particle color affector.
 *
 * @author Grégory Van Den Borre
 */
final class OgreParticleColorAffector extends ParticleColorAffector {

    /**
     * Address to the associated native object.
     */
    private final NativePointer pointer;

    /**
     * Full constructor.
     *
     * @param pointer Address to the native object.
     */
    OgreParticleColorAffector(final NativePointer pointer) {
        super();
        this.pointer = pointer;
    }

    @Override
    protected void setAlphaVariationImpl(final int variation) {
        this.setAlpha(this.pointer.address, variation / 100f);
    }

    /**
     * Set the alpha variation in native code.
     *
     * @param pointer   Address to the native object.
     * @param variation Alpha variation per second.
     */
    private native void setAlpha(final long pointer, final float variation);

}
