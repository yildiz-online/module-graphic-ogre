/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 *  Copyright (c) 2019 Grégory Van den Borre
 *
 *  More infos available: https://engine.yildiz-games.be
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

import be.yildizgames.common.geometry.Rectangle;
import be.yildizgames.common.jni.Native;
import be.yildizgames.common.jni.NativePointer;
import be.yildizgames.common.model.EntityId;
import be.yildizgames.module.graphic.query.Query;
import jni.JniQuery;

import java.util.Arrays;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

/**
 * Ogre implementation for a Query.
 *
 * @author Grégory Van den Borre
 */
public final class OgreQuery implements Query, Native {

    /**
     * Pointer address to the native code object.
     */
    private final NativePointer pointer;

    private final JniQuery jni = new JniQuery();
    private final float resolutionX;
    private final float resolutionY;

    public OgreQuery(NativePointer pointer, float resolutionX, float resolutionY) {
        super();
        this.pointer = pointer;
        this.resolutionX = resolutionX;
        this.resolutionY = resolutionY;
    }

    @Override
    public Optional<EntityId> getEntity(final float x, final float y) {
        final float screenX = x / this.resolutionX;
        final float screenY = y / this.resolutionY;
        EntityId id =  EntityId.valueOf(this.jni.throwRay(this.pointer.getPointerAddress(), screenX, screenY, false));
        if (id.equals(EntityId.WORLD)) {
            return Optional.empty();
        }
        return Optional.of(id);
    }

    @Override
    public List<EntityId> getEntities(final Rectangle rectangle) {
        final float left = rectangle.getLeft() / this.resolutionX;
        final float top = rectangle.getTop() / this.resolutionY;
        final float right = rectangle.getRight() / this.resolutionX;
        final float bottom = rectangle.getBottom() / this.resolutionY;
        final long[] tab = this.jni.throwPlaneRay(this.pointer.getPointerAddress(), left, top, right, bottom);
        return Arrays.stream(tab)
                .mapToObj(EntityId::valueOf)
                .collect(Collectors.toList());
    }

    @Override
    public void delete() {
        this.pointer.delete();
    }

    @Override
    public NativePointer getPointer() {
        return this.pointer;
    }


}
