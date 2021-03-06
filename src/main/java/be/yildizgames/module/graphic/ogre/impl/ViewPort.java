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

package be.yildizgames.module.graphic.ogre.impl;

import be.yildizgames.common.jni.Native;
import be.yildizgames.common.jni.NativePointer;
import be.yildizgames.module.graphic.ogre.OgreCamera;
import jni.JniViewPort;

/**
 * A ViewPort is the display associated to a camera.
 *
 * @author Grégory Van den Borre
 */
public final class ViewPort implements Native, OgreViewport {

    /**
     * Pointer for the native object.
     */
    private final NativePointer pointer;

    /**
     * Associated camera.
     */
    private OgreCamera camera;

    private final JniViewPort jni = new JniViewPort();

    /**
     * Full constructor.
     *
     * @param pointer Pointer to the native object.
     * @param cam     Camera associated to this viewport.
     */
    ViewPort(final NativePointer pointer, final OgreCamera cam) {
        super();
        this.pointer = pointer;
        this.camera = cam;
    }

    /**
     * Set this viewport being active or not.
     *
     * @param active <code>true</code> to set it active, <code>false</code> to deactivate it.
     */
    void setActive(final boolean active) {
        this.jni.setActive(this.pointer.getPointerAddress(), active);
    }

    /**
     * Set the associated camera to this viewport.
     *
     * @param value Camera to associate.
     */
    void setCamera(final OgreCamera value) {
        this.camera = value;
        this.jni.setCamera(this.pointer.getPointerAddress(), this.camera.getPointer().getPointerAddress());
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

    OgreCamera getCamera() {
        return this.camera;
    }
}
