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

package be.yildizgames.module.graphic.ogre;

import be.yildizgames.common.file.ResourcePath;
import be.yildizgames.common.libloader.NativeResourceLoader;
import be.yildizgames.common.os.SystemUtil;
import be.yildizgames.common.util.Checker;
import be.yildizgames.module.color.Color;
import be.yildizgames.module.graphic.BaseGraphicEngine;
import be.yildizgames.module.graphic.Font;
import be.yildizgames.module.graphic.ShadowType;
import be.yildizgames.module.graphic.gui.GuiFactory;
import be.yildizgames.module.graphic.material.Material;
import be.yildizgames.module.graphic.misc.SelectionRectangle;
import be.yildizgames.module.graphic.ogre.impl.OgreRenderWindow;
import be.yildizgames.module.graphic.ogre.impl.OgreSceneManager;
import be.yildizgames.module.graphic.ogre.impl.Root;
import be.yildizgames.module.window.BaseWindowEngine;
import be.yildizgames.module.window.RegisteredView;
import be.yildizgames.module.window.ScreenSize;
import be.yildizgames.module.window.widget.WindowShell;
import be.yildizgames.module.window.widget.WindowShellFactory;
import be.yildizgames.module.window.widget.WindowShellOptions;

import java.io.File;

/**
 * Implementation of the graphic engine based on Ogre.
 *
 * @author Grégory Van Den Borre
 */
public final class OgreGraphicEngine extends BaseGraphicEngine {

    private static final System.Logger LOGGER = System.getLogger(OgreGraphicEngine.class.getName());

    /**
     * Local part of the native Ogre::Root object, mainly used to build renderer, scene manager,....
     */
    private final Root root;

    /**
     * Ogre render window.
     */
    private final OgreRenderWindow renderWindow;

    private final OgreGuiFactory guiBuilder;

    private final OgreMaterialManager materialManager;

    private final NativeResourceLoader nativeResourceLoader;

    private final WindowShell shell;

    private final BaseWindowEngine windowEngine;
    /**
     * Only one can be created at a time.
     */
    //FIXME replace by a simple rectangle object
    private SelectionRectangle selection;

    /**
     * Build a graphic engine.
     *
     * @param engine Window engine.
     * @throws AssertionError If any parameter is null.
     */
    //@Ensures this.size == windowEngine.size
    //@Ensures this.root != null
    public OgreGraphicEngine(final BaseWindowEngine engine, NativeResourceLoader nativeResourceLoader) {
        super();
        LOGGER.log(System.Logger.Level.INFO, "Initializing Ogre graphic engine...");
        this.windowEngine = engine;
        var view = new OgreView(WindowShellOptions.FULLSCREEN);
        engine.registerView(view);
        this.shell = view.shell;

        /*shell.addFocusListener(new FocusListener() {
            @Override
            public void onFocusChange(boolean focused) {
                if(focused) {
                    uiShell.requestFocus();
                }
            }
        });*/
        /*this.shell.addKeyListener(new KeyboardListener() {
            @Override
            public boolean keyPressed(char key) {
                uiShell.requestFocus();
                return false;
            }
        });*/
        this.nativeResourceLoader = nativeResourceLoader;

        this.nativeResourceLoader.loadBaseLibrary();
        this.nativeResourceLoader.loadLibrary("OgreMain", "OgreOverlay", "libyildizogre");
        this.root = new Root();
        this.loadPlugins();
        this.loadRenderer();
        if (SystemUtil.isLinux()) {
            this.renderWindow = this.root.createWindow(shell.getSize());
        } else {
            this.renderWindow = this.root.createWindow(shell.getSize(), shell.getHandle());
        }
        this.materialManager = new OgreMaterialManager();
        this.guiBuilder = new OgreGuiFactory(shell.getSize());
        this.guiBuilder.container().withSize(400,400).withBackground(Material.blue()).build().show();
        this.shell.toFront();
        LOGGER.log(System.Logger.Level.INFO, "Initializing Ogre graphic engine complete.");
    }

    public OgreMaterialManager getMaterialManager() {
        return this.materialManager;
    }

    private void loadPlugins() {
        this.root.setPlugin(this.nativeResourceLoader.getLibPath("Plugin_ParticleFX"));
        //this.root.setPlugin(NativeResourceLoader.getLibPath("Plugin_CgProgramManager"));
    }

    private void loadRenderer() {
        try {
            this.root.setRenderer(this.nativeResourceLoader.getLibPath("RenderSystem_GL"));
        } catch (IllegalStateException e) {
            LOGGER.log(System.Logger.Level.ERROR,"Error setting renderer", e);
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
        LOGGER.log(System.Logger.Level.DEBUG,"Creating Ogre SceneManager...");
        OgreSceneManager sm = new OgreSceneManager(name, this.root.createScene(name), this.renderWindow, this.shell.getSize().width, this.shell.getSize().height);
        LOGGER.log(System.Logger.Level.DEBUG,"Creating Ogre SceneManager complete.");
        //sm.setShadowType(shadowType);
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
    public void updateImpl() {
        this.root.render();
    }

    @Override
    public void addResourcePath(final ResourcePath resource) {
        String[] cpEntries = System.getProperty("java.class.path", "").split(File.pathSeparator);
        boolean found = false;
        for (String cpEntry : cpEntries) {
            if (!cpEntry.contains(".jar")) {
                cpEntry = cpEntry.replace("\\", "/").replace("/target/classes", "/");
                if (new File(cpEntry + resource.getPath()).exists()) {
                    this.root.addResourcePath(resource.getName(), cpEntry + resource.getPath(), resource.getType());
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            this.root.addResourcePath(resource.getName(), resource.getPath(), resource.getType());
        }
    }

    @Override
    public OgreSkybox createSkybox(final String name, final String path) {
        return new OgreSkybox(name, path);
    }

    @Override
    public final Font createFont(String name, String path, int size, Color color) {
        Checker.exceptionNotGreaterThanZero(size);
        assert name != null;
        assert path != null;
        assert  color != null;
        OgreFont font = new OgreFont(name, path, size, color);
        font.load();
        return font;
    }

    @Override
    public final float getFPS() {
        return this.renderWindow.getFramerate();
    }

    @Override
    public final OgreWorld createWorld() {
        OgreSceneManager graphic = this.createGraphicWorld("sc", ShadowType.NONE);
        return new OgreWorld(graphic);
    }

    @Override
    public BaseWindowEngine getWindowEngine() {
        return this.windowEngine;
    }

    @Override
    public final ScreenSize getScreenSize() {
        return this.shell.getMonitorSize();
    }

    @Override
    public final GuiFactory getGuiFactory() {
        return guiBuilder;
    }

    private class OgreView implements RegisteredView {

        private final WindowShellOptions[] options;

        private WindowShell shell;

        private OgreView(WindowShellOptions... options) {
            this.options = options;
        }

        @Override
        public void build(WindowShellFactory windowShellFactory) {
            this.shell = windowShellFactory.buildShell(this.options);
        }
    }
}
