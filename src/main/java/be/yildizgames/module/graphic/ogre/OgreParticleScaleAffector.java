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

import be.yildizgames.module.graphic.particle.ParticleScaleAffector;
import be.yildizgames.common.jni.NativePointer;

/**
 * Ogre implementation for a particle scale affector.
 *
 * @author Grégory Van Den Borre
 */
final class OgreParticleScaleAffector extends ParticleScaleAffector {

    /**
     * Address to the associated native object.
     */
    private final NativePointer pointer;

    /**
     * Full constructor.
     *
     * @param pointer Address to the native object.
     */
    OgreParticleScaleAffector(final NativePointer pointer) {
        super();
        this.pointer = pointer;
    }

    /**
     * Call the native setScale method, parameter are divided by 100 to match
     * Ogre values(i.e 0.5 is half scale).
     *
     * @param width  Particle width scale per second factor.
     * @param height Particle height scale per second factor.
     */
    @Override
    protected void setScaleImpl(final int width, final int height) {
        this.setScale(this.pointer.getPointerAddress(), width / 100.0f, height / 100.0f);
    }

    /**
     * Scale the particle in native code.
     *
     * @param pointer Address to the native object.
     * @param width   Width scale per second.
     * @param height  Height scale per second.
     */
    private native void setScale(final long pointer, final float width, final float height);

}
