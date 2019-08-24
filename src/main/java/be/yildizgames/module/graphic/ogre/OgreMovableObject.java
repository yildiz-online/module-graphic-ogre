package be.yildizgames.module.graphic.ogre;

import be.yildizgames.common.gameobject.Movable;
import be.yildizgames.common.geometry.Point3D;

class OgreMovableObject {

    /**
     * Associated node.
     */
    private final OgreNode node;

    OgreMovableObject(OgreNode node) {
        this.node = node;
    }

    public final void detachFromParent() {
        this.node.detachFromParent();
    }

    public final void setPosition(float posX, float posY, float posZ) {
        this.node.setPosition(posX, posY, posZ);
    }

    public final void setDirection(float dirX, float dirY, float dirZ) {
        this.node.setDirection(dirX, dirY, dirZ);
    }

    public final void addChild(Movable child) {
        this.node.addChild(child);
    }

    public final Point3D getPosition() {
        return this.node.getPosition();
    }

    public final void setPosition(final Point3D position) {
        this.node.setPosition(position);
    }

    public final Point3D getAbsolutePosition() {
        return this.node.getAbsolutePosition();
    }

    public final Point3D getDirection() {
        return this.node.getDirection();
    }

    public final void setDirection(final Point3D direction) {
        this.node.setDirection(direction);
    }

    public final Point3D getAbsoluteDirection() {
        return this.node.getAbsoluteDirection();
    }

    public final void addOptionalChild(Movable child) {
        this.node.addOptionalChild(child);
    }

    public final void removeChild(Movable child) {
        this.node.removeChild(child);
    }

    public final Movable getInternal() {
        return this.node;
    }

    public final void attachTo(final Movable other) {
        this.node.attachTo(other);
    }

    public final void attachToOptional(final Movable other) {
        this.node.attachToOptional(other);
    }

}
