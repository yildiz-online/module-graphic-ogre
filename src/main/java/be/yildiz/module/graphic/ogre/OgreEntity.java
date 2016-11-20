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

import be.yildiz.common.nativeresources.Native;
import be.yildiz.common.nativeresources.NativePointer;
import be.yildiz.module.graphic.Material;
import lombok.AllArgsConstructor;
import lombok.Getter;

/**
 * Associated to an Ogre:Entity.
 *
 * @author Grégory Van den Borre
 */
@AllArgsConstructor
public final class OgreEntity implements Native {

    /**
     * Pointer address to the native code Ogre::Entity.
     */
    @Getter
    private final NativePointer pointer;

    /**
     * Associated ogre node.
     */
    @Getter
    private final OgreNode node;

    /**
     * Set the material to this 3d object.
     *
     * @param material New material to use.
     */
    public void setMaterial(final Material material) {
        this.setMaterial(this.pointer.getPointerAddress(), OgreMaterial.class.cast(material).getPointer().getPointerAddress());
    }

    /**
     * @return The parent Ogre::SceneNode name.
     */
    public String getParentName() {
        return this.getParentSceneNode(this.pointer.getPointerAddress());
    }

    /**
     * Set the entity casting shadows.
     *
     * @param cast <code>true</code> to cast shadow, <code>false</code> to stop casting.
     */
    public void castShadow(final boolean cast) {
        this.castShadow(this.pointer.getPointerAddress(), cast);
    }

    /**
     * Set the entity to be not pickable.
     */
    public void setUnpickable() {
        this.setUnpickable(this.pointer.getPointerAddress());
    }

    /**
     * Render the entity behind other.
     */
    public void renderBehind() {
        this.setRenderQueue(this.pointer.getPointerAddress(), 8);
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
        this.setParameter(this.pointer.getPointerAddress(), index, v1, v2, v3, v4);
    }

    /**
     * Set the maximum distance from where the entity will no longer be rendered.
     *
     * @param distance Maximum rendering distance.
     */
    public void setRenderingDistance(final int distance) {
        this.setRenderingDistance(this.pointer.getPointerAddress(), distance);
    }

    @Override
    public void delete() {
        this.delete(this.pointer.getPointerAddress());
        this.pointer.delete();
    }

    /**
     * Delete the object in native code.
     *
     * @param address Address of the native object.
     */
    private native void delete(final long address);

    /**
     * Get the parent scene node name.
     *
     * @param pointerAddress Address of the native Ogre::Entity pointer.
     * @return Ogre::Entity::getParentSceneNode()->getName().
     */
    private native String getParentSceneNode(final long pointerAddress);

    /**
     * Set the Ogre::Entity casts shadows.
     *
     * @param pointerAddress Address of the native Ogre::Entity pointer.
     * @param cast           <code>true</code> to cast shadow, <code>false</code> to stop casting.
     */
    private native void castShadow(final long pointerAddress, final boolean cast);

    /**
     * Set a Material on this object.
     *
     * @param pointerAddress Address of the native Ogre::Entity pointer.
     * @param material       Material to set.
     */
    private native void setMaterial(final long pointerAddress, final long material);

    /**
     * Set the Ogre::Entity to be ignored by ray picking.
     *
     * @param pointerAddress Address of the native Ogre::Entity pointer.
     */
    private native void setUnpickable(final long pointerAddress);

    /**
     * Set a GPU program parameter.
     *
     * @param pointerAddress Address of the native Ogre::Entity pointer.
     * @param index          Parameter index.
     */
    private native void setParameter(final long pointerAddress, final int index, final float v1, final float v2, final float v3, final float v4);

    /**
     * Set the maximum distance from where the entity will no longer be rendered.
     *
     * @param pointer  Address of the native Entity pointer.
     * @param distance Maximum rendering distance.
     */
    private native void setRenderingDistance(final long pointer, final int distance);

    /**
     * Set the object to be rendered behind the other.
     *
     * @param pointer Address of the native Entity pointer.
     * @param index   Z position(0 = background, 105 = max).
     */
    private native void setRenderQueue(final long pointer, final int index);

}
