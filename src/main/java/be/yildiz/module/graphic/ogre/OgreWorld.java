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

import be.yildiz.common.id.EntityId;
import be.yildiz.common.shape.Box;
import be.yildiz.common.shape.Sphere;
import be.yildiz.common.vector.Point3D;
import be.yildiz.module.graphic.ClientGameEntity;
import be.yildiz.module.graphic.ClientWorld;
import be.yildiz.module.graphic.Material;
import lombok.Getter;

import java.security.InvalidParameterException;

/**
 * Ogre implementation for a ClientWorld.
 *
 * @author Grégory Van den Borre
 */
public final class OgreWorld extends AbstractOgreWorld implements ClientWorld {

    /**
     * The scene manager manage the graphic part of this world.
     */
    private final OgreSceneManager sceneManager;

    @Getter
    private boolean debug;

    /**
     * Full constructor.
     *
     * @param graphic Manage the graphic part of this world.
     */
    public OgreWorld(final OgreSceneManager graphic) {
        super(graphic);
        this.sceneManager = graphic;
    }

    @Override
    public ClientGameEntity createStaticObject(final EntityId id, final Box box, final Material material, final Point3D position, final Point3D direction) {
        final OgreNode node = this.sceneManager.createNode(id);
        final OgreEntity entity = this.sceneManager.createEntity(box, node);
        entity.setMaterial(material);
        node.setPosition(position);
        node.setDirection(direction);
        return new OgreStaticObject(id, entity);
    }

    @Override
    public ClientGameEntity createStaticObject(final EntityId id, final Sphere sphere, final Material material, final Point3D position, final Point3D direction) {
        final OgreNode node = this.sceneManager.createNode(id);
        final OgreEntity entity = this.sceneManager.createEntity(sphere, node);
        entity.setMaterial(material);
        node.setPosition(position);
        node.setDirection(direction);
        return new OgreStaticObject(id, entity);
    }

    @Override
    public ClientGameEntity createMovableObject(final EntityId id, final Box box, final Material material, final Point3D position) {
        final OgreNode node = this.sceneManager.createNode(id);
        final OgreEntity entity = this.sceneManager.createEntity(box, node);
        entity.setMaterial(material);
        node.setPosition(position);
        return new OgreMovableObject(id, entity);
    }

    @Override
    public ClientGameEntity createMovableObject(final EntityId id, final Sphere sphere, final Material material, final Point3D position) {
        final OgreNode node = this.sceneManager.createNode(id);
        final OgreEntity entity = this.sceneManager.createEntity(sphere, node);
        entity.setMaterial(material);
        node.setPosition(position);
        return new OgreMovableObject(id, entity);
    }

    @Override
    public void setDebugMode() {
        this.debug = true;
    }

    @Override
    public void serializeShapeFromMesh(final String mesh, final String file, final String name) {
        throw new InvalidParameterException();
    }

    /**
     * Create a body with an associated node.
     *
     * @param worldPointer Pointer to the btworld object.
     * @param shapePointer Pointer of the shape to build the btbody.
     * @param id           Id to assign.
     * @param mass         Object mass.
     * @param nodePointer  Pointer to the associated Ogre::SceneNode.
     * @return A pointer to the btbody object built in native code.
     */
    private native long createDynamicBody(final long worldPointer, final long shapePointer, final long id, final float mass, final long nodePointer);

    /**
     * Set debug mode for graphic and physic worlds in native code.
     *
     * @param physicWorldPointer  Pointer to the btworld object.
     * @param sceneManagerPointer Pointer to the Ogre::SceneManager object.
     */
    private native void setDebugMode(final long physicWorldPointer, final long sceneManagerPointer);
}
