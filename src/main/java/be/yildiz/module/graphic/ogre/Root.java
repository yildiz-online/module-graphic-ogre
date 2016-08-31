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

import be.yildiz.common.Size;
import be.yildiz.common.log.Logger;
import be.yildiz.common.nativeresources.NativePointer;
import be.yildiz.common.resource.FileResource.FileType;
import be.yildiz.module.window.WindowHandle;

import java.security.InvalidParameterException;

/**
 * Access to the Ogre::Root object in native code.
 *
 * @author Grégory Van Den Borre
 */
final class Root {

    /**
     * Flag to check if initialized or not.
     */
    private boolean initialized;

    /**
     * Simple constructor, call the native constructor to get the pointer to the
     * native object.
     */
    Root() {
        super();
        this.constructor();
        this.initPhysFS();
    }

    /**
     * Load an Ogre plug-in.
     *
     * @param plugin Plug-in name.
     */
    void setPlugin(final String plugin) {
        if (this.initialized) {
            throw new InvalidParameterException("You cannot load plug ins once root is initialized.");
        }
        Logger.info("Loading ogre plugin: " + plugin);
        this.loadPlugin(plugin);
    }

    /**
     * Load an Ogre renderer.
     *
     * @param renderer Renderer name to load.
     */
    void setRenderer(final String renderer) {
        this.loadRenderer(renderer);
        this.initialized = true;
    }

    /**
     * Render the current frame.
     */
    void render() {
        this.renderOneFrame();
    }

    /**
     * Create a new scene manager, type generic.
     *
     * @param name Scene manager name, must be unique.
     * @return The built SceneManager.
     */
    NativePointer createScene(final String name) {
        final long pointerAdress = this.createSceneManager(name);
        return NativePointer.create(pointerAdress);
    }

    /**
     * Build a new RenderWindow.
     *
     * @param res    Resolution to use.
     * @param handle Handle to win32 window, if other os is used, the param will be
     *               unused.
     * @return The built render window.
     */
    RenderWindow createWindow(final Size res, final WindowHandle handle) {
        this.createRenderWindow(res.width, res.height, handle.value);
        return new RenderWindow();
    }

    /**
     * Build a new RenderWindow using the current GL context.
     *
     * @param res Resolution to use.
     * @return The built render window.
     */
    RenderWindow createWindow(final Size res) {
        this.createRenderWindowGlContext(res.width, res.height);
        return new RenderWindow();
    }

    /**
     * Close the root object.
     */
    void closeRoot() {
        this.close();
    }

    void addResourcePath(final String name, final String resourcePath, final FileType type) {
        //FIXME value fileType(4) is not supported 
        this.addResourcePath(name, resourcePath, type.value);
    }

    /**
     * Native constructor, instantiate a new YZ::Root.
     */
    private native void constructor();

    /**
     * Load an ogre plugin in native code.
     *
     * @param plugin Plugin name.
     */
    private native void loadPlugin(final String plugin);

    /**
     * Load an ogre renderer in native code.
     *
     * @param renderer Renderer name.
     */
    private native void loadRenderer(final String renderer);

    /**
     * Render the current frame in native code.
     */
    private native void renderOneFrame();

    /**
     * Add a new folder to be used as graphic container.
     *
     * @param name         Name associated to the group of resources.
     * @param resourcePath Path to the folder.
     * @param type         Resource type value.
     */
    private native void addResourcePath(final String name, final String resourcePath, final int type);

    /**
     * Build a generic scene manager in native code.
     *
     * @param name Scene manager name, must be unique.
     * @return The pointer address of the scene manager native object.
     */
    private native long createSceneManager(final String name);

    /**
     * Build a render window in native code.
     *
     * @param width  RenderWindow resolution width.
     * @param heigth RenderWindow resolution height.
     * @param handle Handle to the win32 window containing the render window, not
     *               used for other OS.
     */
    private native void createRenderWindow(final int width, final int heigth, final long handle);

    /**
     * Build a render window in native code using the current GL context.
     *
     * @param width  RenderWindow resolution width.
     * @param heigth RenderWindow resolution height.
     */
    private native void createRenderWindowGlContext(final int width, final int heigth);

    /**
     * Close the root object in native code.
     */
    private native void close();

    /**
     * Initialize the physFS virtual file system capabilities.
     */
    private native void initPhysFS();

}
