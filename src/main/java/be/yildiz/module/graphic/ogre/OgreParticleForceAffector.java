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

import be.yildiz.module.graphic.ParticleForceAffector;
import be.yildizgames.common.nativeresources.NativePointer;

/**
 * Ogre implementation for the particle force affector.
 *
 * @author Grégory Van den Borre
 */
final class OgreParticleForceAffector extends ParticleForceAffector {

    /**
     * Native pointer for the yz::ParticleForceAffector.
     */
    private final NativePointer pointer;

    /**
     * Full constructor.
     *
     * @param pointer Native pointer for this object.
     */
    OgreParticleForceAffector(final NativePointer pointer) {
        super();
        this.pointer = pointer;
    }

    @Override
    protected void setForceImpl(final float x, final float y, final float z) {
        this.setForce(this.pointer.getPointerAddress(), x, y, z);
    }

    /**
     * Set the force in native code.
     *
     * @param pointerAddress Address to the native yz::ParticleForceAffector.
     * @param x              X axis force strength.
     * @param y              Y axis force strength.
     * @param z              Z axis force strength.
     */
    private native void setForce(final long pointerAddress, final float x, final float y, final float z);

}
