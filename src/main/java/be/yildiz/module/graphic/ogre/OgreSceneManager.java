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
import be.yildiz.common.nativeresources.Native;
import be.yildiz.common.nativeresources.NativePointer;
import be.yildiz.common.shape.Box;
import be.yildiz.common.shape.Plane;
import be.yildiz.common.shape.Sphere;
import be.yildiz.common.util.Registerer;
import be.yildiz.common.util.StringUtil;
import be.yildiz.common.vector.Point3D;
import be.yildiz.module.graphic.*;
import be.yildiz.module.graphic.GraphicEngine.ShadowType;

/**
 * Java part of the yz::SceneManager.
 *
 * @author Grégory Van den Borre
 */
public final class OgreSceneManager implements SceneManager, Native {

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
    private final OgreNode rootNode;

    /**
     * Full constructor.
     *
     * @param pointer      SceneManager native pointer.
     * @param renderWindow Engine render window.
     * @param screenSizeX  Screen width.
     * @param screenSizeY  Screen height.
     */
    OgreSceneManager(final NativePointer pointer, final OgreRenderWindow renderWindow, final int screenSizeX, final int screenSizeY) {
        super();
        this.cameras = Registerer.newRegisterer();
        this.pointer = pointer;
        this.window = renderWindow;
        this.resolutionX = screenSizeX;
        this.resolutionY = screenSizeY;
        this.defaultCamera = this.createCamera("default");
        this.rootNode = new OgreNodeStatic(NativePointer.create(this.getRootNode(this.pointer.getPointerAddress())), null, Point3D.ZERO, Point3D.ZERO);
    }

    /**
     * Set this world ambient light, default is black. Without setting it, nothing will be visible if no light is created.
     *
     * @param color World ambient light color.
     */
    public void setAmbientLight(final Color color) {
        this.setAmbientLight(this.pointer.getPointerAddress(), color.normalizedRed, color.normalizedGreen, color.normalizedBlue, color.normalizedAlpha);
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
        final long lightPointer = this.createPointLight(this.pointer.getPointerAddress(), name, position.x, position.y, position.z);
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
        final long lightPointer = this.createSpotLight(this.pointer.getPointerAddress(), name, position.x, position.y, position.z, direction.x, direction.y, direction.z);
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
        final long lightPointer = this.createDirectionalLight(this.pointer.getPointerAddress(), name, position.x, position.y, position.z, direction.x, direction.y, direction.z);
        return new OgreDirectionalLight(NativePointer.create(lightPointer), name, direction);
    }

    /**
     * @return The Camera created at same time as this manager.
     */
    public AbstractCamera getDefaultCamera() {
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
        final long arcPointer = this.createElectricArc(this.pointer.getPointerAddress(), StringUtil.buildRandomString("earc"), start.x, start.y, start.z, end.x, end.y, end.z, width);
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
        this.setSkybox(this.pointer.getPointerAddress(), sky.getName());
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
        final long address = this.createNode(this.pointer.getPointerAddress(), StringUtil.buildRandomString("node"));
        final NativePointer nodePointer = NativePointer.create(address);
        return new OgreNodeStatic(nodePointer, this.rootNode, position, direction);
    }

    public final OgreNodeStatic createStaticNode(EntityId id, Point3D position, Point3D direction) {
        final long address = this.createNodeId(this.pointer.getPointerAddress(), id.value, StringUtil.buildRandomString("node"));
        final NativePointer nodePointer = NativePointer.create(address);
        return new OgreNodeStatic(nodePointer, this.rootNode, position, direction);
    }

    public final OgreNodeMovable createMovableNode() {
        final long address = this.createNode(this.pointer.getPointerAddress(), StringUtil.buildRandomString("node"));
        final NativePointer nodePointer = NativePointer.create(address);
        return new OgreNodeMovable(nodePointer, this.rootNode);
    }

    public final OgreNodeMovable createMovableNode(EntityId id) {
        final long address = this.createNodeId(this.pointer.getPointerAddress(), id.value, StringUtil.buildRandomString("node"));
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
        return new OgreLensFlare(NativePointer.create(this.createLensFlare(StringUtil.buildRandomString("lf_"), this.pointer.getPointerAddress(), this.defaultCamera.getPointer().getPointerAddress(),
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
        final long address = this.createCamera(this.pointer.getPointerAddress(), name);
        final OgreCamera cam = new OgreCamera(NativePointer.create(address), name, this.createMovableNode(), this.resolutionX, this.resolutionY);

        this.window.createViewport(cam);
        this.cameras.register(cam);
        return cam;
    }

    /**
     * Create a mesh entity.
     *
     * @param mesh Contains mesh name.
     * @param node The created entity will be attached to this node.
     * @return The built mesh entity.
     */
    public OgreEntity createEntity(final GraphicMesh mesh, final OgreNodeBase node) {
        OgreEntity entity = new OgreEntity(NativePointer.create(this.createMeshEntity(this.pointer.getPointerAddress(), mesh.getFile(), node.getPointer().getPointerAddress())), node);
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
        final OgreEntity e = new OgreEntity(NativePointer.create(this.createBoxEntity(this.pointer.getPointerAddress(), node.getPointer().getPointerAddress())), node);
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
        final OgreEntity e = new OgreEntity(NativePointer.create(this.createPlaneEntity(this.pointer.getPointerAddress(), node.getPointer().getPointerAddress())), node);
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
        final OgreEntity e = new OgreEntity(NativePointer.create(this.createSphereEntity(this.pointer.getPointerAddress(), node.getPointer().getPointerAddress(), StringUtil.buildRandomString(node.getName()))), node);
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
        final OgreNode node = this.createMovableNode();
        final long address = this.createParticleSystem(this.pointer.getPointerAddress());
        final NativePointer systemPointer = NativePointer.create(address);
        return new OgreParticleSystem(systemPointer, node);
    }

    /**
     * Set the world shadow type.
     *
     * @param type Shadow type to set.
     */
    public void setShadowType(final ShadowType type) {
        this.setShadowType(this.pointer.getPointerAddress(), type.ordinal());
    }

    /**
     * Create a billboard set and attach it to the root scene node.
     *
     * @param material Material to set on the set.
     * @return A new OgreBillboardSet attached to the root scene node.
     */
    public OgreBillboardSet createBillboardSet(final Material material) {
        NativePointer setPointer = NativePointer.create(this.createBillboardSet(this.pointer.getPointerAddress(), OgreMaterial.class.cast(material).getPointer().getPointerAddress()));
        return new OgreBillboardSet(setPointer, this.rootNode);
    }

    /**
     * Create an explosion object.
     *
     * @return The created object.
     */
    public OgreParticleSystem[] createExplosion() {
        final OgreNode node = this.createMovableNode();
        long address = this.createParticleSystem(this.pointer.getPointerAddress());
        final OgreParticleSystem smoke1 = new OgreParticleSystem(NativePointer.create(address), node);
        address = this.createParticleSystem(this.pointer.getPointerAddress());
        final OgreParticleSystem smoke2 = new OgreParticleSystem(NativePointer.create(address), node);
        address = this.createParticleSystem(this.pointer.getPointerAddress());
        final OgreParticleSystem smoke3 = new OgreParticleSystem(NativePointer.create(address), node);
        address = this.createParticleSystem(this.pointer.getPointerAddress());
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
        this.delete(this.pointer.getPointerAddress());
        this.pointer.delete();
    }

    @Override
    public NativePointer getPointer() {
        return pointer;
    }

    /**
     * Delete the object in native code.
     *
     * @param address Address of the native object.
     */
    private native void delete(final long address);

    /**
     * Create an Ogre::Entity from a mesh.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param meshName       Name of the mesh to use to build the entity.
     * @param nodePointer    The entity will be attached to this node.
     * @return The created entity pointer address.
     */
    private native long createMeshEntity(final long pointerAddress, final String meshName, final long nodePointer);

    /**
     * Create an Ogre::Entity from a box shape.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param nodePointer    The entity will be attached to this node.
     * @return The created entity pointer address.
     */
    private native long createBoxEntity(final long pointerAddress, final long nodePointer);

    /**
     * Create an Ogre::Entity from a plane shape.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param nodePointer    The entity will be attached to this node.
     * @return The created entity pointer address.
     */
    private native long createPlaneEntity(final long pointerAddress, final long nodePointer);

    /**
     * Create an Ogre::Entity from a sphere shape.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param nodePointer    The entity will be attached to this node.
     * @return The created entity pointer address.
     */
    private native long createSphereEntity(final long pointerAddress, final long nodePointer, final String name);

    /**
     * Set the scene ambient light in native code.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param red            Light red value.
     * @param green          Light green value.
     * @param blue           Light blue value.
     * @param alpha          Light intensity.
     */
    private native void setAmbientLight(final long pointerAddress, final float red, final float green, final float blue, final float alpha);

    /**
     * Create a particle system in native code.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @return The particle system pointer address.
     */
    private native long createParticleSystem(final long pointerAddress);

    /**
     * Set the sky box in native code.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param skybox         Sky box material to use.
     */
    private native void setSkybox(final long pointerAddress, final String skybox);

    /**
     * Build an yz::Node in native code.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param name           Node unique name.
     * @return The created yz::Node pointer address.
     */
    private native long createNode(final long pointerAddress, final String name);

    /**
     * Build an yz::Node in native code, it is associated with an id to be retrieved when using picking.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param associatedId   Id to associate to the node, used to identify the node when interactions occurs(raycast...).
     * @param name           Node unique name.
     * @return The created yz::Node pointer address.
     */
    private native long createNodeId(final long pointerAddress, final long associatedId, final String name);

    /**
     * Create a lens flare object in native code.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param camPointer     currently used camera.
     * @param light          Material used for the light.
     * @param streak         Material used for the streak.
     * @param haloMaterial   Material used for the halo.
     * @param burstMaterial  Material used for the burst.
     * @param posX           Lens flare position X value.
     * @param posY           Lens flare position Y value.
     * @param posZ           Lens flare position Z value.
     * @return The pointer address to the newly built lens flare.
     */
    // FIXME does not support camera switch.
    private native long createLensFlare(final String name, final long pointerAddress, final long camPointer, final long light, final long streak, final long haloMaterial, final long burstMaterial,
                                        final float posX, final float posY, final float posZ);

    /**
     * Create a camera in native code.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param name           Camera name.
     * @return The pointer address to the camera native object.
     */
    private native long createCamera(final long pointerAddress, final String name);

    /**
     * Create an electric arc in native code.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param name           Arc unique name.
     * @param x              Arc origin position X value.
     * @param y              Arc origin position Y value.
     * @param z              Arc origin position Z value.
     * @param x2             Arc end position X value.
     * @param y2             Arc end position Y value.
     * @param z2             Arc end position Z value.
     * @param width          elements width.
     * @return The pointer address to the newly built arc.
     */
    private native long createElectricArc(final long pointerAddress, final String name, final float x, final float y, final float z, final float x2, final float y2, final float z2, final float width);

    /**
     * Create a new point light in native code.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param name           Light name, must be unique.
     * @param posX           Light position X value.
     * @param posY           Light position Y value.
     * @param posZ           Light position Z value.
     * @return The pointer address to the light native object.
     */
    private native long createPointLight(final long pointerAddress, final String name, final float posX, final float posY, final float posZ);

    /**
     * Set the shadow technique in Ogre native code.
     *
     * @param pointer        Address to the native yz::SceneManager*.
     * @param techniqueIndex Index of the technique to use.
     */
    private native void setShadowTechnique(final long pointer, final int techniqueIndex);

    /**
     * Create a new spot light in native code.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param name           Light name, must be unique.
     * @param posX           Light position X value.
     * @param posY           Light position Y value.
     * @param posZ           Light position Z value.
     * @param dirX           Spot direction X value.
     * @param dirY           Spot direction Y value.
     * @param dirZ           Spot direction Z value.
     * @return The pointer address to the light native object.
     */
    private native long createSpotLight(final long pointerAddress, final String name, final float posX, final float posY, final float posZ, final float dirX, final float dirY, final float dirZ);

    /**
     * Create a new directional light in native code.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param name           Light name, must be unique.
     * @param posX           Light position X value.
     * @param posY           Light position Y value.
     * @param posZ           Light position Z value.
     * @param dirX           Spot direction X value.
     * @param dirY           Spot direction Y value.
     * @param dirZ           Spot direction Z value.
     * @return The pointer address to the light native object.
     */
    private native long createDirectionalLight(final long pointerAddress, final String name, final float posX, final float posY, final float posZ, final float dirX, final float dirY, final float dirZ);

    /**
     * Set the shadow type in native code.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param type           Type value.
     */
    private native void setShadowType(final long pointerAddress, final int type);

    /**
     * Create a new billboard set in native code.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param material       Set material.
     * @return The created set pointer address.
     */
    private native long createBillboardSet(final long pointerAddress, final long material);

    /**
     * Retrieve the root scene node in native code.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @return The pointer of the native yz::Node root object.
     */
    private native long getRootNode(final long pointerAddress);

    /**
     * Set the size for texture used for shadows.
     *
     * @param pointer Address to the native yz::SceneManager*.
     * @param size    Texture size.
     */
    private native void setShadowTextureSize(final long pointer, final int size);

    /**
     * Set the distance to display shadows.
     *
     * @param pointer  Address to the native yz::SceneManager*.
     * @param distance Maximum distance to display shadows..
     */
    private native void setShadowFarDistance(final long pointer, final int distance);
}
