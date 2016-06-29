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
import lombok.AccessLevel;
import lombok.Getter;

/**
 * A ViewPort is the display associated to a camera.
 *
 * @author Grégory Van den Borre
 */
final class ViewPort implements Native {

    /**
     * Pointer for the native object.
     */
    @Getter
    private final NativePointer pointer;

    /**
     * Associated camera.
     */
    @Getter(value = AccessLevel.PACKAGE)
    private OgreCamera camera;

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
        this.setActive(this.pointer.address, active);
    }

    /**
     * Set the associated camera to this viewport.
     *
     * @param value Camera to associate.
     */
    void setCamera(final OgreCamera value) {
        this.camera = value;
        this.setCamera(this.pointer.address, this.camera.getPointer().address);
    }

    @Override
    public void delete() {
        this.delete(this.pointer.address);
    }

    /**
     * Delete the object in native code.
     *
     * @param address Address of the native object.
     */
    private native void delete(final long address);

    /**
     * Change the camera associated to this view port in native code.
     *
     * @param pointer    This object pointer address.
     * @param camPointer The pointer to the camera to associate.
     */
    private native void setCamera(final long pointer, final long camPointer);

    /**
     * Set the active state in native code.
     *
     * @param pointer Pointer to the native object.
     * @param active  Flag to set active or not the viewport.
     */
    private native void setActive(final long pointer, final boolean active);

}
