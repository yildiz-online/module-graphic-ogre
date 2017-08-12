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

import be.yildiz.common.gameobject.Movable;
import be.yildiz.common.id.EntityId;
import be.yildiz.common.vector.Point3D;
import be.yildiz.module.graphic.BaseGraphicObject;
import be.yildiz.module.graphic.GraphicMovable;
import be.yildiz.module.graphic.Material;

/**
 * Common code for all Ogre Bullet objects.
 *
 * @author Grégory Van den Borre
 */
public abstract class AbstractOgreObject extends BaseGraphicObject implements GraphicMovable {

    /**
     * Object id.
     */
    private final EntityId id;

    /**
     * Ogre scene node.
     */
    private final OgreNode node;

    /**
     * Ogre 3D entity.
     */
    private final OgreEntity entity;
    /**
     * Flag to check if static or not.
     */
    private final boolean staticObject;
    /**
     * Object position.
     */
    private Point3D position;
    /**
     * Object direction.
     */
    private Point3D direction;

    /**
     * Current scale factor.
     */
    private Point3D scaleSize = Point3D.valueOf(1);

    /**
     * Full constructor.
     *
     * @param associatedId Object unique id.
     * @param ogreEntity   Ogre entity.
     * @param staticObject <code>true</code> if the object is static.
     */
    protected AbstractOgreObject(final EntityId associatedId, final OgreEntity ogreEntity, final boolean staticObject) {
        super();
        this.id = associatedId;
        this.node = ogreEntity.getNode();
        this.entity = ogreEntity;
        this.position = this.node.getPosition();
        this.direction = this.node.getDirection();
        if (this.id.equals(EntityId.WORLD)) {
            this.setUnpickable();
        }
        this.staticObject = staticObject;
    }

    @Override
    protected final void castShadowImpl(final boolean cast) {
        this.entity.castShadow(cast);
    }

    @Override
    public final AbstractOgreObject setParameter(final int index, final float v1, final float v2, final float v3, final float v4) {
        this.entity.setParameter(index, v1, v2, v3, v4);
        return this;
    }

    public final void setDirection(final Point3D dir) {
        assert dir != null;
        if (!this.staticObject) {
            this.direction = dir;
            this.node.setDirection(dir);
            this.setDirectionImpl(dir);
        }
    }

    @Override
    public final void setPosition(final Point3D pos) {
        if (!this.staticObject) {
            this.position = pos;
            this.node.setPosition(pos);
        }
    }

    @Override
    public final void rotate(final float x, final float y, final float z, final float w) {
        if (!this.staticObject) {
            this.node.rotate(x, y, z, w);
        }
    }

    /**
     * Rotate the object if it is not static.
     *
     * @param yaw   Rotation value on X axis.
     * @param pitch Rotation value on Y axis.
     */
    @Override
    public final void rotate(final float yaw, final float pitch) {
        if (!this.staticObject) {
            this.node.rotate(yaw, pitch);
        }
    }

    @Override
    public final void lookAt(final Point3D target) {
        if (!this.staticObject) {
            this.setDirection(target.subtract(this.getPosition()));
        }
    }

    public final void attachTo(final Movable other) {
        if (!this.staticObject) {
            this.node.attachTo(((GraphicMovable) other).getNode());
        }
    }

    public final void attachToOptional(final Movable other) {
        if (!this.staticObject) {
            this.node.attachToOptional(((GraphicMovable) other).getNode());
        }
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
    public AbstractOgreObject setRenderingDistance(final int distance) {
        this.entity.setRenderingDistance(distance);
        return this;
    }

    @Override
    protected final void hideImpl() {
        this.node.hide();
    }

    @Override
    public final AbstractOgreObject setUnpickable() {
        this.entity.setUnpickable();
        return this;
    }

    @Override
    public final BaseGraphicObject setRenderBehind() {
        this.entity.renderBehind();
        return this;
    }

    @Override
    public final AbstractOgreObject scale(final float x, final float y, final float z) {
        this.scaleSize = Point3D.valueOf(x, y, z);
        this.node.scale(x, y, z);
        this.scaleImpl(x, y, z);
        return this;
    }

    @Override
    protected final void setMaterialImpl(final Material material) {
        this.entity.setMaterial(material);
    }

    public final EntityId getId() {
        return this.id;
    }

    @Override
    public final OgreNode getNode() {
        return this.node;
    }

    public Point3D getPosition() {
        return position;
    }

    public Point3D getDirection() {
        return direction;
    }

    @Override
    public Point3D getScaleSize() {
        return scaleSize;
    }

    /**
     * Implementation specific code for deleting the object.
     */
    protected abstract void deleteImpl();

    /**
     * Implementation specific code for scaling.
     *
     * @param x X scale value.
     * @param y Y scale value.
     * @param z Z scale value.
     */
    protected abstract void scaleImpl(float x, float y, float z);

    /**
     * Implementation specific code for setting the position.
     *
     * @param position Position value.
     */
    protected abstract void setPositionImpl(Point3D position);

    /**
     * Implementation specific code for setting the direction.
     *
     * @param dir Direction value.
     */
    protected abstract void setDirectionImpl(Point3D dir);

}
