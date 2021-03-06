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

#ifndef YZ_CG_SHADER_H
#define YZ_CG_SHADER_H

#include "stdafx.h"

namespace yz {
/**
*@author Grégory Van den Borre
*/
class CgShader {

public:

    CgShader(
        const std::string& name,
        const std::string& file,
        Ogre::GpuProgramType& type) {
        LOG_FUNCTION
        this->shader =
                Ogre::HighLevelGpuProgramManager::getSingleton().createProgram(
                        name,
                        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                        "cg", type).getPointer();
        shader->setSourceFile(file);
    }

    //FIXME dtor

    //FIXME export in cpp file

    void setParameter(
        const std::string& paramName,
        const std::string& paramValue) {
        LOG_FUNCTION
        this->shader->setParameter(paramName, paramValue);
    }

    static inline CgShader* get(const POINTER pointer) {
        LOG_FUNCTION
        return reinterpret_cast<CgShader*>(pointer);
    }

private:
    Ogre::HighLevelGpuProgram* shader;
};

}
#endif
