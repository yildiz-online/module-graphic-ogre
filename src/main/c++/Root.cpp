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

/**
*@author Grégory Van den Borre
*/

#include "../includes/Root.hpp"
#include <physfs.h>
#include "../includes/PhysFS++.h"
#include "../includes/PhysFSOgre.h"

YZ::Root* YZ::Root::instance = NULL;

YZ::Root::Root() {
    LOG_FUNCTION
    this->root = OGRE_NEW Ogre::Root("", "", "ogre.log");
    this->os = OGRE_NEW Ogre::OverlaySystem();
}

YZ::Root::~Root() {
    LOG_FUNCTION
    OGRE_DELETE this->os;
    OGRE_DELETE this->root;
}

void YZ::Root::initPhysFS() {
    LOG_FUNCTION
    PhysFS::init("");
    PhysFS::registerPhysFSToOgre();
}

void YZ::Root::loadPlugin(const std::string& name) {
    LOG_FUNCTION
    //FIXME use enumeration instead of Strings.
    this->root->loadPlugin(name);
}

void YZ::Root::initialise(const std::string& renderer) {
    LOG_FUNCTION
    //FIXME use enumeration instead of strings
    if(!this->initialized) {
        this->root->loadPlugin(renderer);
        Ogre::RenderSystem* rs = this->root->getAvailableRenderers().front();
        this->root->setRenderSystem(rs);
        this->root->initialise(false);
        this->initialized = true;
    }
}

YZ::SceneManager* YZ::Root::createSceneManager(const std::string& name) {
    LOG_FUNCTION
    Ogre::SceneManager* sm = this->root->createSceneManager(Ogre::ST_GENERIC, name);
    sm->addRenderQueueListener(this->os);
    return new YZ::SceneManager(sm);
}

void YZ::Root::createRenderWindow(const Ogre::Real width, const Ogre::Real height, const long handle) {
    LOG_FUNCTION
    Ogre::NameValuePairList params;
    params["externalWindowHandle"] = Ogre::StringConverter::toString((unsigned int) (handle));
    params["FSAA"] = Ogre::String("4");
    params["vsync"] = Ogre::String("true");
    Ogre::RenderWindow* rw = this->root->createRenderWindow("default", width, height, false, &params);
    YZ::RenderWindow::create(rw);
}

void YZ::Root::createRenderWindow(const Ogre::Real width, const Ogre::Real height) {
    LOG_FUNCTION
    Ogre::NameValuePairList params;
    params["currentGLContext"] = Ogre::String("true");
    Ogre::RenderWindow* rw = this->root->createRenderWindow("default", width, height, false, &params);
    YZ::RenderWindow::create(rw);
}

void YZ::Root::close() {
    LOG_FUNCTION
    this->root->shutdown();
    this->initialized = false;
}

void YZ::Root::addResourcePath(const std::string& name, const std::string& path, const int type) {
    LOG_FUNCTION
    switch (type) {
        case 0:
            this->root->addResourceLocation(path, "FileSystem", name, false);
            break;
        case 1:
            this->root->addResourceLocation(path, "Zip", name, false);
            break;
        case 2:
            PhysFS::addToSearchPath(path);
            this->root->addResourceLocation("", "Package", name, false);
            break;
        default:
            throw std::exception();
            break;
    }
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(name);
}
