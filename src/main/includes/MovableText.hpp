/**
 * File: MovableText.h
 *
 * description: This create create a billboarding object that display a text.
 *
 * @author   2003 by cTh see gavocanov@rambler.ru
 * @update   2006 by barraq see nospam@barraquand.com
 * @update   2012 to work with newer versions of OGRE by MindCalamity <mindcalamity@gmail.com>
 *   - See "Notes" on: http://www.ogre3d.org/tikiwiki/tiki-editpage.php?page=MovableText
 */

#ifndef __include_MovableText_H__
#define __include_MovableText_H__

#define MOVABLETEXT YZ::MovableText

#include "stdafx.h"
#include "Font.hpp"

namespace YZ {

class MovableText: public Ogre::MovableObject, public Ogre::Renderable {
public:
    enum HorizontalAlignment {
        H_LEFT, H_CENTER
    };
    enum VerticalAlignment {
        V_BELOW, V_ABOVE, V_CENTER
    };

private:

    std::string mFontName;
    std::string mType;
    std::string mName;
    std::string mCaption;
    HorizontalAlignment mHorizontalAlignment;
    VerticalAlignment mVerticalAlignment;

    Ogre::ColourValue mColor;
    Ogre::RenderOperation mRenderOp;
    Ogre::AxisAlignedBox mAABB;
    Ogre::LightList mLList;

    Ogre::Real mCharHeight;
    Ogre::Real mSpaceWidth;

    bool mNeedUpdate;
    bool mUpdateColors;
    bool mOnTop;

    const Ogre::Real mTimeUntilNextToggle;
    Ogre::Real mRadius;

    Ogre::Vector3 mGlobalTranslation;
    Ogre::Vector3 mLocalTranslation;

    Ogre::Camera *mpCam;
    Ogre::RenderWindow *mpWin;
    YZ::Font *mpFont;
    Ogre::MaterialPtr mpMaterial;
    Ogre::MaterialPtr mpBackgroundMaterial;

    /******************************** public methods ******************************/
public:
    MovableText(
        const std::string& name,
        const std::string& caption,
        YZ::Font* font,
        const Ogre::Real charHeight,
        const Ogre::ColourValue &color = Ogre::ColourValue::White);

    virtual ~MovableText();

    // Add to build on Shoggoth:
    virtual void visitRenderables(
        Ogre::Renderable::Visitor* visitor,
        bool debugRenderables = false);

    // Set settings
    void setFont(YZ::Font* font);
    void setCaption(const std::string &caption);
    void setColor(
        const Ogre::Real r,
        const Ogre::Real g,
        const Ogre::Real b,
        const Ogre::Real a);
    void setCharacterHeight(const Ogre::Real height);
    void setSpaceWidth(const Ogre::Real width);
    void setTextAlignment(
        const HorizontalAlignment& horizontalAlignment,
        const VerticalAlignment& verticalAlignment);
    void setGlobalTranslation(Ogre::Vector3 trans);
    void setLocalTranslation(Ogre::Vector3 trans);
    void showOnTop(bool show = true);

    // Get settings
    const std::string& getFontName() const {
        return mFontName;
    }
    const std::string& getCaption() const {
        return mCaption;
    }
    const Ogre::ColourValue& getColor() const {
        return mColor;
    }

    const Ogre::Real getCharacterHeight() const {
        return mCharHeight;
    }
    const Ogre::Real getSpaceWidth() const {
        return mSpaceWidth;
    }
    Ogre::Vector3 getGlobalTranslation() const {
        return mGlobalTranslation;
    }
    Ogre::Vector3 getLocalTranslation() const {
        return mLocalTranslation;
    }
    bool getShowOnTop() const {
        return mOnTop;
    }
    Ogre::AxisAlignedBox GetAABB() {
        return mAABB;
    }

    /******************************** protected methods and overload **************/
protected:

    // from MovableText, create the object
    void _setupGeometry();
    void _updateColors();

    // from MovableObject
    void getWorldTransforms(Ogre::Matrix4 *xform) const;
    Ogre::Real getBoundingRadius() const {
        return mRadius;
    }

    Ogre::Real getSquaredViewDepth(const Ogre::Camera *cam) const {
        return 0;
    }

    const Ogre::Quaternion& getWorldOrientation(void) const;
    const Ogre::Vector3& getWorldPosition(void) const;
    const Ogre::AxisAlignedBox& getBoundingBox(void) const {
        return mAABB;
    }

    const std::string& getName() const {
        return mName;
    }

    const std::string& getMovableType() const {
        static Ogre::String movType = "MovableText";
        return movType;
    }

    void _notifyCurrentCamera(Ogre::Camera *cam);
    void _updateRenderQueue(Ogre::RenderQueue* queue);

    // from renderable
    void getRenderOperation(Ogre::RenderOperation &op);
    const Ogre::MaterialPtr &getMaterial() const {
        assert(!mpMaterial.isNull());
        return mpMaterial;
    }

    const Ogre::LightList &getLights() const {
        return mLList;
    }

};

} //end namespace Ogre

#endif
