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

package be.yildizgames.module.graphic.ogre.particle;

import be.yildizgames.common.gameobject.Movable;
import be.yildizgames.common.geometry.Point3D;
import be.yildizgames.common.jni.Native;
import be.yildizgames.common.jni.NativePointer;
import be.yildizgames.module.graphic.material.Material;
import be.yildizgames.module.graphic.ogre.OgreMaterial;
import be.yildizgames.module.graphic.ogre.OgreNode;
import be.yildizgames.module.graphic.ogre.OgreNodeBase;
import be.yildizgames.module.graphic.particle.ParticleColorAffector;
import be.yildizgames.module.graphic.particle.ParticleEmitter;
import be.yildizgames.module.graphic.particle.ParticleEmitter.EmitterType;
import be.yildizgames.module.graphic.particle.ParticleForceAffector;
import be.yildizgames.module.graphic.particle.ParticleScaleAffector;
import be.yildizgames.module.graphic.particle.ParticleSystem;
import jni.JniParticleSystem;

/**
 * Ogre implementation for the ParticleSystem.
 *
 * @author Grégory Van Den Borre
 */
public final class OgreParticleSystem extends ParticleSystem implements Native {

    /**
     * Pointer for the native object.
     */
    private final NativePointer pointer;

    /**
     * Associated node.
     */
    private OgreNode node;

    private final JniParticleSystem jni = new JniParticleSystem();

    private boolean visible;

    /**
     * Full constructor.
     *
     * @param pointer Pointer to the associated native object.
     * @param node    Node used to move the particle system.
     */
    public OgreParticleSystem(final NativePointer pointer, final OgreNodeBase node) {
        super();
        this.visible = true;
        this.pointer = pointer;
        this.node = node;
        this.jni.attachToNode(this.pointer.getPointerAddress(), this.node.getPointer().getPointerAddress());
    }

    @Override
    protected ParticleEmitter createEmitter(final EmitterType type) {
        final long address = this.jni.createEmitter(this.pointer.getPointerAddress());
        return new OgreParticleEmitter(NativePointer.create(address));
    }

    @Override
    protected ParticleColorAffector createColorAffector() {
        final long address = this.jni.createColorAffector(this.pointer.getPointerAddress());
        return new OgreParticleColorAffector(NativePointer.create(address));
    }

    @Override
    protected ParticleForceAffector createForceAffector() {
        final long address = this.jni.createForceAffector(this.pointer.getPointerAddress());
        return new OgreParticleForceAffector(NativePointer.create(address));
    }

    @Override
    protected ParticleScaleAffector createScaleAffector() {
        final long address = this.jni.createScaleAffector(this.pointer.getPointerAddress());
        return new OgreParticleScaleAffector(NativePointer.create(address));
    }

    @Override
    protected void setMaterialImpl(final Material material) {
        this.jni.setMaterial(this.pointer.getPointerAddress(), OgreMaterial.class.cast(material).getPointer().getPointerAddress());
    }

    @Override
    protected void setOrientationImpl(final Orientation orientation) {
        this.jni.setParticleOrientation(this.pointer.getPointerAddress(), orientation.ordinal());
    }

    @Override
    protected void setQuotaImpl(final int quota) {
        this.jni.setQuota(this.pointer.getPointerAddress(), quota);
    }

    @Override
    protected void setSizeImpl(final float width, final float height) {
        this.jni.setSize(this.pointer.getPointerAddress(), width, height);
    }

    @Override
    public void setPosition(float posX, float posY, float posZ) {
        this.node.setPosition(posX, posY, posZ);
    }

    @Override
    public void setDirection(float dirX, float dirY, float dirZ) {
        this.node.setDirection(dirX, dirY, dirZ);
    }

    @Override
    public NativePointer getPointer() {
        return this.pointer;
    }

    @Override
    public void keepInLocalSpace(final boolean keep) {
        this.jni.keepInLocalSpace(this.pointer.getPointerAddress(), keep);
    }

    @Override
    protected void setOriginImpl(final Origin origin) {
        this.jni.setBillboardOrigin(this.pointer.getPointerAddress(), origin.getValue());
    }

    @Override
    public void detachFromParent() {
        this.node.detachFromParent();
    }

    @Override
    public void addOptionalChild(Movable child) {
        this.node.addOptionalChild(child);
    }

    @Override
    public void addChild(Movable child) {
        this.node.addChild(child);
    }

    @Override
    public void removeChild(Movable child) {
        this.node.removeChild(child);
    }

    @Override
    public Movable getInternal() {
        return this.node;
    }

    @Override
    public final void attachTo(final Movable other) {
        this.node.attachTo(other);
    }

    @Override
    public final void attachToOptional(final Movable other) {
        this.node.attachToOptional(other);
    }

    @Override
    public final Point3D getPosition() {
        return this.node.getPosition();
    }

    @Override
    public final void setPosition(final Point3D position) {
        this.node.setPosition(position);
    }

    @Override
    public final Point3D getAbsolutePosition() {
        return this.node.getAbsolutePosition();
    }

    @Override
    public final Point3D getDirection() {
        return this.node.getDirection();
    }

    @Override
    public final void setDirection(final Point3D direction) {
        this.node.setDirection(direction);
    }

    @Override
    public final Point3D getAbsoluteDirection() {
        return this.node.getAbsoluteDirection();
    }

    @Override
    public final void delete() {
        this.node.delete();
    }

    //public final Node getNode() {
    //    return node;
    //}

    /**
     * Set the object visible.
     */
    public final void show() {
        if (!this.visible) {
            this.node.show();
            this.visible = true;
        }
    }

    /**
     * Set the object invisible.
     */
    public final void hide() {
        if (this.visible) {
            this.node.hide();
            this.visible = false;
        }
    }

    /**
     * @return <code>true</code> if object is currently visible.
     */
    public final boolean isVisible() {
        return this.visible;
    }
}
