/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 * Copyright (c) 2018 Grégory Van den Borre
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

#ifndef STENCIL_GLOW_H
#define STENCIL_GLOW_H

#include "stdafx.h"

// render queues
#define RENDER_QUEUE_OUTLINE_GLOW_OBJECTS	Ogre::RENDER_QUEUE_MAIN + 1
#define RENDER_QUEUE_OUTLINE_GLOW_GLOWS		Ogre::RENDER_QUEUE_MAIN + 2
#define RENDER_QUEUE_FULL_GLOW_ALPHA_GLOW	Ogre::RENDER_QUEUE_MAIN + 3
#define RENDER_QUEUE_FULL_GLOW_GLOW			Ogre::RENDER_QUEUE_MAIN + 4
#define LAST_STENCIL_OP_RENDER_QUEUE		RENDER_QUEUE_FULL_GLOW_GLOW

// stencil values
#define STENCIL_VALUE_FOR_OUTLINE_GLOW 1
#define STENCIL_VALUE_FOR_FULL_GLOW 2
#define STENCIL_FULL_MASK 0xFFFFFFFF

// a Render queue listener to change the stencil mode
/**
*@author Grégory Van den Borre
*/
class StencilOpQueueListener : public Ogre::RenderQueueListener 
{ 
public: 
    virtual void renderQueueStarted(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& skipThisInvocation) { 
        Ogre::RenderSystem * rendersys = Ogre::Root::getSingleton().getRenderSystem();
        rendersys->setStencilCheckEnabled(true); 
    
        if (queueGroupId == RENDER_QUEUE_OUTLINE_GLOW_OBJECTS) {// outline glow object 
            rendersys->clearFrameBuffer(Ogre::FBT_STENCIL); 
            rendersys->setStencilBufferParams(Ogre::CMPF_ALWAYS_PASS,
                STENCIL_VALUE_FOR_OUTLINE_GLOW, STENCIL_FULL_MASK, 
                Ogre::SOP_KEEP,Ogre::SOP_KEEP,Ogre::SOP_REPLACE,false);       
        } 
        if (queueGroupId == RENDER_QUEUE_OUTLINE_GLOW_GLOWS)  // outline glow
        { 
            rendersys->setStencilBufferParams(Ogre::CMPF_NOT_EQUAL,
                STENCIL_VALUE_FOR_OUTLINE_GLOW, STENCIL_FULL_MASK, 
                Ogre::SOP_KEEP,Ogre::SOP_KEEP,Ogre::SOP_REPLACE,false);       
        } 
        if (queueGroupId == RENDER_QUEUE_FULL_GLOW_ALPHA_GLOW)  // full glow - alpha glow
        { 
            rendersys->setStencilBufferParams(Ogre::CMPF_ALWAYS_PASS,
                STENCIL_VALUE_FOR_FULL_GLOW,STENCIL_FULL_MASK, 
                Ogre::SOP_KEEP,Ogre::SOP_KEEP,Ogre::SOP_REPLACE,false);       
        } 
        if (queueGroupId == RENDER_QUEUE_FULL_GLOW_GLOW)  // full glow - glow
        { 
            rendersys->setStencilBufferParams(Ogre::CMPF_EQUAL,
                STENCIL_VALUE_FOR_FULL_GLOW,STENCIL_FULL_MASK, 
                Ogre::SOP_KEEP,Ogre::SOP_KEEP,Ogre::SOP_ZERO,false);       
        } 

    } 

    virtual void renderQueueEnded(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& repeatThisInvocation) { 
        if ( queueGroupId == LAST_STENCIL_OP_RENDER_QUEUE ) { 
            Ogre::RenderSystem * rendersys = Ogre::Root::getSingleton().getRenderSystem(); 
            rendersys->setStencilCheckEnabled(false); 
            rendersys->setStencilBufferParams(); 
        } 
    } 

}; 


#endif
