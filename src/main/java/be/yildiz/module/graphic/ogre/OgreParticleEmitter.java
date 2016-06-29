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

import be.yildiz.common.Color;
import be.yildiz.common.nativeresources.NativePointer;
import be.yildiz.common.vector.Point3D;
import be.yildiz.module.graphic.ParticleEmitter;

/**
 * Ogre implementation for a particle emitter.
 *
 * @author Grégory Van den Borre
 */
final class OgreParticleEmitter extends ParticleEmitter {

    /**
     * Pointer address to the associated YZ::ParticleEmitter*.
     */
    private final NativePointer pointer;

    /**
     * Full constructor.
     *
     * @param pointer Native object pointer address.
     */
    OgreParticleEmitter(final NativePointer pointer) {
        super();
        this.pointer = pointer;
    }

    @Override
    protected void setAngleImpl(final float angle) {
        this.setAngle(this.pointer.address, angle);
    }

    @Override
    protected void setRateImpl(final float rate) {
        this.setRate(this.pointer.address, rate);
    }

    @Override
    protected void setDurationImpl(final float duration) {
        this.setDuration(this.pointer.address, duration);
    }

    @Override
    protected void setLifeTimeImpl(final float lifeTime) {
        this.setLifeTime(this.pointer.address, lifeTime);
    }

    @Override
    protected void setDirectionImpl(final Point3D direction) {
        this.setDirection(this.pointer.address, direction.x, direction.y, direction.z);
    }

    @Override
    protected void setMinSpeedImpl(final float minSpeed) {
        this.setMinSpeed(this.pointer.address, minSpeed);
    }

    @Override
    protected void setMaxSpeedImpl(final float maxSpeed) {
        this.setMaxSpeed(this.pointer.address, maxSpeed);
    }

    @Override
    protected void setStartColorImpl(final Color start) {
        this.setStartColor(this.pointer.address, start.normalizedRed, start.normalizedGreen, start.normalizedBlue, start.normalizedAlpha);
    }

    @Override
    protected void setEndColorImpl(final Color end) {
        this.setEndColor(this.pointer.address, end.normalizedRed, end.normalizedGreen, end.normalizedBlue, end.normalizedAlpha);
    }

    @Override
    protected void setRepeatDelayImpl(final float repeatDelay) {
        this.setRepeatDelay(this.pointer.address, repeatDelay);
    }

    /**
     * Set the particle emission rate in native code.
     *
     * @param pointerAddress Address to the native YZ::ParticleEmitter*.
     * @param rate           Emission rate.
     */
    private native void setRate(final long pointerAddress, final float rate);

    /**
     * Set the particle emission duration in native code.
     *
     * @param pointerAddress Address to the native YZ::ParticleEmitter*.
     * @param duration       Emission duration.
     */
    private native void setDuration(final long pointerAddress, final float duration);

    /**
     * Set the particle life time in native code.
     *
     * @param pointerAddress Address to the native YZ::ParticleEmitter*.
     * @param lifeTime       Particle life time.
     */
    private native void setLifeTime(final long pointerAddress, final float lifeTime);

    /**
     * Set the particle emission direction in native code.
     *
     * @param pointerAddress Address to the native YZ::ParticleEmitter*.
     * @param x              Emission direction X value.
     * @param y              Emission direction Y value.
     * @param z              Emission direction Z value.
     */
    private native void setDirection(final long pointerAddress, final float x, final float y, final float z);

    /**
     * Set the particle color when created in native code.
     *
     * @param pointerAddress Address to the native YZ::ParticleEmitter*.
     * @param red            Color red value.
     * @param green          Color green value.
     * @param blue           Color blue value.
     * @param alpha          Color alpha value.
     */
    private native void setStartColor(final long pointerAddress, final float red, final float green, final float blue, final float alpha);

    /**
     * Set the particle color when life is finished in native code.
     *
     * @param pointerAddress Address to the native YZ::ParticleEmitter*.
     * @param red            Color red value.
     * @param green          Color green value.
     * @param blue           Color blue value.
     * @param alpha          Color alpha value.
     */
    private native void setEndColor(final long pointerAddress, final float red, final float green, final float blue, final float alpha);

    /**
     * Set the particle emission angle in native code.
     *
     * @param pointerAddress Address to the native YZ::ParticleEmitter*.
     * @param angle          emission angle.
     */
    private native void setAngle(final long pointerAddress, final float angle);

    /**
     * Set the particle emitter repeat delay in native code.
     *
     * @param pointerAddress Address to the native YZ::ParticleEmitter*.
     * @param repeatDelay    Delay to restart the emitter.
     */
    private native void setRepeatDelay(final long pointerAddress, final float repeatDelay);

    /**
     * Set the particle emitter maximum speed emission in native code.
     *
     * @param pointerAddress Address to the native YZ::ParticleEmitter*.
     * @param maxSpeed       Particle emission maximum speed.
     */
    private native void setMaxSpeed(final long pointerAddress, final float maxSpeed);

    /**
     * Set the particle emitter minimum speed emission in native code.
     *
     * @param pointerAddress Address to the native YZ::ParticleEmitter*.
     * @param minSpeed       Particle emission minimum speed.
     */
    private native void setMinSpeed(final long pointerAddress, final float minSpeed);

}
