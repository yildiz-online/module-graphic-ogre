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

import be.yildizgames.module.coordinate.BaseCoordinate;
import be.yildizgames.module.graphic.Font;
import be.yildizgames.module.graphic.gui.container.Container;
import be.yildizgames.module.graphic.gui.internal.impl.StandardGuiFactory;
import be.yildizgames.module.graphic.material.Material;
import be.yildizgames.module.window.ScreenSize;

/**
 * Ogre implementation for the GuiBuilder.
 *
 * @author Grégory Van den Borre
 */
final class OgreGuiFactory extends StandardGuiFactory {


    /**
     * Simple constructor.
     * Use the getter in the graphic engine.
     * This constructor will be package protected in future version
     *
     * @param screenSize Contains the screen size data.
     */
    OgreGuiFactory(final ScreenSize screenSize) {
        super(screenSize);
    }

    /**
     * Build a new container.
     *
     * @param name        Container name, must be unique.
     * @param coordinates Container size and position.
     * @param background  Container background material.
     * @return The newly built container.
     */
    @Override
    public OgreGuiContainer buildContainerElement(final String name,
                                                 final BaseCoordinate coordinates, final Material background) {
        return new OgreGuiContainer(name, background, coordinates,
                this.screenSize.width, this.screenSize.height, false);
    }

    /**
     * Build a new container.
     *
     * @param name        Container name, must be unique.
     * @param coordinates Container size and position.
     * @param background  Container background material.
     * @param parent      Container holding the container to build.
     * @param widget      <code>true</code> to consider the container as part as other
     *                    element, it will be considered as element.
     * @return The newly built container.
     */
    @Override
    public OgreGuiContainer buildContainerElement(final String name,
                                                 final BaseCoordinate coordinates, final Material background,
                                                 final Container parent, final boolean widget) {
        return new OgreGuiContainer(name, background, coordinates, parent,
                this.screenSize.width, this.screenSize.height, widget);
    }

    /**
     * Build a new icon element.
     *
     * @param name        Icon name, must be unique.
     * @param coordinates Icon size and position.
     * @param background  Icon background material.
     * @param container   Container holding the icon.
     * @return The newly built icon element.
     */
    @Override
    protected OgreIcon buildIconElement(final String name,
                                                   final BaseCoordinate coordinates, final Material background,
                                                   final Container container) {
        return new OgreIcon(name, coordinates, background, container);
    }

    /**
     * Build a new text element.
     *
     * @param coordinates Text size and position.
     * @param font        Text font.
     * @param container   Container holding the text.
     * @return The newly built text element.
     */
    @Override
    protected OgreText buildTextElement(
            final BaseCoordinate coordinates, final Font font,
            final Container container) {
        return new OgreText(coordinates, font, container);
    }
}
