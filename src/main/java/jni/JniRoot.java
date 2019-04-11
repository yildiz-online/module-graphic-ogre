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

package jni;

/**
 * @author Grégory Van den Borre
 */
public class JniRoot {

    /**
     * Native constructor, instantiate a new yz::Root.
     */
    public native void constructor();

    /**
     * Load an ogre plugin in native code.
     *
     * @param plugin Plugin name.
     */
    public native void loadPlugin(final String plugin);

    /**
     * Load an ogre renderer in native code.
     *
     * @param renderer Renderer name.
     */
    public native void loadRenderer(final String renderer);

    /**
     * Render the current frame in native code.
     */
    public native void renderOneFrame();

    /**
     * Add a new folder to be used as graphic container.
     *
     * @param name         Name associated to the group of resources.
     * @param resourcePath Path to the folder.
     * @param type         Resource type value.
     */
    public native void addResourcePath(final String name, final String resourcePath, final int type);

    /**
     * Build a generic scene manager in native code.
     *
     * @param name Scene manager name, must be unique.
     * @return The pointer address of the scene manager native object.
     */
    public native long createSceneManager(final String name);

    /**
     * Build a render window in native code.
     *
     * @param width  RenderWindow resolution width.
     * @param height RenderWindow resolution height.
     * @param handle Handle to the win32 window containing the render window, not
     *               used for other OS.
     */
    public native void createRenderWindow(final int width, final int height, final long handle);

    /**
     * Build a render window in native code using the current GL context.
     *
     * @param width  RenderWindow resolution width.
     * @param height RenderWindow resolution height.
     */
    public native void createRenderWindowGlContext(final int width, final int height);

    /**
     * Close the root object in native code.
     */
    public native void close();

    /**
     * Initialize the physFS virtual file system capabilities.
     */
    public native void initPhysFS(long vfsPointer);
}
