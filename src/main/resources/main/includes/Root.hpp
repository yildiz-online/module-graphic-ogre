/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 * Copyright (c) 2019 Grégory Van den Borre
 *
 * More infos available: https://engine.yildiz-games.be
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

#ifndef YZ_ROOT_H
#define YZ_ROOT_H

#define ROOT yz::Root

#include <Ogre.h>
#include <OgreOverlaySystem.h>
#include "RenderWindow.hpp"
#include "SceneManager.hpp"

namespace yz {

class OgreLogger;
class RenderWindow;
class SceneManager;

/**
 * Wrap an Ogre::Root pointer.
 * This class can load plugins and must be initialized with a renderer.
 * @author Grégory Van den Borre
 */
class Root {

public:

    static void create() {
        LOG_FUNCTION
        if(instance == NULL) {
            yz::Root::instance =  new yz::Root();
        }
    }

    static inline yz::Root* get() {
        LOG_FUNCTION
        return yz::Root::instance;
    }

    /**
     * Constructor, create the wrapped Ogre::Root object, an Ogre::OverlaySystem and register the PhysFS VFS.
     */
    Root();

    virtual ~Root();

    void initPhysFS();

    void loadPlugin(const std::string& name);

    void initialise(const std::string& renderer);

    void addResourcePath(const std::string& name, const std::string& path, const int type);

    SceneManager* createSceneManager(const std::string& name);

    //FIXME full screen set to false, why?
    void createRenderWindow(const Ogre::Real width, const Ogre::Real height, const long handle);

    void createRenderWindow(const Ogre::Real width, const Ogre::Real height);

    inline void renderOneFrame() {
        this->root->renderOneFrame();
    }

    void close();

private:


    static yz::Root* instance;

    /**
     * Wrapped Ogre::Root.
     */
    Ogre::Root* root;

    Ogre::OverlaySystem* os;

    /**
    * Flag to check if the root is initialized or not.
    */
    bool initialized = false;
};
}

#endif
