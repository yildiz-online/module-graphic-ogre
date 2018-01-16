/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 *  Copyright (c) 2017 Grégory Van den Borre
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

import be.yildiz.module.graphic.Node;
import be.yildizgames.common.collection.Sets;
import be.yildizgames.common.geometry.Movable;
import be.yildizgames.common.geometry.Point3D;
import be.yildizgames.common.geometry.Quaternion;
import be.yildizgames.common.model.EntityId;
import be.yildizgames.common.nativeresources.Native;
import be.yildizgames.common.nativeresources.NativePointer;
import be.yildizgames.common.util.Deletable;
import jni.OgreNodeNative;

import java.util.Set;

/**
 * @author Grégory Van den Borre
 */
abstract class OgreNodeBase extends Node implements OgreNode {

    /**
     * Pointer address to the associated yz::Node.
     */
    private final NativePointer pointer;

    private final OgreNodeNative nodeNative = new OgreNodeNative();

    /**
     * Name specified in native code.
     */
    private final String name;

    protected Movable parent;

    private final Set<Movable> childrenList = Sets.newSet();

    private final Set<Movable> optionalList = Sets.newSet();

    /**
     * Full constructor.
     *
     * @param pointerAddress Address to the native object.
     */
    protected OgreNodeBase(final NativePointer pointerAddress, final Movable parent) {
        super(parent);
        this.pointer = pointerAddress;
        this.name = this.nodeNative.getName(this.pointer.getPointerAddress());
        this.parent = parent;
    }

    /**
     * Full constructor.
     *
     * @param pointerAddress Address to the native object.
     */
    protected OgreNodeBase(final NativePointer pointerAddress, final EntityId id, final Movable parent) {
        super(id, parent);
        this.pointer = pointerAddress;
        this.name = this.nodeNative.getName(this.pointer.getPointerAddress());
        this.parent = parent;
    }

    /**
     * @return The current object position from the native code.
     */
    @Override
    public final Point3D getPosition() {
        float[] v = this.nodeNative.getPosition(this.pointer.getPointerAddress());
        return Point3D.valueOf(v[0], v[1], v[2]);
    }

    @Override
    public final Point3D getDirection() {
        float[] v = this.nodeNative.getDirection(this.pointer.getPointerAddress());
        return Point3D.valueOf(v[0], v[1], v[2]);
    }

    public final String getName() {
        return name;
    }

    @Override
    public final void show() {
        this.nodeNative.show(this.pointer.getPointerAddress());
    }

    @Override
    public final void hide() {
        this.nodeNative.hide(this.pointer.getPointerAddress());
    }

    @Override
    public final Quaternion getOrientation() {
        float[] v = this.nodeNative.getOrientation(this.pointer.getPointerAddress());
        return new Quaternion(v[0], v[1], v[2], v[3]);
    }


    @Override
    public final void detachFromParent() {
        this.parent.removeChild(this);
        this.nodeNative.detachFromParent(this.pointer.getPointerAddress(),
                Native.class.cast(this.parent.getInternal()).getPointer().getPointerAddress());
    }

    @Override
    public final void removeChild(Movable child) {
        this.childrenList.remove(child);
        this.optionalList.remove(child);
    }
    @Override
    public final void addOptionalChild(Movable child) {
        if(this.optionalList.add(child)) {
            child.attachToOptional(this);
        }
    }

    @Override
    public final void addChild(Movable child) {
        if(this.childrenList.add(child)) {
            child.attachTo(this);
        }
    }

    /**
     * Delete the node and free its resources.
     */
    protected final void deleteImpl() {
        this.nodeNative.delete(this.pointer.getPointerAddress());
        this.optionalList.forEach(Movable::detachFromParent);
        for(Movable m : this.childrenList) {
            ((Deletable)m).delete();
        }
        this.optionalList.clear();
        this.childrenList.clear();
        this.pointer.delete();
    }

    @Override
    public final Movable getInternal() {
        return this;
    }

    @Override
    public final NativePointer getPointer() {
        return this.pointer;
    }


    @Override
    public String toString() {
        return "Ogre node movable " + this.getName() +  " : pointer:" + this.pointer;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + ((this.name == null) ? 0 : this.name.hashCode());
        result = prime * result + ((this.pointer == null) ? 0 : this.pointer.hashCode());
        return result;
    }

    @Override
    public boolean equals(final Object obj) {
        if (this == obj) {
            return true;
        }
        if (!(obj instanceof OgreNodeBase)) {
            return false;
        }
        OgreNodeBase other = (OgreNodeBase) obj;
        return this.name.equals(other.name) && this.pointer.equals(other.pointer);
    }
}
