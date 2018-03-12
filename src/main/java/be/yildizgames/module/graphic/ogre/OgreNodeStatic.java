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
import be.yildizgames.common.jni.NativePointer;
import jni.JniNode;

/**
 * @author Grégory Van den Borre
 */
public class OgreNodeStatic extends OgreNodeBase {

    public OgreNodeStatic(NativePointer pointerAddress, Movable parent, Point3D position, Point3D direction) {
        super(pointerAddress, parent);
        JniNode n = new JniNode();
        n.setPosition(pointerAddress.getPointerAddress(), position.x, position.y, position.z);
        n.setDirection(pointerAddress.getPointerAddress(), direction.x, direction.y, direction.z);
    }

    private OgreNodeStatic(NativePointer pointerAddress) {
        super(pointerAddress, null);
    }

    public static OgreNodeStatic root(NativePointer pointerAddress) {
        return new OgreNodeStatic(pointerAddress);
    }

    @Override
    public void setPosition(final Point3D position) {
        // Static node does not change position.
    }

    @Override
    public void scale(float scaleX, float scaleY, float scaleZ) {
        // Static node does not change scale.
    }

    @Override
    public final void rotate(final float x, final float y, final float z, final float w) {
        // Static node does not rotate.
    }

    @Override
    public Point3D rotate(final float yaw, final float pitch) {
        // Static node does not rotate.
        return this.getDirection();
    }

    @Override
    public Point3D translate(final float moveX, final float moveY, final float moveZ) {
        // Static node does not translate.
        return this.getPosition();
    }

    @Override
    public void setDirection(final float dirX, final float dirY, final float dirZ) {
        // Static node does not change direction.
    }

    @Override
    public void setPosition(float posX, float posY, float posZ) {
        // Does nothing.
    }

    @Override
    public String toString() {
        return "Ogre node static " + this.getName() +  " : pointer:" + this.getPointer();
    }


    @Override
    public final void attachTo(final Movable other) {
        //Static, does nothing.
    }


    @Override
    public void attachToOptional(Movable other) {
        //Static, does nothing.
    }
}
