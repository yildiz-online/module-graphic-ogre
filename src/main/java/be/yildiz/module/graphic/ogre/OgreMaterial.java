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

package be.yildiz.module.graphic.ogre;

import be.yildiz.module.graphic.Material;
import be.yildiz.module.graphic.MaterialEffect;
import be.yildiz.module.graphic.MaterialEffect.EffectType;
import be.yildiz.module.graphic.MaterialPass;
import be.yildiz.module.graphic.MaterialTechnique;
import be.yildiz.module.graphic.TextureUnit;
import be.yildizgames.common.collection.Lists;
import be.yildizgames.common.nativeresources.Native;
import be.yildizgames.common.nativeresources.NativePointer;

import java.util.List;

/**
 * Ogre implementation for a material.
 *
 * @author Grégory Van den Borre
 */
final class OgreMaterial extends Material implements Native {

    /**
     * Pointer address to the associated Ogre::Material.
     */
    private final NativePointer pointer;

    /**
     * Full constructor.
     *
     * @param name Material name, must be unique.
     */
    OgreMaterial(final String name) {
        super(name);
        this.pointer = NativePointer.create(this.createTexture(name));
        this.createTechnique();
    }

    /**
     * Copy constructor.
     *
     * @param name           Material name, must be unique.
     * @param pointerAddress Address to the native object.
     * @param list           List of the copied techniques to match this object with the native part.
     */
    private OgreMaterial(final String name, final long pointerAddress, final List<MaterialTechnique> list) {
        super(name, list);
        this.pointer = NativePointer.create(pointerAddress);
    }

    @Override
    public MaterialEffect addEffect(final EffectType type, final long time) {
        // FIXME implements
        // return new OgreMaterialEffect(this, time);
        return null;
    }

    @Override
    protected void loadImpl() {
        this.loadTexture(this.pointer.getPointerAddress());
    }

    @Override
    protected Material copyImpl(final String name) {
        final long copyPointer = this.copy(this.pointer.getPointerAddress(), name);
        final long[] copyTechniques = this.getTechniqueList(copyPointer);
        final List<MaterialTechnique> techniqueCopyList = Lists.newList(copyTechniques.length);
        for (int techniqueIndex = 0; techniqueIndex < copyTechniques.length; techniqueIndex++) {
            final long[] copyPass = OgreMaterialTechnique.getPassList(copyTechniques[techniqueIndex]);
            final List<MaterialPass> passCopyList = Lists.newList(copyPass.length);
            for (int passIndex = 0; passIndex < copyPass.length; passIndex++) {
                final long[] copyUnit = OgreMaterialPass.getUnitList(copyPass[passIndex]);
                final List<TextureUnit> unitCopyList = Lists.newList(copyUnit.length);
                for (int unitIndex = 0; unitIndex < copyUnit.length; unitIndex++) {
                    final OgreTextureUnit unitCopy = new OgreTextureUnit(copyUnit[unitIndex]);
                    unitCopyList.add(unitCopy);
                }
                final OgreMaterialPass passCopy = new OgreMaterialPass(copyPass[passIndex], passIndex, unitCopyList);
                passCopyList.add(passCopy);
            }
            final OgreMaterialTechnique techniqueCopy = new OgreMaterialTechnique(copyTechniques[techniqueIndex], techniqueIndex, passCopyList);
            techniqueCopyList.add(techniqueCopy);
        }
        return new OgreMaterial(name, copyPointer, techniqueCopyList);
    }

    /**
     * Ogre create a default technique for every material, if index is 0, this technique will be retrieved, otherwise, a new one will be created.
     *
     * @param index Technique index.
     * @return The Created or retrieved technique.
     */
    @Override
    protected OgreMaterialTechnique createTechniqueImpl(final int index) {
        if (index == 0) {
            return new OgreMaterialTechnique(this.getTechnique(this.pointer.getPointerAddress(), 0), 0);
        }
        return new OgreMaterialTechnique(this.createTechnique(this.pointer.getPointerAddress()), index);
    }

    @Override
    protected void receiveShadowImpl(final boolean receive) {
        this.receiveShadow(this.pointer.getPointerAddress(), receive);
    }

    @Override
    public void delete() {
        this.delete(this.pointer.getPointerAddress());
        this.pointer.delete();
    }

    @Override
    public NativePointer getPointer() {
        return pointer;
    }

    /**
     * Delete the object in native code.
     *
     * @param address Address of the native object.
     */
    private native void delete(final long address);

    /**
     * Create a new Ogre::Material in native code.
     *
     * @param name Material name, must be unique.
     * @return A pointer address to the newly created Ogre::Material.
     */
    private native long createTexture(final String name);

    /**
     * Copy this material.
     *
     * @param pointerAddress Address to the native Ogre::Material*.
     * @param name           Copied object name, must be unique.
     * @return A pointer address to the newly created Ogre::Material.
     */
    private native long copy(final long pointerAddress, final String name);

    /**
     * Load the material in native code.
     *
     * @param pointerAddress Address to the native Ogre::Material*.
     */
    private native void loadTexture(final long pointerAddress);

    /**
     * Create a new technique for this material.
     *
     * @param pointerAddress Address to the native Ogre::Material*.
     * @return A pointer address to the newly created Ogre::Technique.
     */
    private native long createTechnique(final long pointerAddress);

    /**
     * Retrieve a technique in native from its index.
     *
     * @param pointerAddress Address to the native Ogre::Material*.
     * @param index          Index of the technique to retrieve.
     * @return A pointer address to the retrieved Ogre::Technique.
     */
    private native long getTechnique(final long pointerAddress, final int index);

    /**
     * Get all techniques for this material.
     *
     * @param pointerAddress Address to the native Ogre::Material*.
     * @return A list pointer addresses to the retrieved Ogre::Technique.
     */
    private native long[] getTechniqueList(final long pointerAddress);

    /**
     * Set the material receive or not shadows.
     *
     * @param pointerAddress Address to the native Ogre::Material*.
     * @param receive        <code>true</code> to receive shadows.
     */
    private native void receiveShadow(final long pointerAddress, final boolean receive);
}
