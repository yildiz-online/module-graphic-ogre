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

import java.io.IOException;

/**
 * @author Grégory Van den Borre
 */
@SuppressWarnings("rawtypes")
public class BaseJniTest {

    public BaseJniTest() {
        super();
    }

    protected final void testJni(Class clazz, String h, String c) throws IOException {
        //JniChecker checker = new JniChecker("D:/development/javadev/prj/yildiz_native_ogre/src/jni/include", "D:/development/javadev/prj/yildiz_native_ogre/src/jni/source");
        // FIXME uncomment.
        // checker.check(clazz, h, c);
    }

    public final void test() throws IOException {
        this.testJni(OgreBillboardChain.class, "jniBillboardChain.h", "jniBillboardChain.cpp");
        this.testJni(OgreBillboardSet.class, "jniBillboardSet.h", "jniBillboardSet.cpp");
        this.testJni(OgreBillboard.class, "jniBillboard.h", "jniBillboard.cpp");
        this.testJni(OgreCamera.class, "jniCamera.h", "jniCamera.cpp");
        this.testJni(OgreElectricArc.class, "jniElectricArc.h", "jniElectricArc.cpp");
        this.testJni(OgreEntity.class, "jniOgreEntity.h", "jniOgreEntity.cpp");
        this.testJni(OgreFont.class, "jniFont.h", "jniFont.cpp");
        this.testJni(OgreGuiContainer.class, "jniGuiContainer.h", "jniGuiContainer.cpp");
        this.testJni(OgreIcon.class, "jniGuiIcon.h", "jniGuiIcon.cpp");
        this.testJni(OgreLensFlare.class, "jniLensFlare.h", "jniLensFlare.cpp");
        this.testJni(OgreLine.class, "jniDynamicLine.h", "jniDynamicLine.cpp");
        this.testJni(OgreMaterialPass.class, "jniMaterialPass.h", "jniMaterialPass.cpp");
        this.testJni(OgreMaterialTechnique.class, "jniMaterialTechnique.h", "jniMaterialTechnique.cpp");
        this.testJni(OgreMaterial.class, "jniMaterial.h", "jniMaterial.cpp");
        this.testJni(OgreMovableText.class, "jniMovableText.h", "jniMovableText.cpp");
        this.testJni(OgreNode.class, "jniNode.h", "jniNode.cpp");
        this.testJni(OgreParticleEmitter.class, "jniParticleEmitter.h", "jniParticleEmitter.cpp");
        this.testJni(OgreParticleSystem.class, "jniParticleSystem.h", "jniParticleSystem.cpp");
        this.testJni(OgrePointLight.class, "jniPointLight.h", "jniPointLight.cpp");
        this.testJni(RenderWindow.class, "jniRenderWindow.h", "jniRenderWindow.cpp");
        this.testJni(Root.class, "jniRoot.h", "jniRoot.cpp");
        this.testJni(OgreSceneManager.class, "jniOgreWorld.h", "jniOgreWorld.cpp");
        this.testJni(OgreSpotLight.class, "jniSpotLight.h", "jniSpotLight.cpp");
        this.testJni(OgreText.class, "jniGuiText.h", "jniGuiText.cpp");
        this.testJni(OgreTextureUnit.class, "jniMaterialUnit.h", "jniMaterialUnit.cpp");
    }
}
