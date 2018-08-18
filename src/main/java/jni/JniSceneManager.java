/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *  
 *  Copyright (c) 2018 Grégory Van den Borre
 *  
 *  More infos available: https://www.yildiz-games.be
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

package jni;

/**
 * @author Grégory Van den Borre
 */
public class JniSceneManager {

    /**
     * Delete the object in native code.
     *
     * @param address Address of the native object.
     */
    public native void delete(final long address);

    /**
     * Create an Ogre::Entity from a mesh.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param meshName       Name of the mesh to use to build the entity.
     * @param nodePointer    The entity will be attached to this node.
     * @return The created entity pointer address.
     */
    public native long createMeshEntity(final long pointerAddress, final String meshName, final long nodePointer);

    /**
     * Create an Ogre::Entity from a box shape.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param nodePointer    The entity will be attached to this node.
     * @return The created entity pointer address.
     */
    public native long createBoxEntity(final long pointerAddress, final long nodePointer);

    /**
     * Create an Ogre::Entity from a plane shape.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param nodePointer    The entity will be attached to this node.
     * @return The created entity pointer address.
     */
    public native long createPlaneEntity(final long pointerAddress, final long nodePointer);

    /**
     * Create an Ogre::Entity from a sphere shape.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param nodePointer    The entity will be attached to this node.
     * @param name Entity name.
     * @return The created entity pointer address.
     */
    public native long createSphereEntity(final long pointerAddress, final long nodePointer, final String name);

    /**
     * Set the scene ambient light in native code.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param red            Light red value.
     * @param green          Light green value.
     * @param blue           Light blue value.
     * @param alpha          Light intensity.
     */
    public native void setAmbientLight(final long pointerAddress, final float red, final float green, final float blue, final float alpha);

    /**
     * Create a particle system in native code.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @return The particle system pointer address.
     */
    public native long createParticleSystem(final long pointerAddress);

    /**
     * Set the sky box in native code.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param skybox         Sky box material to use.
     */
    public native void setSkybox(final long pointerAddress, final String skybox);

    /**
     * Build an yz::Node in native code.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param name           Node unique name.
     * @return The created yz::Node pointer address.
     */
    public native long createNode(final long pointerAddress, final String name);

    /**
     * Build an yz::Node in native code, it is associated with an id to be retrieved when using picking.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param associatedId   Id to associate to the node, used to identify the node when interactions occurs(raycast...).
     * @param name           Node unique name.
     * @return The created yz::Node pointer address.
     */
    public native long createNodeId(final long pointerAddress, final long associatedId, final String name);

    /**
     * Create a lens flare object in native code.
     *
     * @param name Object name.
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
    public native long createLensFlare(final String name, final long pointerAddress, final long camPointer, final long light, final long streak, final long haloMaterial, final long burstMaterial,
                                        final float posX, final float posY, final float posZ);

    /**
     * Create a camera in native code.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param name           Camera name.
     * @return The pointer address to the camera native object.
     */
    public native long createCamera(final long pointerAddress, final String name);

    public native long createQuery(final long pointerAddress, final long providerPointerAddress);

    public native long createDummyGroundQuery(final long pointerAddress, final long providerPointerAddress);

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
    public native long createElectricArc(final long pointerAddress, final String name, final float x, final float y, final float z, final float x2, final float y2, final float z2, final float width);

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
    public native long createPointLight(final long pointerAddress, final String name, final float posX, final float posY, final float posZ);

    /**
     * Set the shadow technique in Ogre native code.
     *
     * @param pointer        Address to the native yz::SceneManager*.
     * @param techniqueIndex Index of the technique to use.
     */
    public native void setShadowTechnique(final long pointer, final int techniqueIndex);

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
    public native long createSpotLight(final long pointerAddress, final String name, final float posX, final float posY, final float posZ, final float dirX, final float dirY, final float dirZ);

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
    public native long createDirectionalLight(final long pointerAddress, final String name, final float posX, final float posY, final float posZ, final float dirX, final float dirY, final float dirZ);

    /**
     * Set the shadow type in native code.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param type           Type value.
     */
    public native void setShadowType(final long pointerAddress, final int type);

    /**
     * Create a new billboard set in native code.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @param material       Set material.
     * @return The created set pointer address.
     */
    public native long createBillboardSet(final long pointerAddress, final long material);

    /**
     * Retrieve the root scene node in native code.
     *
     * @param pointerAddress Address to the native yz::SceneManager*.
     * @return The pointer of the native yz::Node root object.
     */
    public native long getRootNode(final long pointerAddress);

    /**
     * Set the size for texture used for shadows.
     *
     * @param pointer Address to the native yz::SceneManager*.
     * @param size    Texture size.
     */
    public native void setShadowTextureSize(final long pointer, final int size);

    /**
     * Set the distance to display shadows.
     *
     * @param pointer  Address to the native yz::SceneManager*.
     * @param distance Maximum distance to display shadows..
     */
    public native void setShadowFarDistance(final long pointer, final int distance);
}
