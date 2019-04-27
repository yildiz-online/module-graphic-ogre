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

import be.yildizgames.common.file.FileResource;
import be.yildizgames.common.jni.NativePointer;
import be.yildizgames.module.vfs.Vfs;
import be.yildizgames.module.window.ScreenSize;
import be.yildizgames.module.window.WindowHandle;
import jni.JniRoot;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.nio.file.Paths;

/**
 * Access to the Ogre::Root object in native code.
 *
 * @author Grégory Van Den Borre
 */
public final class Root {

    private static final Logger LOGGER = LoggerFactory.getLogger(Root.class);

    private final JniRoot jni = new JniRoot();
    private final Vfs vfs;

    /**
     * Flag to check if initialized or not.
     */
    private boolean initialized;

    /**
     * Simple constructor, call the native constructor to get the pointer to the
     * native object.
     */
    public Root(Vfs vfs) {
        super();
        this.jni.constructor();
        this.jni.initPhysFS();
        this.vfs = vfs;
    }

    /**
     * Load an Ogre plug-in.
     *
     * @param plugin Plug-in name.
     */
    public void setPlugin(final String plugin) {
        if (this.initialized) {
            throw new IllegalStateException("You cannot load plug ins once root is initialized.");
        }
        LOGGER.info("Loading ogre plugin: " + plugin);
        this.jni.loadPlugin(plugin);
    }

    /**
     * Load an Ogre renderer.
     *
     * @param renderer Renderer name to load.
     */
    public void setRenderer(final String renderer) {
        this.jni.loadRenderer(renderer);
        this.initialized = true;
    }

    /**
     * Render the current frame.
     */
    public void render() {
        this.jni.renderOneFrame();
    }

    /**
     * Create a new scene manager, type generic.
     *
     * @param name Scene manager name, must be unique.
     * @return The built SceneManager.
     */
    public NativePointer createScene(final String name) {
        final long pointerAddress = this.jni.createSceneManager(name);
        return NativePointer.create(pointerAddress);
    }

    /**
     * Build a new RenderWindow.
     *
     * @param res    Resolution to use.
     * @param handle Handle to win32 window, if other os is used, the param will be
     *               unused.
     * @return The built render window.
     */
    public RenderWindow createWindow(final ScreenSize res, final WindowHandle handle) {
        this.jni.createRenderWindow(res.width, res.height, handle.value);
        return new RenderWindow();
    }

    /**
     * Build a new RenderWindow using the current GL context.
     *
     * @param res Resolution to use.
     * @return The built render window.
     */
    public RenderWindow createWindow(final ScreenSize res) {
        this.jni.createRenderWindowGlContext(res.width, res.height);
        return new RenderWindow();
    }

    /**
     * Close the root object.
     */
    public void closeRoot() {
        this.jni.close();
    }

    public void addResourcePath(final String name, final String resourcePath, final FileResource.FileType type) {
        if(type == FileResource.FileType.VFS) {
            this.vfs.registerContainer(Paths.get(resourcePath));

        }
        this.jni.addResourcePath(name, resourcePath, type.value);
    }
}
