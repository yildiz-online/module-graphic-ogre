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

import be.yildiz.common.gameobject.Movable;
import be.yildiz.common.nativeresources.Native;
import be.yildiz.common.nativeresources.NativePointer;
import be.yildiz.module.graphic.*;
import be.yildiz.module.graphic.ParticleEmitter.EmitterType;

/**
 * Ogre implementation for the ParticleSystem.
 *
 * @author Grégory Van Den Borre
 */
final class OgreParticleSystem extends AbstractParticleSystem implements Native {

    /**
     * Pointer for the native object.
     */
    private final NativePointer pointer;

    /**
     * Associated node.
     */
    private OgreNode node;

    /**
     * Full constructor.
     *
     * @param pointer Pointer to the associated native object.
     * @param node    Node used to move the particle system.
     */
    OgreParticleSystem(final NativePointer pointer, final OgreNodeBase node) {
        super(node);
        this.pointer = pointer;
        this.node = node;
        this.attachToNode(this.pointer.getPointerAddress(), this.node.getPointer().getPointerAddress());
    }

    @Override
    protected ParticleEmitter createEmitter(final EmitterType type) {
        final long address = this.createEmitter(this.pointer.getPointerAddress());
        return new OgreParticleEmitter(NativePointer.create(address));
    }

    @Override
    protected ParticleColorAffector createColorAffector() {
        final long address = this.createColorAffector(this.pointer.getPointerAddress());
        return new OgreParticleColorAffector(NativePointer.create(address));
    }

    @Override
    protected ParticleForceAffector createForceAffector() {
        final long address = this.createForceAffector(this.pointer.getPointerAddress());
        return new OgreParticleForceAffector(NativePointer.create(address));
    }

    @Override
    protected ParticleScaleAffector createScaleAffector() {
        final long address = this.createScaleAffector(this.pointer.getPointerAddress());
        return new OgreParticleScaleAffector(NativePointer.create(address));
    }

    @Override
    protected void setMaterialImpl(final Material material) {
        this.setMaterial(this.pointer.getPointerAddress(), OgreMaterial.class.cast(material).getPointer().getPointerAddress());
    }

    @Override
    protected void setOrientationImpl(final Orientation orientation) {
        this.setParticleOrientation(this.pointer.getPointerAddress(), orientation.ordinal());
    }

    @Override
    protected void setQuotaImpl(final int quota) {
        this.setQuota(this.pointer.getPointerAddress(), quota);
    }

    @Override
    protected void setSizeImpl(final float width, final float height) {
        this.setSize(this.pointer.getPointerAddress(), width, height);
    }

    @Override
    protected void showImpl() {
        this.show(this.pointer.getPointerAddress());
    }

    @Override
    protected void hideImpl() {
        this.hide(this.pointer.getPointerAddress());
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
        this.keepInLocalSpace(this.pointer.getPointerAddress(), keep);
    }

    @Override
    protected void setOriginImpl(final Origin origin) {
        this.setBillboardOrigin(this.pointer.getPointerAddress(), origin.getValue());
    }

    /**
     * Create an emitter in native code.
     *
     * @param pointer Pointer address to the native object.
     * @return The emitter pointer address.
     */
    private native long createEmitter(final long pointer);

    /**
     * Create a color affector in native code.
     *
     * @param pointer Address to the native object.
     * @return The color affector pointer address.
     */
    private native long createColorAffector(final long pointer);

    /**
     * Create a force affector in native code.
     *
     * @param pointer Address to the native object.
     * @return The force affector pointer address.
     */
    private native long createForceAffector(final long pointer);

    /**
     * Create a scale affector in native code.
     *
     * @param pointer Address to the native object.
     * @return The scale affector pointer address.
     */
    private native long createScaleAffector(final long pointer);

    /**
     * Set the particle size in native code.
     *
     * @param pointer Address to the native object.
     * @param width   Particle width.
     * @param height  Particle height.
     */
    private native void setSize(final long pointer, final float width, final float height);

    /**
     * Set the particle material in native code.
     *
     * @param pointer  Address to the native object.
     * @param material Material to use.
     */
    private native void setMaterial(final long pointer, final long material);

    /**
     * Set the particle quota in native code.
     *
     * @param pointer Address to the native object.
     * @param quota   Quota to set.
     */
    private native void setQuota(final long pointer, final int quota);

    /**
     * Show the particle in native code.
     *
     * @param pointer Address to the native object.
     */
    private native void show(final long pointer);

    /**
     * Hide the particle system in native code.
     *
     * @param pointer Address to the native object.
     */
    private native void hide(final long pointer);

    /**
     * Set the particle billboard orientation in native code.
     *
     * @param pointer         Address to the native object.
     * @param orientationType Orientation type.
     */
    private native void setParticleOrientation(final long pointer, final int orientationType);

    /**
     * Set the billboard origin.
     *
     * @param pointerAddress Address to the native object.
     * @param value          Origin enum value.
     */
    private native void setBillboardOrigin(final long pointerAddress, final int value);

    /**
     * Attach this object to a node in native code.
     *
     * @param pointer     Address to the native object.
     * @param nodePointer Address to the native node object.
     */
    private native void attachToNode(final long pointer, final long nodePointer);

    /**
     * Keep particle in local space.
     *
     * @param pointer Address to the native object.
     * @param keep    <code>true</code> to keep.
     */
    private native void keepInLocalSpace(final long pointer, final boolean keep);

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
}
