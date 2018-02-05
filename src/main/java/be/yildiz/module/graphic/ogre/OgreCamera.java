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

package be.yildiz.module.graphic.ogre;

import be.yildiz.module.graphic.AbstractCamera;
import be.yildiz.module.graphic.LensFlare;
import be.yildiz.module.graphic.Node;
import be.yildizgames.common.collection.Lists;
import be.yildizgames.common.geometry.Axis;
import be.yildizgames.common.geometry.Point3D;
import be.yildizgames.common.geometry.Rectangle;
import be.yildizgames.common.model.EntityId;
import be.yildizgames.common.nativeresources.Native;
import be.yildizgames.common.nativeresources.NativePointer;

import java.util.List;
import java.util.Optional;

/**
 * Ogre implementation for the Camera.
 *
 * @author Grégory Van den Borre
 */
final class OgreCamera extends AbstractCamera implements Native {

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
    private final OgreNode node;

    /**
     * Full constructor.
     *
     * @param pointer Pointer address to the associated native object.
     * @param name    Camera name.
     * @param node    The node will be used to auto track a specific position.
     */
    OgreCamera(final NativePointer pointer, final String name, final OgreNode node, final float resX, final float resY) {
        super(name);
        this.pointer = pointer;
        this.node = node;
        this.resolutionX = resX;
        this.resolutionY = resY;
        this.enableRenderingDistance(pointer.getPointerAddress());
        //FIXME LOW hardcoded
        this.setFarClip(this.pointer.getPointerAddress(), 200000);
        this.setNearClip(this.pointer.getPointerAddress(), 10);
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
        final long[] tab = this.throwPlaneRay(this.pointer.getPointerAddress(), left, top, right, bottom);
        final List<EntityId> ids = Lists.newList(tab.length);
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
        EntityId id = EntityId.valueOf(this.throwRay(this.pointer.getPointerAddress(), screenX, screenY, false));
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
        final float[] destination = this.computeMoveDestinationGroundIntersect(this.pointer.getPointerAddress(), screenX, screenY);
        return Point3D.valueOf(destination[0], destination[1], destination[2]);
    }

    @Override
    public void removeListener(final LensFlare ls) {
        OgreLensFlare listener = (OgreLensFlare) ls;
        this.unregisterListener(this.pointer.getPointerAddress(), listener.getPointer().getPointerAddress());
    }

    @Override
    public void stopAutoTrackImpl() {
        this.stopAutotrack(this.pointer.getPointerAddress());
    }

    @Override
    public void autoTrackImpl(final Node e) {
        OgreNode nodeToTrack = (OgreNode) e;
        this.setAutotrack(this.pointer.getPointerAddress(), nodeToTrack.getPointer().getPointerAddress());
    }

    @Override
    public void autoTrack(final Point3D pos) {
        this.node.setPosition(pos);
        this.setAutotrack(this.pointer.getPointerAddress(), this.node.getPointer().getPointerAddress());
    }

    @Override
    protected Point3D rotateImpl(final float yaw, final float pitch) {
        float[] v = this.rotate(this.pointer.getPointerAddress(), yaw * OgreCamera.ROTATION_SPEED, pitch * OgreCamera.ROTATION_SPEED);
        return Point3D.valueOf(v[0], v[1], v[2]);
    }

    @Override
    protected void yaw(final float yaw) {
        this.rotate(this.pointer.getPointerAddress(), yaw * OgreCamera.ROTATION_SPEED, 0);
    }

    @Override
    protected Point3D moveImpl(final float xTranslation, final float yTranslation, final float zTranslation) {
        float[] v = this.move(this.pointer.getPointerAddress(), xTranslation, yTranslation, zTranslation);
        return Point3D.valueOf(v[0], v[1], v[2]);
    }

    @Override
    protected Point3D setPositionImpl(final int x, final int y, final Axis axis) {
        float[] v = this.setPositionAxis(this.pointer.getPointerAddress(), x, y, axis.ordinal());
        return Point3D.valueOf(v[0], v[1], v[2]);
    }

    @Override
    protected void setPositionImpl(final float xPosition, final float yPosition, final float zPosition) {
        this.setPosition(this.pointer.getPointerAddress(), xPosition, yPosition, zPosition);
    }

    @Override
    protected Point3D setOrientationImpl(final float x, final float y, final float z) {
        this.setOrientation(this.pointer.getPointerAddress(), x, y, z);
        return Point3D.valueOf(x, y, z);
    }

    @Override
    protected Point3D lookAtImpl(final Point3D target) {
        float[] l = this.lookAt(this.pointer.getPointerAddress(), target.x, target.y, target.z);
        return Point3D.valueOf(l[0], l[1], l[2]);
    }

    /**
     * Check if an object is viewable by the camera.
     *
     * @param position Object position.
     * @return <code>true</code> if the camera can view this object, <code>false</code> otherwise.
     */
    boolean see(final Point3D position) {
        return this.isVisible(this.pointer.getPointerAddress(), position.x, position.y, position.z);
    }

    @Override
    protected Point3D getDirectionImpl() {
        float[] v = this.getDirection(this.pointer.getPointerAddress());
        return Point3D.valueOf(v[0], v[1], v[2]);
    }

    /**
     * Force the listeners update in native code.
     */
    void forceListenersUpdate() {
        this.forceListenersUpdate(this.pointer.getPointerAddress());
    }

    /**
     * Detach the camera from its parent node.
     */
    void detachFromParent() {
        this.detachFromParent(this.pointer.getPointerAddress());
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
     * Rotate the camera in native code.
     *
     * @param pointer Address to the native object.
     * @param yaw     Rotation X axis.
     * @param pitch   Rotation Y axis.
     * @return The new camera direction in an array(0 = X, 1 = Y, 2 = Z);
     */
    private native float[] rotate(final long pointer, final float yaw, final float pitch);

    /**
     * Set the camera look to a position.
     *
     * @param pointer Address to the native object.
     * @param targetX Target position X value.
     * @param targetY Target position Y value.
     * @param targetZ Target position Z value.
     * @return The new camera direction in an array(0 = X, 1 = Y, 2 = Z);
     */
    private native float[] lookAt(final long pointer, final float targetX, final float targetY, final float targetZ);

    /**
     * Set the camera direction.
     *
     * @param pointer Address to the native object.
     * @param dirX    Direction X value.
     * @param dirY    Direction Y value.
     * @param dirZ    Direction Z value.
     */
    private native void setOrientation(final long pointer, final float dirX, final float dirY, final float dirZ);

    /**
     * Check if a position in visible by the camera.
     *
     * @param pointer   Address to the native object.
     * @param xPosition Position to check X value.
     * @param yPosition Position to check Y value.
     * @param zPosition Position to check Z value.
     * @return <code>true</code> if visible, <code>false</code> otherwise.
     */
    private native boolean isVisible(final long pointer, final float xPosition, final float yPosition, final float zPosition);

    /**
     * Set the camera position in native code.
     *
     * @param pointer Address to the native object.
     * @param posX    Camera new position X value.
     * @param posY    Camera new position Y value.
     * @param posZ    Camera new position Z value.
     */
    private native void setPosition(final long pointer, final float posX, final float posY, final float posZ);

    /**
     * Set the camera position in native code.
     *
     * @param pointer Address to the native object.
     * @param posX    Camera new position X value.
     * @param posY    Camera new position Y value.
     * @param ordinal Axis to assign X and Y.
     * @return The camera new position in an array(0 = X, 1 = Y, 2 = Z);
     */
    private native float[] setPositionAxis(final long pointer, final float posX, final float posY, final int ordinal);

    /**
     * Move the camera in native code.
     *
     * @param pointer      Address to the native object.
     * @param translationX Translation X value.
     * @param translationY Translation Y value.
     * @param translationZ Translation Z value.
     * @return The camera new position in an array(0 = X, 1 = Y, 2 = Z);
     */
    private native float[] move(final long pointer, final float translationX, final float translationY, final float translationZ);

    /**
     * Retrieve the camera direction in native code.
     *
     * @param pointer Address to the native object.
     * @return The camera direction in an array(0 = X, 1 = Y, 2 = Z);
     */
    private native float[] getDirection(final long pointer);

    /**
     * Detach from the parent node in native code.
     *
     * @param pointer Address of this yz::Camera.
     */
    private native void detachFromParent(final long pointer);

    /**
     * Use this when the camera is not moved directly(i.e. by nodes) to force listeners being updated.
     *
     * @param pointer Address to the native object.
     */
    private native void forceListenersUpdate(final long pointer);

    /**
     * Remove a listener in native code.
     *
     * @param pointer Address of this yz::Camera.
     * @param ls      Address of the listener to remove.
     */
    private native void unregisterListener(final long pointer, final long ls);

    /**
     * Activate auto tracking for a node in native code.
     *
     * @param pointer     Address of this yz::Camera.
     * @param nodePointer Address of the yz::Node to track.
     */
    private native void setAutotrack(final long pointer, final long nodePointer);

    /**
     * Deactivate auto tracking in native code.
     *
     * @param pointer Address of this yz::Camera.
     */
    private native void stopAutotrack(final long pointer);

    /**
     * Enable the rendering distance.
     *
     * @param pointer Pointer to the native object.
     */
    private native void enableRenderingDistance(final long pointer);

    /**
     * Set the far clip distance.
     *
     * @param pointer  Pointer to the native object.
     * @param distance Far clip distance.
     */
    private native void setFarClip(final long pointer, final int distance);

    /**
     * Set the near clip distance.
     *
     * @param pointer  Pointer to the native object.
     * @param distance Near clip distance.
     */
    private native void setNearClip(final long pointer, final int distance);

    /**
     * Throw a plane ray in native code to retrieve the movable in the plane.
     *
     * @param pointerAddress Address to the native yz::Camera*.
     * @param left           Plane left value.
     * @param top            Plane top value.
     * @param right          Plane right value.
     * @param bottom         Plane bottom value.
     * @return An array with the movable pointer addresses.
     */
    private native long[] throwPlaneRay(final long pointerAddress, final float left, final float top, final float right, final float bottom);

    /**
     * Throw a ray to retrieve an entity in native code.
     *
     * @param pointerAddress Address to the native yz::Camera*.
     * @param screenX        Screen X position to throw the ray.
     * @param screenY        Screen Y position to throw the ray.
     * @param poly           <code>true</code> to make selection with polygon precision, false to use bounding box.
     * @return The pointer value of the found movable object, if none, 0.
     */
    private native long throwRay(final long pointerAddress, final float screenX, final float screenY, final boolean poly);

    /**
     * Compute the intersection point between the mouse position and the invisible ground associated to the camera.
     *
     * @param pointerAddress Address to the native yz::Camera*.
     * @param screenX        Mouse x position.
     * @param screenY        Mouse y position.
     * @return The intersection point.
     */
    private native float[] computeMoveDestinationGroundIntersect(final long pointerAddress, final float screenX, final float screenY);
}
