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

import be.yildiz.module.graphic.GraphicMovable;
import be.yildiz.module.graphic.GraphicObject;
import be.yildiz.module.graphic.Material;
import be.yildizgames.common.gameobject.Movable;
import be.yildizgames.common.geometry.Point3D;
import be.yildizgames.common.model.EntityId;

/**
 * Common code for all Ogre Bullet objects.
 *
 * @author Grégory Van den Borre
 */
public class OgreObject extends GraphicObject implements GraphicMovable {

    /**
     * Object id.
     */
    private final EntityId id;

    /**
     * Ogre scene node.
     */
    private final OgreNodeBase node;

    /**
     * Ogre 3D entity.
     */
    private final OgreEntity entity;


    /**
     * Current scale factor.
     */
    private Point3D scaleSize = Point3D.valueOf(1);

    /**
     * Full constructor.
     *
     * @param associatedId Object unique id.
     * @param ogreEntity   Ogre entity.
     */
    protected OgreObject(final EntityId associatedId, final OgreEntity ogreEntity) {
        super();
        this.id = associatedId;
        this.node = ogreEntity.getNode();
        this.entity = ogreEntity;
        if (this.id.equals(EntityId.WORLD)) {
            this.setUnpickable();
        }
    }


    @Override
    public final Point3D getPosition() {
        return this.node.getPosition();
    }

    @Override
    public final Point3D getAbsolutePosition() {
        return this.node.getAbsolutePosition();
    }

    @Override
    public final void setPosition(final Point3D pos) {
        this.node.setPosition(pos);
    }

    @Override
    public final Point3D getDirection() {
        return this.node.getDirection();
    }

    @Override
    public final void setDirection(final Point3D dir) {
        assert dir != null;
        this.node.setDirection(dir);
    }

    @Override
    protected final void castShadowImpl(final boolean cast) {
        this.entity.castShadow(cast);
    }

    @Override
    public final OgreObject setParameter(final int index, final float v1, final float v2, final float v3, final float v4) {
        this.entity.setParameter(index, v1, v2, v3, v4);
        return this;
    }

    @Override
    public final void rotate(final float x, final float y, final float z, final float w) {
        this.node.rotate(x, y, z, w);
    }

    /**
     * Rotate the object if it is not static.
     *
     * @param yaw   Rotation value on X axis.
     * @param pitch Rotation value on Y axis.
     */
    @Override
    public final void rotate(final float yaw, final float pitch) {
        this.node.rotate(yaw, pitch);
    }

    @Override
    public final void lookAt(final Point3D target) {
        this.setDirection(target.subtract(this.getPosition()));
    }

    @Override
    public Point3D getAbsoluteDirection() {
        return this.node.getAbsoluteDirection();
    }

    @Override
    public void addOptionalChild(Movable child) {
        this.node.addOptionalChild(child);
    }

    @Override
    protected final void showImpl() {
        this.node.show();
    }

    @Override
    public final void delete() {
        this.node.delete();
    }

    @Override
    public OgreObject setRenderingDistance(final int distance) {
        this.entity.setRenderingDistance(distance);
        return this;
    }

    @Override
    protected final void hideImpl() {
        this.node.hide();
    }

    @Override
    public final OgreObject setUnpickable() {
        this.entity.setUnpickable();
        return this;
    }

    @Override
    public final OgreObject setRenderBehind() {
        this.entity.renderBehind();
        return this;
    }

    @Override
    public final OgreObject scale(final float x, final float y, final float z) {
        this.scaleSize = Point3D.valueOf(x, y, z);
        this.node.scale(x, y, z);
        return this;
    }

    @Override
    public final void setPosition(float posX, float posY, float posZ) {
        this.node.setPosition(posX, posY, posZ);
    }

    @Override
    public final void setDirection(float dirX, float dirY, float dirZ) {
        this.node.setDirection(dirX, dirY, dirZ);
    }

    @Override
    public final void detachFromParent() {
        this.node.detachFromParent();
    }

    @Override
    public final void addChild(Movable other) {
        this.node.addChild(other);
    }

    @Override
    public void removeChild(Movable child) {
        this.node.removeChild(child);
    }

    @Override
    public void attachTo(Movable other) {
        this.node.attachTo(other);
    }

    @Override
    public void attachToOptional(Movable other) {
        this.node.attachToOptional(other);
    }

    @Override
    protected final void setMaterialImpl(final Material material) {
        this.entity.setMaterial(material);
    }

    public final EntityId getId() {
        return this.id;
    }

    @Override
    public final OgreNodeBase getNode() {
        return this.node;
    }

    @Override
    public Point3D getScaleSize() {
        return scaleSize;
    }

    @Override
    public Movable getInternal() {
        return this.node;
    }
}
