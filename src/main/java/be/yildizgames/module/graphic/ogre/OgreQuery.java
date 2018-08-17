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

import be.yildizgames.common.geometry.Rectangle;
import be.yildizgames.common.jni.Native;
import be.yildizgames.common.jni.NativePointer;
import be.yildizgames.common.model.EntityId;
import be.yildizgames.module.graphic.query.Query;
import jni.JniQuery;

import java.util.Arrays;
import java.util.List;
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

    public OgreQuery(NativePointer pointer) {
        super();
        this.pointer = pointer;
    }

    @Override
    public EntityId getEntity(final float x, final float y) {
        return EntityId.valueOf(this.jni.throwRay(this.pointer.getPointerAddress(), x, y, false));
    }

    @Override
    public List<EntityId> getEntities(final Rectangle rectangle) {
        long[] result = this.jni.throwPlaneRay(this.pointer.getPointerAddress(), rectangle.getLeft(), rectangle.getTop(), rectangle.getRight(), rectangle.getBottom());
        return Arrays.stream(result)
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
