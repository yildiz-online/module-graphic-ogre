/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 * Copyright (c) 2019 Grégory Van den Borre
 *
 * More infos available: https://engine.yildiz-games.be
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

#ifndef YZ_RENDER_WINDOW_H
#define YZ_RENDER_WINDOW_H

#define RENDERWINDOW yz::RenderWindow

#include <Ogre.h>
#include "Camera.hpp"
#include "Viewport.hpp"

namespace yz {

/**
*@author Grégory Van den Borre
*/
class RenderWindow {

    public:


        static void create(Ogre::RenderWindow* rw) {
            LOG_FUNCTION
            if(instance == NULL) {
                instance = new RenderWindow(rw);
            }
        }

		yz::Viewport* addViewport(yz::Camera*);

		inline Ogre::RenderWindow* getWindow() const{
		    LOG_FUNCTION
		    return this->window;
		}

		inline float getFps() const{
		    LOG_FUNCTION
			return this->window->getStatistics().lastFPS;
		}

        inline void printScreen(const std::string& file) const{
            LOG_FUNCTION
            this->window->writeContentsToFile(file);
        }

        inline void addListener(Ogre::RenderTargetListener* listener) {
            LOG_FUNCTION
            this->window->addListener(listener);
        }

        static inline yz::RenderWindow* get() {
            LOG_FUNCTION
            return instance;
        }


    private:

        static yz::RenderWindow* instance;

		Ogre::RenderWindow* window;

		RenderWindow(Ogre::RenderWindow* rw);

};
}
#endif

