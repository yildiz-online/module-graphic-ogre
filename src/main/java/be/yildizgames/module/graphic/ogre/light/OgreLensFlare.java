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
import be.yildizgames.common.jni.Native;
import be.yildizgames.common.jni.NativePointer;
import be.yildizgames.module.graphic.light.LensFlare;
import jni.JniLensFlare;

/**
 * Ogre implementation for a Lens flare.
 *
 * @author Grégory Van den Borre
 */
public final class OgreLensFlare extends LensFlare implements Native {

    /**
     * Pointer address to the native code yz::LensFlare.
     */
    private final NativePointer pointer;

    private final JniLensFlare jni = new JniLensFlare();

    /**
     * Full constructor.
     *
     * @param pointerAddress Pointer address to the associated native object.
     * @param position       lens flare position.
     */
    public OgreLensFlare(final NativePointer pointerAddress, final Point3D position) {
        super(position);
        this.pointer = pointerAddress;
    }

    @Override
    protected void setPositionImpl(final Point3D position) {
        this.jni.setPosition(this.pointer.getPointerAddress(), position.x, position.y, position.z);
    }

    @Override
    public void setStreakSize(final float w, final float h) {
        this.jni.setStreakSize(this.pointer.getPointerAddress(), w, h);
    }

    @Override
    public void setLightSize(final float w, final float h) {
        this.jni.setLightSize(this.pointer.getPointerAddress(), w, h);
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
