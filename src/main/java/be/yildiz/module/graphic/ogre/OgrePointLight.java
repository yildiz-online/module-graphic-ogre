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
import be.yildiz.common.nativeresources.Native;
import be.yildiz.common.nativeresources.NativePointer;
import be.yildiz.common.vector.Point3D;
import be.yildiz.module.graphic.PointLight;

/**
 * Ogre implementation for a PointLight.
 *
 * @author Grégory Van den Borre
 */
final class OgrePointLight extends PointLight implements Native {

    /**
     * Pointer address to the native code YZ::PointLight.
     */
    private final NativePointer pointer;

    /**
     * Full constructor.
     *
     * @param pointerAddress Pointer address to the associated native object.
     * @param name           Light unique name.
     * @param position       Light position.
     */
    OgrePointLight(final NativePointer pointerAddress, final String name, final Point3D position) {
        super(name, position);
        this.pointer = pointerAddress;
    }

    @Override
    protected void deleteImpl() {
        this.delete(this.pointer.getPointerAddress());
        this.pointer.delete();
    }

    @Override
    protected void setPositionImpl(final Point3D position) {
        this.setPosition(this.pointer.getPointerAddress(), position.x, position.y, position.z);
    }

    @Override
    public void setColor(final Color color) {
        this.setColor(this.pointer.getPointerAddress(), color.normalizedRed, color.normalizedGreen, color.normalizedBlue);
    }

    @Override
    public void setAttenuation(final float range, final float constant, final float linear, final float quadratic) {
        this.setAttenuation(this.pointer.getPointerAddress(), range, constant, linear, quadratic);
    }

    @Override
    public void setDebug() {
        this.setDebug(this.pointer.getPointerAddress());
    }

    @Override
    public NativePointer getPointer() {
        return this.pointer;
    }

    /**
     * Set light color in native code.
     *
     * @param address Address of the native YZ::PointLight pointer.
     * @param r       Red value.
     * @param g       Green value.
     * @param b       Blue value.
     */
    private native void setColor(final long address, final float r, final float g, final float b);

    /**
     * Set the light position in native code.
     *
     * @param pointerAddress Address of the native YZ::PointLight pointer.
     * @param x              New X position.
     * @param y              New Y position.
     * @param z              New Z position.
     */
    private native void setPosition(final long pointerAddress, final float x, final float y, final float z);

    /**
     * Delete the object in native code.
     *
     * @param pointerAddress Address of the native YZ::PointLight pointer.
     */
    private native void delete(final long pointerAddress);

    /**
     * Set the light attenuation in native code.
     *
     * @param pointerAddress Address of the native YZ::PointLight pointer.
     * @param range          Light range.
     * @param constant       Constant value.
     * @param linear         Linear value.
     * @param quadratic      Quadratic value.
     */
    private native void setAttenuation(final long pointerAddress, final float range, final float constant, final float linear,
                                       final float quadratic);

    /**
     * Enable debug display in native code.
     *
     * @param pointerAddress Address of the native YZ::PointLight pointer.
     */
    private native void setDebug(final long pointerAddress);
}
