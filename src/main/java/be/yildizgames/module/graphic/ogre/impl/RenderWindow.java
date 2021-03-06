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

import be.yildizgames.common.jni.NativePointer;
import be.yildizgames.module.graphic.ogre.OgreCamera;
import jni.JniRenderWindow;

/**
 * Access to the Render Window object in native code.
 *
 * @author Grégory Van Den Borre
 */
final class RenderWindow implements OgreRenderWindow {

    private final JniRenderWindow jni = new JniRenderWindow();

    /**
     * Full constructor.
     */
    RenderWindow() {
        super();
    }

    /**
     * Build a new viewport.
     *
     * @param camera Camera to use in the viewport.
     * @return The new built ViewPort.
     */
    @Override
    public OgreViewport createViewport(final OgreCamera camera) {
        final long address = this.jni.createViewport(camera.getPointer().getPointerAddress());
        return new ViewPort(NativePointer.create(address), camera);
    }

    /**
     * Print in a file the current display in this window.
     */
    @Override
    public void getPrintScreen() {
        this.jni.printScreen(String.valueOf(System.currentTimeMillis()));
    }

    /**
     * @return The current frame per second rate.
     */
    @Override
    public float getFramerate() {
        return this.jni.getFps();
    }


}
