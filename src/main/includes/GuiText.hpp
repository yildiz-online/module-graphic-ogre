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

#ifndef YZ_GUI_TEXT_H
#define YZ_GUI_TEXT_H

#include "stdafx.h"
#include "GuiContainer.hpp"
#include "Font.hpp"
#include <Overlay/OgreTextAreaOverlayElement.h>

namespace yz {

/**
 * Wrap an ogre text overlay.
 * @author Grégory Van den Borre
 */
class GuiText {

public:

	/**
	 * Full constructor.
	 * @param parent Container holding the element.
	 * @param name Element name, must be unique.
	 */
	GuiText(yz::GuiContainer* parent, const std::string& name);

	/**
	 * Destructor.
	 */
	virtual ~GuiText();

	/**
	 * Set the element visible.
	 */
	inline void show() {
	    LOG_FUNCTION
		this->text->show();
	}

	/**
	 * Set the element invisible.
	 */
	inline void hide() {
	    LOG_FUNCTION
		this->text->hide();
	}

	/**
	 * Move the element to left or right from its current position.
	 * @param left Value to add to the left position.
	 */
	inline void addToLeft(const Ogre::Real left) {
	    LOG_FUNCTION
		this->text->setLeft(this->text->getLeft() + left);
	}

	/**
	 * Move the element to up or down from its current position.
	 * @param top Value to add to the top position.
	 */
	inline void addToTop(const Ogre::Real top) {
	    LOG_FUNCTION
		this->text->setTop(this->text->getTop() + top);
	}

	/**
	 * Update the text to print.
	 * @param text New text to print.
	 */
	inline void setText(const std::string& text) {
	    LOG_FUNCTION
		this->text->setCaption(Ogre::UTFString(text));
	}

	/**
	 * Change the font to use to print the text.
	 * @param font Name of the font to use.
	 * @param charHeight Size of the font to use.
	 */
	inline void setFont(const yz::Font* font, const Ogre::Real charHeight) {
	    LOG_FUNCTION
		this->text->setFontName(font->getName());
		this->text->setCharHeight(charHeight);
	}

	/**
	 * Update the text size.
	 * @param width New text width.
	 * @param height New text height.
	 */
	inline void setSize(const Ogre::Real width, const Ogre::Real height) {
	    LOG_FUNCTION
		this->text->setDimensions(width, height);
	}

	/**
	 * Update the text position, from the parent container border, in pixel.
	 * @param left Left position from the container border.
	 * @param top Top position from the container border.
	 */
	inline void setPosition(const Ogre::Real left, const Ogre::Real top) {
	    LOG_FUNCTION
		this->text->setPosition(left, top);
	}

	/**
	 * Update the text color.
	 */
	inline void setColor(const Ogre::Real red, const Ogre::Real green,
			const Ogre::Real blue, const Ogre::Real alpha) {
	    LOG_FUNCTION
		this->text->setColour(Ogre::ColourValue(red, green, blue, alpha));
	}

    inline static yz::GuiText* get(const POINTER pointer) {
        LOG_FUNCTION
        return reinterpret_cast<yz::GuiText*>(pointer);
    }

private:

	/**
	 * Wrapped element.
	 */
	Ogre::TextAreaOverlayElement* text;
};
}

#endif
