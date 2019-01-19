/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *  
 * Copyright (c) 2019 Grégory Van den Borre
 *
 * More infos available: https://engine.yildiz-games.be
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this 
 * software and associated documentation files (the "Software"), to deal in the Software 
 * without restriction, including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons 
 * to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or 
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS  OR COPYRIGHT  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE  SOFTWARE.
 */

package jni;

/**
 * @author Grégory Van den Borre
 */
public class JniParticleEmitter {

    /**
     * Set the particle emission rate in native code.
     *
     * @param pointerAddress Address to the native yz::ParticleEmitter*.
     * @param rate           Emission rate.
     */
    public native void setRate(final long pointerAddress, final float rate);

    /**
     * Set the particle emission duration in native code.
     *
     * @param pointerAddress Address to the native yz::ParticleEmitter*.
     * @param duration       Emission duration.
     */
    public native void setDuration(final long pointerAddress, final float duration);

    /**
     * Set the particle life time in native code.
     *
     * @param pointerAddress Address to the native yz::ParticleEmitter*.
     * @param lifeTime       Particle life time.
     */
    public native void setLifeTime(final long pointerAddress, final float lifeTime);

    /**
     * Set the particle emission direction in native code.
     *
     * @param pointerAddress Address to the native yz::ParticleEmitter*.
     * @param x              Emission direction X value.
     * @param y              Emission direction Y value.
     * @param z              Emission direction Z value.
     */
    public native void setDirection(final long pointerAddress, final float x, final float y, final float z);

    /**
     * Set the particle color when created in native code.
     *
     * @param pointerAddress Address to the native yz::ParticleEmitter*.
     * @param red            Color red value.
     * @param green          Color green value.
     * @param blue           Color blue value.
     * @param alpha          Color alpha value.
     */
    public native void setStartColor(final long pointerAddress, final float red, final float green, final float blue, final float alpha);

    /**
     * Set the particle color when life is finished in native code.
     *
     * @param pointerAddress Address to the native yz::ParticleEmitter*.
     * @param red            Color red value.
     * @param green          Color green value.
     * @param blue           Color blue value.
     * @param alpha          Color alpha value.
     */
    public native void setEndColor(final long pointerAddress, final float red, final float green, final float blue, final float alpha);

    /**
     * Set the particle emission angle in native code.
     *
     * @param pointerAddress Address to the native yz::ParticleEmitter*.
     * @param angle          emission angle.
     */
    public native void setAngle(final long pointerAddress, final float angle);

    /**
     * Set the particle emitter repeat delay in native code.
     *
     * @param pointerAddress Address to the native yz::ParticleEmitter*.
     * @param repeatDelay    Delay to restart the emitter.
     */
    public native void setRepeatDelay(final long pointerAddress, final float repeatDelay);

    /**
     * Set the particle emitter maximum speed emission in native code.
     *
     * @param pointerAddress Address to the native yz::ParticleEmitter*.
     * @param maxSpeed       Particle emission maximum speed.
     */
    public native void setMaxSpeed(final long pointerAddress, final float maxSpeed);

    /**
     * Set the particle emitter minimum speed emission in native code.
     *
     * @param pointerAddress Address to the native yz::ParticleEmitter*.
     * @param minSpeed       Particle emission minimum speed.
     */
    public native void setMinSpeed(final long pointerAddress, final float minSpeed);
}
