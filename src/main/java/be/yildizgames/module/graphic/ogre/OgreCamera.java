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

package be.yildizgames.module.graphic.ogre;

import be.yildizgames.common.gameobject.Movable;
import be.yildizgames.common.geometry.Point3D;
import be.yildizgames.common.geometry.Rectangle;
import be.yildizgames.common.jni.Native;
import be.yildizgames.common.jni.NativePointer;
import be.yildizgames.common.model.EntityId;
import be.yildizgames.module.graphic.camera.Camera;
import be.yildizgames.module.graphic.light.LensFlare;
import be.yildizgames.module.graphic.ogre.light.OgreLensFlare;
import jni.JniCamera;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

/**
 * Ogre implementation for the Camera.
 *
 * @author Grégory Van den Borre
 */
public final class OgreCamera extends Camera implements Native {

    /**
     * Rotation camera speed.
     */
    private static final float ROTATION_SPEED = 0.05f;
    /**
     * Screen size Y value.
     */
    private final float resolutionY;
    /**
     * Screen size X value.
     */
    private final float resolutionX;
    /**
     * Pointer address to the native code object.
     */
    private final NativePointer pointer;

    /**
     * Node to auto track a specific position.
     */
    private final OgreNodeBase node;

    private final OgreNodeBase targetNode;

    private final JniCamera jni = new JniCamera();

    /**
     * Full constructor.
     *
     * @param pointer Pointer address to the associated native object.
     * @param name    Camera name.
     * @param node    The node will be used to auto track a specific position.
     * @param resX    Resolution width.
     * @param resY    Resolution height.
     */
    public OgreCamera(
            final NativePointer pointer,
            final String name,
            final OgreNodeBase master,
            final OgreNodeBase node,
            final OgreNodeBase targetNode,
            final float resX,
            final float resY) {
        super(name);
        this.pointer = pointer;
        this.node = node;
        this.targetNode = targetNode;
        this.resolutionX = resX;
        this.resolutionY = resY;
    }

    public void adaptToScreenRatio() {
        this.jni.setAspectRatio(this.pointer.getPointerAddress(), this.getScreenRatio());
    }

    public float getScreenRatio() {
        return this.resolutionX / this.resolutionY;
    }

    @Override
    public OgreCamera setFarClip(int far) {
        this.jni.enableRenderingDistance(this.pointer.getPointerAddress());
        this.jni.setFarClip(this.pointer.getPointerAddress(), far);
        return this;
    }

    @Override
    public OgreCamera setNearClip(int near) {
        this.jni.enableRenderingDistance(this.pointer.getPointerAddress());
        this.jni.setNearClip(this.pointer.getPointerAddress(), near);
        return this;
    }

    @Override
    public void setTargetPosition(Point3D target) {
        this.targetNode.setPosition(target);
    }

    @Override
    public void rotateTarget(float yaw, float pitch) {
        this.targetNode.rotate(yaw, pitch);
    }

    @Override
    public void rotate(float yaw, float pitch) {
        this.jni.rotate(this.pointer.getPointerAddress(), yaw, pitch);
    }

    /**
     * Create a plane on the screen and return all objects contained in it.
     *
     * @param rectangle Plane to use.
     * @return The list of id of the found objects.
     */
    public List<EntityId> throwPlaneRay(final Rectangle rectangle) {
        // FIXME set the resolution in camera and compute this there
        final float left = rectangle.getLeft() / this.resolutionX;
        final float top = rectangle.getTop() / this.resolutionY;
        final float right = rectangle.getRight() / this.resolutionX;
        final float bottom = rectangle.getBottom() / this.resolutionY;
        final long[] tab = this.jni.throwPlaneRay(this.pointer.getPointerAddress(), left, top, right, bottom);
        final List<EntityId> ids = new ArrayList<>(tab.length);
        for (long i : tab) {
            ids.add(EntityId.valueOf(i));
        }
        return ids;
    }

    /**
     * Throw a ray from the camera to a position from mouse coordinates.
     *
     * @param x Mouse X coordinates to compute the ray.
     * @param y Mouse Y coordinates to compute the ray.
     * @return The Id of the closest object hit by the ray, if none, Id.WORLD will be returned.
     */
    @Override
    public Optional<EntityId> throwRay(final int x, final int y) {
        final float screenX = x / this.resolutionX;
        final float screenY = y / this.resolutionY;
        EntityId id = EntityId.valueOf(this.jni.throwRay(this.pointer.getPointerAddress(), screenX, screenY, false));
        if (id.equals(EntityId.WORLD)) {
            return Optional.empty();
        }
        return Optional.of(id);
    }

    /**
     * Compute the destination from 2D coordinates to 3D coordinates, collision ground is considered at Y = 0.
     *
     * @param x X screen coordinates.
     * @param y Y screen coordinates.
     * @return A point representing a destination.
     */
    public Point3D computeMoveDestination(final int x, int y) {
        final float screenX = (float) x / this.resolutionX;
        final float screenY = (float) y / this.resolutionY;
        final float[] destination = this.jni.computeMoveDestinationGroundIntersect(this.pointer.getPointerAddress(), screenX, screenY);
        return Point3D.valueOf(destination[0], destination[1], destination[2]);
    }

    @Override
    public void removeListener(final LensFlare ls) {
        OgreLensFlare listener = (OgreLensFlare) ls;
        this.jni.unregisterListener(this.pointer.getPointerAddress(), listener.getPointer().getPointerAddress());
    }

    @Override
    public void setAspectRatio(float ratio) {
        this.jni.setAspectRatio(this.pointer.getPointerAddress(), ratio);
    }

    @Override
    public Point3D getTargetPosition() {
        return null;
    }

    @Override
    public void initOrigin() {

    }

    @Override
    public void initTarget() {

    }

    /**
     * Check if an object is viewable by the camera.
     *
     * @param position Object position.
     * @return <code>true</code> if the camera can view this object, <code>false</code> otherwise.
     */
    boolean see(final Point3D position) {
        return this.jni.isVisible(this.pointer.getPointerAddress(), position.x, position.y, position.z);
    }

    protected Point3D getDirectionImpl() {
        float[] v = this.jni.getDirection(this.pointer.getPointerAddress());
        return Point3D.valueOf(v[0], v[1], v[2]);
    }

    /**
     * Force the listeners update in native code.
     */
    void forceListenersUpdate() {
        this.jni.forceListenersUpdate(this.pointer.getPointerAddress());
    }

    /**
     * Detach the camera from its parent node.
     */
    @Override
    public void detachFromParent() {
        this.jni.detachFromParent(this.pointer.getPointerAddress());
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

    @Override
    public final void attachTo(final Movable other) {
        this.node.attachTo(other);
    }

    @Override
    public final void attachToOptional(final Movable other) {
        this.node.attachToOptional(other);
    }

    @Override
    public final Point3D getPosition() {
        return this.node.getPosition();
    }

    @Override
    public final void setPosition(final Point3D position) {
        this.node.setPosition(position);
    }

    @Override
    public final Point3D getAbsolutePosition() {
        return this.node.getAbsolutePosition();
    }

    @Override
    public final Point3D getDirection() {
        return this.node.getDirection();
    }

    @Override
    public final Point3D getAbsoluteDirection() {
        return this.node.getAbsoluteDirection();
    }

    @Override
    public void setPosition(float v, float v1, float v2) {
        this.node.setPosition(v, v1, v2);
    }

    @Override
    public void setDirection(float v, float v1, float v2) {
        this.node.setDirection(v, v1, v2);
    }

    @Override
    public void addOptionalChild(Movable movable) {

    }

    @Override
    public void addChild(Movable movable) {

    }

    @Override
    public void removeChild(Movable movable) {

    }
}
