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

import be.yildizgames.common.geometry.Point3D;
import be.yildizgames.common.util.Registerer;
import be.yildizgames.module.color.Color;
import be.yildizgames.module.graphic.Font;
import be.yildizgames.module.graphic.GraphicObjectBuilder;
import be.yildizgames.module.graphic.GraphicWorld;
import be.yildizgames.module.graphic.RayProvider;
import be.yildizgames.module.graphic.billboard.BillboardSet;
import be.yildizgames.module.graphic.camera.Camera;
import be.yildizgames.module.graphic.light.DirectionalLight;
import be.yildizgames.module.graphic.light.LensFlare;
import be.yildizgames.module.graphic.light.Light;
import be.yildizgames.module.graphic.light.PointLight;
import be.yildizgames.module.graphic.light.SpotLight;
import be.yildizgames.module.graphic.material.Material;
import be.yildizgames.module.graphic.misc.ElectricArc;
import be.yildizgames.module.graphic.misc.Explosion;
import be.yildizgames.module.graphic.misc.Line;
import be.yildizgames.module.graphic.misc.MovableText;
import be.yildizgames.module.graphic.misc.Ocean;
import be.yildizgames.module.graphic.misc.Sky;
import be.yildizgames.module.graphic.misc.SkyBox;
import be.yildizgames.module.graphic.ogre.impl.OgreSceneManager;
import be.yildizgames.module.graphic.particle.ParticleSystem;
import be.yildizgames.module.graphic.query.GroundQuery;
import be.yildizgames.module.graphic.query.Query;

import java.security.InvalidParameterException;

/**
 * Ogre implementation for a graphic world.
 *
 * @author Grégory Van den Borre
 */
final class OgreWorld implements GraphicWorld {

    private static final System.Logger LOGGER = System.getLogger(OgreWorld.class.getName());

    /**
     * The scene manager manage the graphic part of this world.
     */
    private final OgreSceneManager sceneManager;

    /**
     * Contains all created Light, to check name is unique and to retrieve a Light from its name.
     */
    private final Registerer<Light> lights = Registerer.newRegisterer();

    private boolean debug;

    /**
     * Full constructor.
     *
     * @param graphic Manage the graphic part of this world.
     */
    OgreWorld(final OgreSceneManager graphic) {
        super();
        this.sceneManager = graphic;
    }


    @Override
    public String getName() {
        return this.sceneManager.getName();
    }

    @Override
    public GraphicObjectBuilder createObject() {
        return new OgreGraphicObjectBuilder(this.sceneManager);
    }

    @Override
    public final LensFlare createLensFlare(final LensFlare.LensFlareMaterial mat, Point3D pos) {
        return this.sceneManager.createLensFlare(mat.getMaterial(), mat.getStreak(), mat.getHalo(), mat.getBurst(), pos);
    }

    @Override
    public final Camera createCamera(final String name) {
        return this.sceneManager.createCamera(name);
    }

    @Override
    public final Query createQuery(final RayProvider provider) {
        return this.sceneManager.createQuery(provider);
    }

    @Override
    public final GroundQuery createGroundQuery(final RayProvider provider) {
        return this.sceneManager.createGroundQuery(provider);
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
    public final void setSkybox(final SkyBox sky) {
        LOGGER.log(System.Logger.Level.DEBUG, "Set skybox.");
        this.sceneManager.setSkybox(sky);
    }

    @Override
    public final ElectricArc createElectricArc(final Point3D start, final Point3D end, final float width) {
        return this.sceneManager.createElectricArc(start, end, width);
    }

    @Override
    public final ParticleSystem createParticleSystem() {
        return this.sceneManager.createParticleSystem();
    }

    @Override
    public final Explosion createExplosion() {
        ParticleSystem[] s = this.sceneManager.createExplosion();
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
    public final Camera getDefaultCamera() {
        return this.sceneManager.getDefaultCamera();
    }

    @Override
    public final Line create3DLine() {
        return this.sceneManager.createLine();
    }

    @Override
    public final Light getLight(final String name) {
        return this.lights.get(name);
    }

    @Override
    public final MovableText createMovableText(final String name, final String text, final Font font) {
        return this.sceneManager.createMovableText(name, text, font);
    }

    @Override
    public final void deleteLight(final Light light) {
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
    public final Camera getCamera(final String name) {
        return this.sceneManager.getCamera(name);
    }

    @Override
    public final void deleteLight(final String name) {
        this.deleteLight(this.getLight(name));
    }


    @Override
    public void setDebugMode() {
        this.debug = true;
    }

    @Override
    public void serializeShapeFromMesh(final String mesh, final String file, final String name) {
        throw new InvalidParameterException();
    }

    @Override
    public boolean isDebug() {
        return debug;
    }

}
