//        This file is part of the Yildiz-Online project, licenced under the MIT License
//        (MIT)
//
//        Copyright (c) 2016 Grégory Van den Borre
//
//        More infos available: http://yildiz.bitbucket.org
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
//        of this software and associated documentation files (the "Software"), to deal
//        in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
//        furnished to do so, subject to the following conditions:
//
//        The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
//        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//        SOFTWARE.

package be.yildiz.module.graphic.ogre;

import be.yildiz.common.BaseCoordinate;
import be.yildiz.common.Size;
import be.yildiz.module.graphic.Font;
import be.yildiz.module.graphic.Material;
import be.yildiz.module.graphic.gui.AbstractIconElement;
import be.yildiz.module.graphic.gui.AbstractTextElement;
import be.yildiz.module.graphic.gui.GuiBuilder;
import be.yildiz.module.graphic.gui.GuiContainer;

/**
 * Ogre implementation for the GuiBuilder.
 *
 * @author Grégory Van den Borre
 */
public final class OgreGuiBuilder extends GuiBuilder {


    /**
     * Simple constructor.
     * Use the getter in the graphic engine.
     * This constructor will be package protected in future version
     *
     * @param screenSize Contains the screen size data.
     */
    public OgreGuiBuilder(final Size screenSize) {
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
    public GuiContainer buildContainerElement(final String name,
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
    public GuiContainer buildContainerElement(final String name,
                                                 final BaseCoordinate coordinates, final Material background,
                                                 final GuiContainer parent, final boolean widget) {
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
    protected AbstractIconElement buildIconElement(final String name,
                                                   final BaseCoordinate coordinates, final Material background,
                                                   final GuiContainer container) {
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
    protected AbstractTextElement buildTextElement(
            final BaseCoordinate coordinates, final Font font,
            final GuiContainer container) {
        return new OgreText(coordinates, font, container);
    }
}
