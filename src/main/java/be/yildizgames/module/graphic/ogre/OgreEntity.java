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

package be.yildizgames.module.graphic.ogre;

import be.yildizgames.common.jni.Native;
import be.yildizgames.common.jni.NativePointer;
import be.yildizgames.module.graphic.material.Material;
import jni.JniEntity;

/**
 * Associated to an Ogre:Entity.
 *
 * @author Grégory Van den Borre
 */
public final class OgreEntity implements Native {

    /**
     * Pointer address to the native code Ogre::Entity.
     */
    private final NativePointer pointer;

    /**
     * Associated ogre node.
     */
    private final OgreNodeBase node;

    private final JniEntity jni = new JniEntity();

    public OgreEntity(NativePointer pointer, OgreNodeBase node) {
        super();
        this.pointer = pointer;
        this.node = node;
    }

    /**
     * Set the material to this 3d object.
     *
     * @param material New material to use.
     */
    public void setMaterial(final Material material) {
        this.jni.setMaterial(this.pointer.getPointerAddress(), ((OgreMaterial) material).getPointer().getPointerAddress());
    }

    /**
     * @return The parent Ogre::SceneNode name.
     */
    public String getParentName() {
        return this.jni.getParentSceneNode(this.pointer.getPointerAddress());
    }

    /**
     * Set the entity casting shadows.
     *
     * @param cast <code>true</code> to cast shadow, <code>false</code> to stop casting.
     */
    public void castShadow(final boolean cast) {
        this.jni.castShadow(this.pointer.getPointerAddress(), cast);
    }

    /**
     * Set the entity to be not pickable.
     */
    public void setUnpickable() {
        this.jni.setUnpickable(this.pointer.getPointerAddress());
    }

    /**
     * Render the entity behind other.
     */
    public void renderBehind() {
        this.jni.setRenderQueue(this.pointer.getPointerAddress(), 8);
    }

    /**
     * Set a GPU parameter on this entity.
     *
     * @param index Parameter index.
     * @param v1 Float4 1st value.
     * @param v2 Float4 2nd value.
     * @param v3 Float4 3rd value.
     * @param v4 Float4 4th value.
     */
    public void setParameter(final int index, final float v1, final float v2, final float v3, final float v4) {
        this.jni.setParameter(this.pointer.getPointerAddress(), index, v1, v2, v3, v4);
    }

    /**
     * Set the maximum distance from where the entity will no longer be rendered.
     *
     * @param distance Maximum rendering distance.
     */
    public void setRenderingDistance(final int distance) {
        this.jni.setRenderingDistance(this.pointer.getPointerAddress(), distance);
    }

    @Override
    public void delete() {
        this.jni.delete(this.pointer.getPointerAddress());
        this.pointer.delete();
    }

    @Override
    public NativePointer getPointer() {
        return this.pointer;
    }

    public OgreNodeBase getNode() {
        return this.node;
    }



}
