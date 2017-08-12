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
import be.yildiz.common.id.EntityId;
import be.yildiz.common.log.Logger;
import be.yildiz.common.shape.Box;
import be.yildiz.common.shape.Plane;
import be.yildiz.common.shape.Sphere;
import be.yildiz.common.util.Registerer;
import be.yildiz.common.vector.Point3D;
import be.yildiz.module.graphic.*;
import be.yildiz.module.graphic.LensFlare.LensFlareMaterial;

/**
 * Base Ogre implementation for a ClientWorld.
 *
 * @author Grégory Van den Borre
 */
public abstract class AbstractOgreWorld implements GraphicWorld {

    /**
     * The scene manager manage the graphic part of this world.
     */
    private final OgreSceneManager sceneManager;

    /**
     * Contains all created Light, to check name is unique and to retrieve a Light from its name.
     */
    private final Registerer<AbstractLight> lights;

    /**
     * Full constructor.
     *
     * @param graphic Manage the graphic part of this world.
     */
    protected AbstractOgreWorld(final OgreSceneManager graphic) {
        super();
        this.sceneManager = graphic;
        this.lights = Registerer.newRegisterer();
    }

    @Override
    public final ClientGameEntity createStaticDoodad(final Box box, final Material material, final Point3D position, final Point3D direction) {
        final OgreNode node = this.sceneManager.createNode();
        final OgreEntity entity = this.sceneManager.createEntity(box, node);
        entity.setMaterial(material);
        node.setPosition(position);
        node.setDirection(direction);
        return new OgreStaticObject(EntityId.WORLD, entity);
    }

    @Override
    public ClientGameEntity createStaticObject(final EntityId id, final GraphicMesh mesh, final Point3D position, final Point3D direction) {
        final OgreNode node = this.sceneManager.createNode(id);
        final OgreEntity entity = this.sceneManager.createEntity(mesh, node);
        entity.setMaterial(mesh.getMaterial());
        node.setPosition(position);
        node.setDirection(direction);
        return new OgreStaticObject(id, entity);
    }

    @Override
    public final ClientGameEntity createStaticDoodad(final Plane plane, final Material material, final Point3D position, final Point3D direction) {
        final OgreNode node = this.sceneManager.createNode();
        final OgreEntity entity = this.sceneManager.createEntity(plane, node);
        entity.setMaterial(material);
        node.setPosition(position);
        node.setDirection(direction);
        return new OgreStaticObject(EntityId.WORLD, entity);
    }

    @Override
    public final ClientGameEntity createStaticDoodad(final Sphere sphere, final Material material, final Point3D position, final Point3D direction) {
        final OgreNode node = this.sceneManager.createNode();
        final OgreEntity entity = this.sceneManager.createEntity(sphere, node);
        entity.setMaterial(material);
        node.setPosition(position);
        node.setDirection(direction);
        return new OgreStaticObject(EntityId.WORLD, entity);
    }

    @Override
    public final ClientGameEntity createStaticDoodad(final Sphere sphere, final Material material, final Point3D position) {
        return this.createStaticDoodad(sphere, material, position, Point3D.BASE_DIRECTION);
    }

    @Override
    public final ClientGameEntity createStaticDoodad(final GraphicMesh mesh, final Point3D position, final Point3D direction) {
        final OgreNode node = this.sceneManager.createNode();
        final OgreEntity entity = this.sceneManager.createEntity(mesh, node);
        entity.setMaterial(mesh.getMaterial());
        node.setPosition(position);
        node.setDirection(direction);
        return new OgreStaticObject(EntityId.WORLD, entity);
    }

    @Override
    public final ClientGameEntity createMovableDoodad(final Box box, final Material material) {
        final OgreNode node = this.sceneManager.createNode();
        final OgreEntity entity = this.sceneManager.createEntity(box, node);
        entity.setMaterial(material);
        return new OgreMovableObject(EntityId.WORLD, entity);
    }

    @Override
    public final ClientGameEntity createMovableDoodad(final Plane plane, final Material material) {
        final OgreNode node = this.sceneManager.createNode();
        final OgreEntity entity = this.sceneManager.createEntity(plane, node);
        entity.setMaterial(material);
        return new OgreMovableObject(EntityId.WORLD, entity);
    }

    @Override
    public final ClientGameEntity createMovableDoodad(final Sphere sphere, final Material material) {
        final OgreNode node = this.sceneManager.createNode();
        final OgreEntity entity = this.sceneManager.createEntity(sphere, node);
        entity.setMaterial(material);
        return new OgreMovableObject(EntityId.WORLD, entity);
    }

    @Override
    public final ClientGameEntity createMovableDoodad(final GraphicMesh mesh) {
        final OgreNode node = this.sceneManager.createNode();
        final OgreEntity entity = this.sceneManager.createEntity(mesh, node);
        entity.setMaterial(mesh.getMaterial());
        return new OgreMovableObject(EntityId.WORLD, entity);
    }

    @Override
    public final ClientGameEntity createMovableObject(final EntityId id, final GraphicMesh mesh, final Point3D position) {
        final OgreNode node = this.sceneManager.createNode(id);
        final OgreEntity entity = this.sceneManager.createEntity(mesh, node);
        entity.setMaterial(mesh.getMaterial());
        node.setPosition(position);
        return new OgreMovableObject(id, entity);
    }

    @Override
    public final ClientGameEntity createStaticObject(final EntityId id, final GraphicMesh mesh, final Point3D position) {
        final OgreNode node = this.sceneManager.createNode(id);
        final OgreEntity entity = this.sceneManager.createEntity(mesh, node);
        entity.setMaterial(mesh.getMaterial());
        node.setPosition(position);
        return new OgreStaticObject(id, entity);
    }

    @Override
    public final LensFlare createLensFlare(final LensFlareMaterial mat, Point3D pos) {
        return this.sceneManager.createLensFlare(mat.getMaterial(), mat.getStreak(), mat.getHalo(), mat.getBurst(), pos);
    }

    @Override
    public final AbstractCamera createCamera(final String name) {
        return this.sceneManager.createCamera(name);
    }

    @Override
    public final void setAmbientLight(final Color color) {
        this.sceneManager.setAmbientLight(color);
    }

    @Override
    public final PointLight createPointLight(final String name, final Point3D position) {
        //FIXME LOW make register return object and use chaining return register(this.sm.createPointLight);
        PointLight light = this.sceneManager.createPointLight(name, position);
        this.lights.register(light);
        return light;
    }

    @Override
    public final SpotLight createSpotLight(final String name, final Point3D position, final Point3D direction) {
        SpotLight light = this.sceneManager.createSpotLight(name, position, direction);
        this.lights.register(light);
        return light;
    }

    @Override
    public final DirectionalLight createDirectionalLight(final String name, final Point3D position, final Point3D direction) {
        return this.sceneManager.createDirectionalLight(name, position, direction);
    }

    @Override
    public final void setSkybox(final Skybox sky) {
        Logger.info("Set skybox.");
        this.sceneManager.setSkybox(sky);
    }

    @Override
    public final ElectricArc createElectricArc(final Point3D start, final Point3D end, final float width) {
        return this.sceneManager.createElectricArc(start, end, width);
    }

    @Override
    public final AbstractParticleSystem createParticleSystem() {
        return this.sceneManager.createParticleSystem();
    }

    @Override
    public final Explosion createExplosion() {
        AbstractParticleSystem[] s = this.sceneManager.createExplosion();
        return new Explosion(s[0], s[1], s[2], s[3]);
    }

    @Override
    public final Ocean createOcean() {
        return this.sceneManager.createOcean();
    }

    @Override
    public final Sky createSky() {
        return this.sceneManager.createSky();
    }

    @Override
    public final AbstractCamera getDefaultCamera() {
        return this.sceneManager.getDefaultCamera();
    }

    @Override
    public final Line create3DLine() {
        return this.sceneManager.createLine();
    }

    @Override
    public final AbstractLight getLight(final String name) {
        return this.lights.get(name);
    }

    @Override
    public final MovableText createMovableText(final String name, final String text, final Font font) {
        return this.sceneManager.createMovableText(name, text, font);
    }

    @Override
    public final void deleteLight(final AbstractLight light) {
        for (LensFlare ls : light.getLensFlareList()) {
            this.sceneManager.getDefaultCamera().removeListener(ls);
        }
        this.lights.remove(light);
        light.delete();
    }

    @Override
    public final BillboardSet createBillboardSet(final Material mat) {
        return this.sceneManager.createBillboardSet(mat);
    }

    @Override
    public final AbstractCamera getCamera(final String name) {
        return this.sceneManager.getCamera(name);
    }

    @Override
    public final void deleteLight(final String name) {
        this.deleteLight(this.getLight(name));
    }
}
