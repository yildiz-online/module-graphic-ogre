/*
 *
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
 *  portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 *  WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT  HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  SOFTWARE.
 *
 *
 */

package be.yildizgames.module.graphic.ogre;

import be.yildizgames.common.model.EntityId;
import be.yildizgames.module.graphic.GraphicObject;
import be.yildizgames.module.graphic.GraphicObjectBuilder;
import be.yildizgames.module.graphic.ogre.impl.OgreSceneManager;

class OgreGraphicObjectBuilder extends GraphicObjectBuilder {

    private final OgreSceneManager sceneManager;

    OgreGraphicObjectBuilder(OgreSceneManager sceneManager) {
        super();
        this.sceneManager = sceneManager;
    }

    public GraphicObject buildMovable() {
        final OgreNodeBase node;
        if(EntityId.isWorld(this.id)) {
            node = this.sceneManager.createMovableNode();
        } else {
            node = this.sceneManager.createMovableNode(id);
        }
        node.setPosition(this.position);
        node.setDirection(this.direction);
        return build(node);
    }

    public GraphicObject buildStatic() {
        final OgreNodeBase node;
        if(EntityId.isWorld(this.id)) {
            node = this.sceneManager.createStaticNode(position, direction);
        } else {
            node = this.sceneManager.createStaticNode(id, position, direction);
        }
        return build(node);
    }

    private GraphicObject build(OgreNodeBase node) {
        final OgreEntity entity;
        if(mesh != null) {
            entity = this.sceneManager.createEntity(mesh, node);
        } else if(box != null) {
            entity = this.sceneManager.createEntity(box, node);
        } else if(sphere != null) {
            entity = this.sceneManager.createEntity(sphere, node);
        } else if(plane != null) {
            entity = this.sceneManager.createEntity(plane, node);
        } else {
            throw new RuntimeException("Missing shape");
        }
        entity.setMaterial(material);
        return new OgreObject(this.id, entity);
    }
}
