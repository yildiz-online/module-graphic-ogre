/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 * Copyright (c) 2017 Grégory Van den Borre
 *
 * More infos available: https://www.yildiz-games.be
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without
 * limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT  HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  SOFTWARE.
 */

package be.yildiz.module.graphic.ogre;

import be.yildiz.common.Color;
import be.yildiz.common.Size;
import be.yildiz.common.exeption.NativeException;
import be.yildiz.common.log.Logger;
import be.yildiz.common.nativeresources.NativeResourceLoader;
import be.yildiz.common.resource.FileResource.FileType;
import be.yildiz.common.util.Checker;
import be.yildiz.common.util.Util;
import be.yildiz.module.graphic.*;
import be.yildiz.module.graphic.Shader.FragmentProfileList;
import be.yildiz.module.graphic.Shader.ShaderType;
import be.yildiz.module.graphic.Shader.VertexProfileList;
import be.yildiz.module.window.WindowEngine;
import be.yildiz.module.window.dummy.DummyWindowEngine;

import java.io.File;

/**
 * Implementation of the graphic engine based on Ogre.
 *
 * @author Grégory Van Den Borre
 */
public final class OgreGraphicEngine implements GraphicEngine {

    /**
     * Local part of the native Ogre::Root object, mainly used to build renderer, scene manager,....
     */
    private final Root root;

    /**
     * Ogre render window.
     */
    private final OgreRenderWindow renderWindow;

    private final OgreGuiBuilder guiBuilder;
    /**
     * Screen size.
     */
    private final Size size;
    private final NativeResourceLoader nativeResourceLoader;
    private final WindowEngine windowEngine;
    /**
     * Only one can be created at a time.
     */
    private SelectionRectangle selection;

    /**
     * Simple constructor.
     *
     * @param windowEngine WindowEngine wrapping this graphic context.
     * @throws NullPointerException If windowEngine is null.
     */
    //@Ensures this.size == windowEngine.size
    //@Ensures this.root != null
    public OgreGraphicEngine(final WindowEngine windowEngine, NativeResourceLoader nativeResourceLoader) {
        super();
        this.size = windowEngine.getScreenSize();
        Logger.info("Initializing Ogre graphic engine...");
        nativeResourceLoader.loadBaseLibrary("libgcc_s_sjlj-1", "libstdc++-6");
        nativeResourceLoader.loadLibrary("libphysfs", "OgreMain", "OgreOverlay", "libyildizogre");
        this.nativeResourceLoader = nativeResourceLoader;
        this.root = new Root();
        this.loadPlugins();
        this.loadRenderer();
        if (Util.isLinux()) {
            this.renderWindow = this.root.createWindow(this.size);
        } else {
            this.renderWindow = this.root.createWindow(this.size, windowEngine.getHandle());
        }
        this.guiBuilder = new OgreGuiBuilder(this.size);
        this.windowEngine = windowEngine;
        Logger.info("Ogre graphic engine initialized.");
    }

    private OgreGraphicEngine(NativeResourceLoader loader) {
        super();
        this.size = new Size(0);
        this.nativeResourceLoader = loader;
        Logger.info("Initializing Headless Ogre graphic engine...");
        nativeResourceLoader.loadBaseLibrary("libgcc_s_sjlj-1", "libstdc++-6");
        nativeResourceLoader.loadLibrary("libphysfs", "OgreMain", "OgreOverlay", "libyildizogre");
        this.root = new Root();
        this.loadPlugins();
        this.loadRenderer();
        this.renderWindow = new DummyRenderWindow();
        this.guiBuilder = new OgreGuiBuilder(this.size);
        this.windowEngine = new DummyWindowEngine();
        Logger.info("Headless Ogre graphic engine initialized.");
    }

    /**
     * Build a headless engine, to be used to test on headless system like CI server.
     * @param nativeResourceLoader Loader for the native libraries.
     * @return A headless graphic engine for testing.
     */
    public static OgreGraphicEngine headless(NativeResourceLoader nativeResourceLoader) {
        return new OgreGraphicEngine(nativeResourceLoader);
    }

    private void loadPlugins() {
        this.root.setPlugin(this.nativeResourceLoader.getLibPath("Plugin_ParticleFX"));
        //this.root.setPlugin(NativeResourceLoader.getLibPath("Plugin_CgProgramManager"));
    }

    private void loadRenderer() {
        try {
            this.root.setRenderer(this.nativeResourceLoader.getLibPath("RenderSystem_GL"));
        } catch (NativeException e) {
            Logger.error(e);
        }
    }

    @Override
    public SelectionRectangle createSelectionRectangle(final Material texture, final Material material2) {
        if (this.selection == null) {
            this.selection = new OgreSelectionRectangle(texture, material2);
        }
        return this.selection;
    }

    @Override
    public OgreSceneManager createGraphicWorld(final String name, final ShadowType shadowType) {
        OgreSceneManager sm = new OgreSceneManager(this.root.createScene(name), this.renderWindow, this.size.width, this.size.height);
        sm.setShadowType(shadowType);
        return sm;
    }

    @Override
    public void close() {
        this.root.closeRoot();
    }

    @Override
    public void printScreen() {
        this.renderWindow.getPrintScreen();
    }

    @Override
    public void update() {
        this.root.render();
    }

    @Override
    public void addResourcePath(final String name, final String path, final FileType type) {
        String[] cpEntries = System.getProperty("java.class.path", "").split(File.pathSeparator);
        boolean found = false;
        for (String cpEntry : cpEntries) {
            if (!cpEntry.contains(".jar")) {
                cpEntry = cpEntry.replace("\\", "/").replace("/target/classes", "/");
                if (new File(cpEntry + path).exists()) {
                    this.root.addResourcePath(name, cpEntry + path, type);
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            this.root.addResourcePath(name, path, type);
        }
    }

    @Override
    public Material createMaterial(final String name) {
        return new OgreMaterial(name);
    }

    @Override
    public OgreSkybox createSkybox(final String name, final String path) {
        return new OgreSkybox(name, path);
    }

    @Override
    public Font createFont(String name, String path, int size, Color color) {
        Checker.exceptionNotGreaterThanZero(size);
        assert name != null;
        assert path != null;
        assert  color != null;
        OgreFont font = new OgreFont(name, path, size, color);
        font.load();
        return font;
    }

    @Override
    public float getFPS() {
        return this.renderWindow.getFramerate();
    }

    @Override
    public Shader createFragmentShader(final String name, final String file, final String entry, final FragmentProfileList profile) {
        return new OgreShader(name, file, entry, ShaderType.FRAGMENT, profile);
    }

    @Override
    public Shader createVertexShader(final String name, final String file, final String entry, final VertexProfileList profile) {
        return new OgreShader(name, file, entry, ShaderType.VERTEX, profile);
    }

    @Override
    public ClientWorld createWorld() {
        OgreSceneManager graphic = this.createGraphicWorld("sc", ShadowType.NONE);
        return new OgreWorld(graphic);
    }

    @Override
    public Size getScreenSize() {
        return this.size;
    }

    @Override
    public WindowEngine getWindowEngine() {
        return this.windowEngine;
    }

    @Override
    public OgreGuiBuilder getGuiBuilder() {
        return guiBuilder;
    }
}
