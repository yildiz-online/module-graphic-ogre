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

#ifndef JNI_UTIL_H_INCLUDED
#define JNI_UTIL_H_INCLUDED

#include "stdafx.h"
#include <string>
#include <Ogre.h>

/**
*@author Grégory Van den Borre
*/
class JniStringWrapper {

    public:
        JniStringWrapper(JNIEnv* env, jstring& jstr) {
            this->env = env;
            this->jstr = jstr;
            this->str = env->GetStringUTFChars(jstr, 0);
        }

        ~JniStringWrapper() {
            this->env->ReleaseStringUTFChars(this->jstr, this->str);
        }

        std::string getValue() const {
            return this->str;
        }

    private:
        jstring jstr;
        const char* str;
        JNIEnv* env;
};

    inline void throwException(JNIEnv* env, const char* message) {
        jclass exception = env->FindClass("be/yildiz/common/exeption/NativeException");
        env->ThrowNew(exception, message);
    }

    /**
    * Convert an Ogre::Vector3 to a java float array.
    * @param env Java environment.
    * @param vector Vector3 to use to build the array.
    * @return A float array with a size of 3, index 0 = X, 1 = Y, 2 = Z.
    */
	inline jfloatArray vectorToArray(JNIEnv* env, const Ogre::Vector3& vector) {
    jfloat buf[3];
	buf[0] = vector.x;
	buf[1] = vector.y;
	buf[2] = vector.z;
	jfloatArray result =  env->NewFloatArray(3);
	env->SetFloatArrayRegion(result,0,3,buf);
	return result;
}

	inline jfloatArray quaternionToArray(JNIEnv* env, const Ogre::Quaternion& quat) {
    jfloat buf[4];
	buf[0] = quat.w;
	buf[1] = quat.x;
	buf[2] = quat.y;
	buf[3] = quat.z;
	jfloatArray result =  env->NewFloatArray(4);
	env->SetFloatArrayRegion(result,0,4,buf);
	return result;
}

	inline jfloatArray valuesToArray(JNIEnv* env, const float x, const float y, const float z) {
    jfloat buf[3];
	buf[0] = x;
	buf[1] = y;
	buf[2] = z;
	jfloatArray result =  env->NewFloatArray(3);
	env->SetFloatArrayRegion(result,0,3,buf);
	return result;
}


#endif
