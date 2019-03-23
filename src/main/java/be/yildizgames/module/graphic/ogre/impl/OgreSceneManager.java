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

package be.yildizgames.module.graphic.ogre.impl;

import be.yildizgames.common.geometry.Point3D;
import be.yildizgames.common.jni.Native;
import be.yildizgames.common.jni.NativePointer;
import be.yildizgames.common.model.EntityId;
import be.yildizgames.common.shape.Box;
import be.yildizgames.common.shape.Plane;
import be.yildizgames.common.shape.Sphere;
import be.yildizgames.common.util.Registerer;
import be.yildizgames.common.util.StringUtil;
import be.yildizgames.module.color.Color;
import be.yildizgames.module.graphic.Font;
import be.yildizgames.module.graphic.GraphicMesh;
import be.yildizgames.module.graphic.RayProvider;
import be.yildizgames.module.graphic.SceneManager;
import be.yildizgames.module.graphic.ShadowType;
import be.yildizgames.module.graphic.camera.Camera;
import be.yildizgames.module.graphic.material.Material;
import be.yildizgames.module.graphic.misc.Skybox;
import be.yildizgames.module.graphic.ogre.OgreBillboardChain;
import be.yildizgames.module.graphic.ogre.OgreBillboardSet;
import be.yildizgames.module.graphic.ogre.OgreCamera;
import be.yildizgames.module.graphic.ogre.OgreEntity;
import be.yildizgames.module.graphic.ogre.OgreGroundQuery;
import be.yildizgames.module.graphic.ogre.OgreMaterial;
import be.yildizgames.module.graphic.ogre.OgreMovableText;
import be.yildizgames.module.graphic.ogre.OgreNode;
import be.yildizgames.module.graphic.ogre.OgreNodeBase;
import be.yildizgames.module.graphic.ogre.OgreNodeMovable;
import be.yildizgames.module.graphic.ogre.OgreNodeStatic;
import be.yildizgames.module.graphic.ogre.OgreQuery;
import be.yildizgames.module.graphic.ogre.light.OgreDirectionalLight;
import be.yildizgames.module.graphic.ogre.light.OgreLensFlare;
import be.yildizgames.module.graphic.ogre.light.OgrePointLight;
import be.yildizgames.module.graphic.ogre.light.OgreSpotLight;
import be.yildizgames.module.graphic.ogre.misc.OgreElectricArc;
import be.yildizgames.module.graphic.ogre.misc.OgreHydrax;
import be.yildizgames.module.graphic.ogre.misc.OgreLine;
import be.yildizgames.module.graphic.ogre.misc.OgreSkyX;
import be.yildizgames.module.graphic.ogre.particle.OgreParticleSystem;
import jni.JniSceneManager;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * Java part of the yz::SceneManager.
 *
 * @author Grégory Van den Borre
 */
public final class OgreSceneManager implements SceneManager, Native {

    private final Logger logger = LoggerFactory.getLogger(OgreSceneManager.class);

    /**
     * Value to scale the boxes to match Ogre and engine sizes.
     */
    private static final float OGRE_SCALE = 0.01f;

    /**
     * Screen size Y value.
     */
    private final float resolutionY;

    /**
     * Screen size X value.
     */
    private final float resolutionX;

    /**
     * Pointer address to the associated yz::SceneManager*.
     */
    private final NativePointer pointer;

    /**
     * Contains all created Camera, to check name is unique and to retrieve a Camera from its name.
     */
    private final Registerer<OgreCamera> cameras;

    /**
     * Default camera, build at same time as this scene manager.
     */
    private final OgreCamera defaultCamera;

    /**
     * Game render window.
     */
    private final OgreRenderWindow window;

    /**
     * Scene root node.
     */
    private final OgreNodeBase rootNode;

    private final JniSceneManager jni = new JniSceneManager();

    private final String name;

    /**
     * Full constructor.
     *
     * @param pointer      SceneManager native pointer.
     * @param renderWindow Engine render window.
     * @param screenSizeX  Screen width.
     * @param screenSizeY  Screen height.
     */
    public OgreSceneManager(String name, final NativePointer pointer, final OgreRenderWindow renderWindow, final int screenSizeX, final int screenSizeY) {
        super();
        this.name = name;
        this.cameras = Registerer.newRegisterer();
        this.pointer = pointer;
        this.window = renderWindow;
        this.resolutionX = screenSizeX;
        this.resolutionY = screenSizeY;
        this.logger.debug("Initializing root node...");
        this.rootNode = OgreNodeStatic.root(NativePointer.create(this.jni.getRootNode(this.pointer.getPointerAddress())));
        this.logger.debug("Root node initialized.");
        this.logger.debug("Creating default camera...");
        this.defaultCamera = this.createCamera("default");
        this.logger.debug("Default camera created.");
        this.createDummyGround();
    }

    /**
     * Set this world ambient light, default is black. Without setting it, nothing will be visible if no light is created.
     *
     * @param color World ambient light color.
     */
    public void setAmbientLight(final Color color) {
        this.jni.setAmbientLight(this.pointer.getPointerAddress(), color.normalizedRed, color.normalizedGreen, color.normalizedBlue, color.normalizedAlpha);
    }

    /**
     * Create a new billboard chain.
     *
     * @return The created billboard chain.
     */
    public OgreBillboardChain createBillboardChain() {
        OgreNode node = this.createMovableNode();
        return new OgreBillboardChain(node);
    }

    /**
     * Create a light of type PointLight.
     *
     * @param name     Light name, must be unique.
     * @param position Light position.
     * @return The created point light.
     */
    public OgrePointLight createPointLight(final String name, final Point3D position) {
        final long lightPointer = this.jni.createPointLight(this.pointer.getPointerAddress(), name, position.x, position.y, position.z);
        return new OgrePointLight(NativePointer.create(lightPointer), name, position);
    }

    /**
     * Create a light of type spotlight.
     *
     * @param name      Light name, must be unique.
     * @param position  Spot position.
     * @param direction Spot direction.
     * @return The created spot light.
     */
    public OgreSpotLight createSpotLight(final String name, final Point3D position, final Point3D direction) {
        final long lightPointer = this.jni.createSpotLight(this.pointer.getPointerAddress(), name, position.x, position.y, position.z, direction.x, direction.y, direction.z);
        return new OgreSpotLight(NativePointer.create(lightPointer), name, position, direction);
    }

    /**
     * Create a light of type directional light.
     *
     * @param name      Light name, must be unique.
     * @param position  Light position.
     * @param direction Light direction.
     * @return The created directional light.
     */
    public OgreDirectionalLight createDirectionalLight(final String name, final Point3D position, final Point3D direction) {
        final long lightPointer = this.jni.createDirectionalLight(this.pointer.getPointerAddress(), name, position.x, position.y, position.z, direction.x, direction.y, direction.z);
        return new OgreDirectionalLight(NativePointer.create(lightPointer), name, direction);
    }

    /**
     * @return The Camera created at same time as this manager.
     */
    public Camera getDefaultCamera() {
        return this.defaultCamera;
    }

    /**
     * Create an ElectricArc.
     *
     * @param start Arc start position.
     * @param end   Arc end position.
     * @param width Element width.
     * @return An Ogre implementation for ElectricArc.
     */
    public OgreElectricArc createElectricArc(final Point3D start, final Point3D end, final float width) {
        final long arcPointer = this.jni.createElectricArc(this.pointer.getPointerAddress(), StringUtil.buildRandomString("earc"), start.x, start.y, start.z, end.x, end.y, end.z, width);
        return new OgreElectricArc(NativePointer.create(arcPointer), start, end);
    }

    /**
     * Create an Ocean.
     *
     * @return An Ogre implementation for Ocean.
     */
    public OgreHydrax createOcean() {
        return new OgreHydrax(this.pointer, this.defaultCamera);
    }

    /**
     * Create a Sky.
     *
     * @return An Ogre implementation for a Sky.
     */
    public OgreSkyX createSky() {
        // FIXME create the object from the scene manager in native code.
        return new OgreSkyX(this, this.window);
    }

    /**
     * Set a sky box in the scene.
     *
     * @param sky Sky box to use.
     */
    public void setSkybox(final Skybox sky) {
        this.jni.setSkybox(this.pointer.getPointerAddress(), sky.getName());
    }

    /**
     * Create a simple 3d line.
     *
     * @return The created line.
     */
    public OgreLine createLine() {
        return new OgreLine(this.createMovableNode());
    }

    public final OgreNodeStatic createStaticNode(Point3D position, Point3D direction) {
        final long address = this.jni.createNode(this.pointer.getPointerAddress(), StringUtil.buildRandomString("node"));
        final NativePointer nodePointer = NativePointer.create(address);
        return new OgreNodeStatic(nodePointer, this.rootNode, position, direction);
    }

    public final OgreNodeStatic createStaticNode(EntityId id, Point3D position, Point3D direction) {
        final long address = this.jni.createNodeId(this.pointer.getPointerAddress(), id.value, StringUtil.buildRandomString("node"));
        final NativePointer nodePointer = NativePointer.create(address);
        return new OgreNodeStatic(nodePointer, this.rootNode, position, direction);
    }

    public final OgreNodeMovable createMovableNode() {
        final long address = this.jni.createNode(this.pointer.getPointerAddress(), StringUtil.buildRandomString("node"));
        final NativePointer nodePointer = NativePointer.create(address);
        return new OgreNodeMovable(nodePointer, this.rootNode);
    }

    public final OgreNodeMovable createMovableNode(EntityId id) {
        final long address = this.jni.createNodeId(this.pointer.getPointerAddress(), id.value, StringUtil.buildRandomString("node"));
        final NativePointer nodePointer = NativePointer.create(address);
        return new OgreNodeMovable(nodePointer, this.rootNode);
    }

    /**
     * Create a lens flare.
     *
     * @param light  Lens light material.
     * @param streak Lens streak material.
     * @param halo   Lens halo material.
     * @param burst  Lens burst Material.
     * @param pos    Lens initial position.
     * @return The created lens flare.
     */
    public OgreLensFlare createLensFlare(final Material light, final Material streak, final Material halo, final Material burst, final Point3D pos) {
        // FIXME linked to camera, does not support switching cam
        return new OgreLensFlare(NativePointer.create(this.jni.createLensFlare(StringUtil.buildRandomString("lf_"), this.pointer.getPointerAddress(), this.defaultCamera.getPointer().getPointerAddress(),
                OgreMaterial.class.cast(light).getPointer().getPointerAddress(), OgreMaterial.class.cast(streak).getPointer().getPointerAddress(), OgreMaterial.class.cast(halo).getPointer().getPointerAddress(), OgreMaterial.class.cast(burst).getPointer().getPointerAddress(),
                pos.x, pos.y, pos.z)), Point3D.valueOf(pos.x, pos.y, pos.z));
    }

    /**
     * Create a new camera with default behavior(free fly).
     *
     * @param name Camera name, must be unique.
     * @return The newly built camera.
     */
    public OgreCamera createCamera(final String name) {
        final long address = this.jni.createCamera(this.pointer.getPointerAddress(), name);
        final OgreCamera cam = new OgreCamera(NativePointer.create(address), name, this.createMovableNode(), this.createMovableNode(), this.createMovableNode(), this.resolutionX, this.resolutionY);

        this.window.createViewport(cam);
        this.cameras.register(cam);
        cam.adaptToScreenRatio();
        return cam;
    }

    public OgreQuery createQuery(RayProvider provider) {
       final long address = this.jni.createQuery(this.pointer.getPointerAddress(), Native.class.cast(provider).getPointer().getPointerAddress());
       return new OgreQuery(NativePointer.create(address), resolutionX, resolutionY);
    }

    public void createDummyGround() {
        final long address = this.jni.createDummyGround(this.pointer.getPointerAddress());
        OgreNode node = new OgreNodeMovable(NativePointer.create(address), this.rootNode);
        //FIXME only attached to default cam, cannot handle multiple cameras.
        node.attachTo(this.defaultCamera);
    }

    public OgreGroundQuery createGroundQuery(RayProvider provider) {
       final long address = this.jni.createGroundQuery(this.pointer.getPointerAddress(), Native.class.cast(provider).getPointer().getPointerAddress());
       return new OgreGroundQuery(NativePointer.create(address), resolutionX, resolutionY);
    }

    /**
     * Create a mesh entity.
     *
     * @param mesh Contains mesh name.
     * @param node The created entity will be attached to this node.
     * @return The built mesh entity.
     */
    public OgreEntity createEntity(final GraphicMesh mesh, final OgreNodeBase node) {
        OgreEntity entity = new OgreEntity(NativePointer.create(this.jni.createMeshEntity(this.pointer.getPointerAddress(), mesh.getFile(), node.getPointer().getPointerAddress())), node);
        entity.setMaterial(mesh.getMaterial());
        return entity;
    }

    /**
     * Create a box entity, by default Ogre build 100*100*100 box, to resize it to the correct dimensions, the node scale is divided by 100.
     *
     * @param box  Contains the box dimensions data.
     * @param node The created entity will be attached to this node.
     * @return The built box entity.
     */
    public OgreEntity createEntity(final Box box, final OgreNodeBase node) {
        final OgreEntity e = new OgreEntity(NativePointer.create(this.jni.createBoxEntity(this.pointer.getPointerAddress(), node.getPointer().getPointerAddress())), node);
        node.scale(box.width * OgreSceneManager.OGRE_SCALE, box.height * OgreSceneManager.OGRE_SCALE, box.depth * OgreSceneManager.OGRE_SCALE);
        return e;
    }

    /**
     * Create a plane entity, by default Ogre build 100*100 plane, to resize it to the correct dimensions, the node scale is divided by 100.
     *
     * @param plane Contains the plane dimensions data.
     * @param node  The created entity will be attached to this node.
     * @return The built plane entity.
     */
    public OgreEntity createEntity(final Plane plane, final OgreNodeBase node) {
        final OgreEntity e = new OgreEntity(NativePointer.create(this.jni.createPlaneEntity(this.pointer.getPointerAddress(), node.getPointer().getPointerAddress())), node);
        node.scale(plane.width * OgreSceneManager.OGRE_SCALE, plane.depth * OGRE_SCALE, plane.depth * OGRE_SCALE);
        return e;
    }

    /**
     * Create a sphere entity, by default Ogre build 100 radius sphere, to resize it to the correct dimensions, the node scale is divided by 100.
     *
     * @param sphere Contains the sphere dimension data.
     * @param node   The created entity will be attached to this node.
     * @return The built sphere entity.
     */
    public OgreEntity createEntity(final Sphere sphere, final OgreNodeBase node) {
        final OgreEntity e = new OgreEntity(NativePointer.create(this.jni.createSphereEntity(this.pointer.getPointerAddress(), node.getPointer().getPointerAddress(), StringUtil.buildRandomString(node.getName()))), node);
        node.scale(OgreSceneManager.OGRE_SCALE * sphere.radius);
        return e;
    }

    /**
     * Create a movable text object.
     *
     * @param name Object unique name.
     * @param text Text to display.
     * @param font Font to use.
     * @return The created movable text object.
     */
    public OgreMovableText createMovableText(final String name, final String text, final Font font) {
        return new OgreMovableText(this.createMovableNode(), name, text, font);
    }

    /**
     * Create a new ParticleSystem.
     *
     * @return An OgreParticleSystem.
     */
    public OgreParticleSystem createParticleSystem() {
        final OgreNodeBase node = this.createMovableNode();
        final long address = this.jni.createParticleSystem(this.pointer.getPointerAddress());
        final NativePointer systemPointer = NativePointer.create(address);
        return new OgreParticleSystem(systemPointer, node);
    }

    /**
     * Set the world shadow type.
     *
     * @param type Shadow type to set.
     */
    public void setShadowType(final ShadowType type) {
        this.jni.setShadowType(this.pointer.getPointerAddress(), type.ordinal());
    }

    /**
     * Create a billboard set and attach it to the root scene node.
     *
     * @param material Material to set on the set.
     * @return A new OgreBillboardSet attached to the root scene node.
     */
    public OgreBillboardSet createBillboardSet(final Material material) {
        NativePointer setPointer = NativePointer.create(this.jni.createBillboardSet(this.pointer.getPointerAddress(), OgreMaterial.class.cast(material).getPointer().getPointerAddress()));
        return new OgreBillboardSet(setPointer, this.rootNode);
    }

    /**
     * Create an explosion object.
     *
     * @return The created object.
     */
    public OgreParticleSystem[] createExplosion() {
        final OgreNodeBase node = this.createMovableNode();
        long address = this.jni.createParticleSystem(this.pointer.getPointerAddress());
        final OgreParticleSystem smoke1 = new OgreParticleSystem(NativePointer.create(address), node);
        address = this.jni.createParticleSystem(this.pointer.getPointerAddress());
        final OgreParticleSystem smoke2 = new OgreParticleSystem(NativePointer.create(address), node);
        address = this.jni.createParticleSystem(this.pointer.getPointerAddress());
        final OgreParticleSystem smoke3 = new OgreParticleSystem(NativePointer.create(address), node);
        address = this.jni.createParticleSystem(this.pointer.getPointerAddress());
        final OgreParticleSystem smoke4 = new OgreParticleSystem(NativePointer.create(address), node);
        return new OgreParticleSystem[]{smoke1, smoke2, smoke3, smoke4};
    }

    /**
     * Get a camera from its name.
     *
     * @param name Camera name.
     * @return The camera matching the name.
     */
    public OgreCamera getCamera(final String name) {
        return this.cameras.get(name);
    }

    @Override
    public void delete() {
        this.jni.delete(this.pointer.getPointerAddress());
        this.pointer.delete();
    }

    @Override
    public NativePointer getPointer() {
        return pointer;
    }

    public String getName() {
        return name;
    }
}
