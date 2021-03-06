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

package be.yildizgames.module.graphic.ogre.particle;

import be.yildizgames.common.geometry.Point3D;
import be.yildizgames.common.jni.NativePointer;
import be.yildizgames.module.color.Color;
import be.yildizgames.module.graphic.particle.ParticleEmitter;
import jni.JniParticleEmitter;

/**
 * Ogre implementation for a particle emitter.
 *
 * @author Grégory Van den Borre
 */
final class OgreParticleEmitter extends ParticleEmitter {

    /**
     * Pointer address to the associated yz::ParticleEmitter*.
     */
    private final NativePointer pointer;

    private final JniParticleEmitter jni = new JniParticleEmitter();

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
        this.jni.setAngle(this.pointer.getPointerAddress(), angle);
    }

    @Override
    protected void setRateImpl(final float rate) {
        this.jni.setRate(this.pointer.getPointerAddress(), rate);
    }

    @Override
    protected void setDurationImpl(final float duration) {
        this.jni.setDuration(this.pointer.getPointerAddress(), duration);
    }

    @Override
    protected void setLifeTimeImpl(final float lifeTime) {
        this.jni.setLifeTime(this.pointer.getPointerAddress(), lifeTime);
    }

    @Override
    protected void setDirectionImpl(final Point3D direction) {
        this.jni.setDirection(this.pointer.getPointerAddress(), direction.x, direction.y, direction.z);
    }

    @Override
    protected void setMinSpeedImpl(final float minSpeed) {
        this.jni.setMinSpeed(this.pointer.getPointerAddress(), minSpeed);
    }

    @Override
    protected void setMaxSpeedImpl(final float maxSpeed) {
        this.jni.setMaxSpeed(this.pointer.getPointerAddress(), maxSpeed);
    }

    @Override
    protected void setStartColorImpl(final Color start) {
        this.jni.setStartColor(this.pointer.getPointerAddress(), start.normalizedRedValue, start.normalizedGreenValue, start.normalizedBlueValue, start.normalizedAlphaValue);
    }

    @Override
    protected void setEndColorImpl(final Color end) {
        this.jni.setEndColor(this.pointer.getPointerAddress(), end.normalizedRedValue, end.normalizedGreenValue, end.normalizedBlueValue, end.normalizedAlphaValue);
    }

    @Override
    protected void setRepeatDelayImpl(final float repeatDelay) {
        this.jni.setRepeatDelay(this.pointer.getPointerAddress(), repeatDelay);
    }

    //FIXME get correct value.
    @Override
    protected float getInitialAngle() {
        return 0;
    }

    //FIXME get correct value.
    @Override
    protected float getInitialRate() {
        return 0;
    }

    //FIXME get correct value.
    @Override
    protected float getInitialDuration() {
        return 0;
    }

    //FIXME get correct value.
    @Override
    protected float getInitialLifeTime() {
        return 0;
    }

    //FIXME get correct value.
    @Override
    protected Point3D getInitialDirection() {
        return Point3D.BASE_DIRECTION;
    }

    //FIXME get correct value.
    @Override
    protected float getInitialMinSpeed() {
        return 0;
    }

    //FIXME get correct value.
    @Override
    protected float getInitialMaxSpeed() {
        return 0;
    }

    //FIXME get correct value.
    @Override
    protected  Color getInitialStartColor() {
        return Color.BLACK;
    }

    //FIXME get correct value.
    @Override
    protected  Color getInitialEndColor() {
        return Color.BLACK;
    }

    //FIXME get correct value.
    @Override
    protected  float getInitialRepeatDelay() {
        return 0;
    }

}
