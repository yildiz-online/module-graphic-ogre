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

/**
 * Ogre Bullet implementation for manually movable object, the motion state is kinematic and associated with Ogre SceneNode, so moving the bullet motion state will update the SceneNode.
 *
 * @author Grégory Van den Borre
 */
public final class OgreMovableObject extends AbstractOgreObject {

    /**
     * Full constructor.
     *
     * @param id       Object unique Id.
     * @param entity   Graphic part of the object.
     */
    public OgreMovableObject(final EntityId id, final OgreEntity entity) {
        super(id, entity, false);
    }

    @Override
    public Point3D getAbsolutePosition() {
        // FIXME implements add child and correct this
        return this.getPosition();
    }

    @Override
    public void setAbsolutePosition(Point3D pos) {
        // TODO Auto-generated method stub

    }

    @Override
    public Point3D getAbsoluteDirection() {
        // FIXME implements add child and correct this
        return this.getPosition();
    }

    @Override
    public void scaleImpl(final float x, final float y, final float z) {
    }

    @Override
    public void deleteImpl() {
    }

    @Override
    public void sleep(final boolean b) {
    }

    @Override
    protected void setPositionImpl(final Point3D position) {
    }

    @Override
    protected void setDirectionImpl(final Point3D dir) {
    }

    @Override
    public void detach(Movable other) {
        // TODO Auto-generated method stub

    }

    @Override
    public void addChild(Movable other) {
        // TODO Auto-generated method stub

    }
}
