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
import be.yildizgames.module.graphic.material.MaterialEffect;
import be.yildizgames.module.graphic.material.MaterialEffect.EffectType;
import be.yildizgames.module.graphic.material.MaterialPass;
import be.yildizgames.module.graphic.material.MaterialTechnique;
import be.yildizgames.module.graphic.material.TextureUnit;
import jni.JniMaterial;

import java.util.ArrayList;
import java.util.List;

/**
 * Ogre implementation for a material.
 *
 * @author Grégory Van den Borre
 */
public final class OgreMaterial extends Material implements Native {

    /**
     * Pointer address to the associated Ogre::Material.
     */
    private final NativePointer pointer;

    private final JniMaterial jni = new JniMaterial();

    /**
     * Full constructor.
     *
     * @param name Material name, must be unique.
     */
    OgreMaterial(final String name) {
        super(name);
        this.pointer = NativePointer.create(this.jni.createTexture(name));
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
        this.jni.loadTexture(this.pointer.getPointerAddress());
    }

    @Override
    protected Material copyImpl(final String name) {
        final long copyPointer = this.jni.copy(this.pointer.getPointerAddress(), name);
        final long[] copyTechniques = this.jni.getTechniqueList(copyPointer);
        final List<MaterialTechnique> techniqueCopyList = new ArrayList<>(copyTechniques.length);
        for (int techniqueIndex = 0; techniqueIndex < copyTechniques.length; techniqueIndex++) {
            final long[] copyPass = OgreMaterialTechnique.getPassList(copyTechniques[techniqueIndex]);
            final List<MaterialPass> passCopyList = new ArrayList<>(copyPass.length);
            for (int passIndex = 0; passIndex < copyPass.length; passIndex++) {
                final long[] copyUnit = OgreMaterialPass.getUnitList(copyPass[passIndex]);
                final List<TextureUnit> unitCopyList = new ArrayList<>(copyUnit.length);
                for (long aCopyUnit : copyUnit) {
                    final OgreTextureUnit unitCopy = new OgreTextureUnit(aCopyUnit);
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
            return new OgreMaterialTechnique(this.jni.getTechnique(this.pointer.getPointerAddress(), 0), 0);
        }
        return new OgreMaterialTechnique(this.jni.createTechnique(this.pointer.getPointerAddress()), index);
    }

    @Override
    protected void receiveShadowImpl(final boolean receive) {
        this.jni.receiveShadow(this.pointer.getPointerAddress(), receive);
    }

    @Override
    public void delete() {
        this.jni.delete(this.pointer.getPointerAddress());
        this.pointer.delete();
    }

    @Override
    public NativePointer getPointer() {
        return pointer;
    }
}
