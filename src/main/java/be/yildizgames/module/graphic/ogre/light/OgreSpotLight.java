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

package be.yildizgames.module.graphic.ogre.light;

import be.yildizgames.common.geometry.Point3D;
import be.yildizgames.common.jni.NativePointer;
import be.yildizgames.module.graphic.light.SpotLight;
import jni.JniSpotLight;

/**
 * Ogre implementation for a SpotLight.
 *
 * @author Grégory Van den Borre
 */
public final class OgreSpotLight extends SpotLight {

    /**
     * Pointer address to the native code yz::SpotLight.
     */
    private final NativePointer pointer;

    private final JniSpotLight jni = new JniSpotLight();

    /**
     * Full constructor.
     *
     * @param pointerAddress Pointer address to the associated native object.
     * @param name           Light unique name.
     * @param position       Light position.
     * @param direction      Light direction.
     */
    public OgreSpotLight(final NativePointer pointerAddress, final String name, final Point3D position, final Point3D direction) {
        super(name, position, direction);
        this.pointer = pointerAddress;
    }

    @Override
    protected void setDirectionImpl(final Point3D direction) {
        this.jni.setDirection(this.pointer.getPointerAddress(), direction.x, direction.y, direction.z);
    }

    @Override
    protected void setPositionImpl(final Point3D position) {
        this.jni.setPosition(this.pointer.getPointerAddress(), position.x, position.y, position.z);
    }

    @Override
    protected void deleteImpl() {
        this.jni.delete(this.pointer.getPointerAddress());
        this.pointer.delete();
    }
}
