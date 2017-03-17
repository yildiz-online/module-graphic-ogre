/**
 * File: MovableText.cpp
 *
 * description: This create create a billboarding object that display a text.
 *
 * @author	2003 by cTh see gavocanov@rambler.ru
 * @update	2006 by barraq see nospam@barraquand.com
 * @update	2012 to work with newer versions of OGRE by MindCalamity <mindcalamity@gmail.com>
 *	- See "Notes" on: http://www.ogre3d.org/tikiwiki/tiki-editpage.php?page=MovableText
 */

#include "../includes/MovableText.hpp"

#define POS_TEX_BINDING    0
#define COLOUR_BINDING     1

yz::MovableText::MovableText(
		const std::string& name,
		const std::string& caption,
		 yz::Font* font,
		const Ogre::Real charHeight,
		const Ogre::ColourValue &color) :
		mpCam(NULL),
		mpWin(NULL),
		mpFont(NULL),
		mName(name),
		mCaption(caption),
		mFontName(font->getName()),
		mCharHeight(charHeight),
		mColor(color),
		mType("MovableText"),
		mTimeUntilNextToggle(0),
		mSpaceWidth(0),
		mUpdateColors(true),
		mOnTop(false),
		mHorizontalAlignment(H_LEFT),
		mVerticalAlignment(V_BELOW),
		mGlobalTranslation(0.0),
		mLocalTranslation(0.0),
		mNeedUpdate(false),
		mRadius(0) {
    LOG_FUNCTION
	assert(name != "" && "Trying to create MovableText without name");
	assert(caption != "" && "Trying to create MovableText without caption");

	this->mRenderOp.vertexData = NULL;
	this->setFont(font);
	this->_setupGeometry();
}

yz::MovableText::~MovableText() {
    LOG_FUNCTION
	if (this->mRenderOp.vertexData)
		delete this->mRenderOp.vertexData;
}

void yz::MovableText::setFont(yz::Font* font) {
    LOG_FUNCTION
	std::string materialName = this->mName + "Material";
	if ((Ogre::MaterialManager::getSingletonPtr()->resourceExists(materialName))) {
		Ogre::MaterialManager::getSingleton().remove(materialName);
	}

	if (this->mFontName != font->getName() || mpMaterial.isNull() || !mpFont) {
		mFontName = font->getName();

		mpFont = font;
		if (!mpFont)
			throw Ogre::Exception(Ogre::Exception::ERR_ITEM_NOT_FOUND,
					"Could not find font " + font->getName(),
					"MovableText::setFontName");

		mpFont->load();
		if (!mpMaterial.isNull()) {
			Ogre::MaterialManager::getSingletonPtr()->remove(
					mpMaterial->getName());
			mpMaterial.setNull();
		}

		mpMaterial = mpFont->getMaterial()->clone(materialName);
		if (!mpMaterial->isLoaded())
			mpMaterial->load();

		mpMaterial->setDepthCheckEnabled(!mOnTop);
		mpMaterial->setDepthBias(1.0, 1.0);
		mpMaterial->setDepthWriteEnabled(mOnTop);
		mpMaterial->setLightingEnabled(false);
		mNeedUpdate = true;
	}
}

void yz::MovableText::setCaption(const std::string &caption) {
    LOG_FUNCTION
	if (caption != mCaption) {
		mCaption = caption;
		mNeedUpdate = true;
	}
}

void yz::MovableText::setColor(const Ogre::Real r, const Ogre::Real g,
		const Ogre::Real b, const Ogre::Real a) {
    LOG_FUNCTION
	const Ogre::ColourValue color(r, g, b, a);
	if (color != mColor) {
		mColor = color;
		mUpdateColors = true;
	}
}

void yz::MovableText::setCharacterHeight(const Ogre::Real height) {
    LOG_FUNCTION
    Ogre::Real r = height - mCharHeight;
	if (r > 0.001F || r < - 0.001F) {
		mCharHeight = height;
		mNeedUpdate = true;
	}
}

void yz::MovableText::setSpaceWidth(const Ogre::Real width) {
    LOG_FUNCTION
    Ogre::Real r = width - mSpaceWidth;
	if (r > 0.001F || r < - 0.001F) {
		mSpaceWidth = width;
		mNeedUpdate = true;
	}
}

void yz::MovableText::setTextAlignment(
		const HorizontalAlignment& horizontalAlignment,
		const VerticalAlignment& verticalAlignment) {
    LOG_FUNCTION
	if (mHorizontalAlignment != horizontalAlignment) {
		mHorizontalAlignment = horizontalAlignment;
		mNeedUpdate = true;
	}
	if (mVerticalAlignment != verticalAlignment) {
		mVerticalAlignment = verticalAlignment;
		mNeedUpdate = true;
	}
}

void yz::MovableText::setGlobalTranslation(Ogre::Vector3 trans) {
    LOG_FUNCTION
	mGlobalTranslation = trans;
}

void yz::MovableText::setLocalTranslation(Ogre::Vector3 trans) {
	mLocalTranslation = trans;
}

void yz::MovableText::showOnTop(bool show) {
	if (mOnTop != show && !mpMaterial.isNull()) {
		mOnTop = show;
		mpMaterial->setDepthBias(1.0, 1.0);
		mpMaterial->setDepthCheckEnabled(!mOnTop);
		mpMaterial->setDepthWriteEnabled(mOnTop);
	}
}

void yz::MovableText::_setupGeometry() {
	assert(mpFont);
	assert(!mpMaterial.isNull());

	unsigned int vertexCount = static_cast<unsigned int>(mCaption.size() * 6);

	if (mRenderOp.vertexData) {
		// Removed this test as it causes problems when replacing a caption
		// of the same size: replacing "Hello" with "hello"
		// as well as when changing the text alignment
		//if (mRenderOp.vertexData->vertexCount != vertexCount)
		{
			delete mRenderOp.vertexData;
			mRenderOp.vertexData = NULL;
			mUpdateColors = true;
		}
	}

	if (!mRenderOp.vertexData)
		mRenderOp.vertexData = new Ogre::VertexData();

	mRenderOp.indexData = 0;
	mRenderOp.vertexData->vertexStart = 0;
	mRenderOp.vertexData->vertexCount = vertexCount;
	mRenderOp.operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST;
	mRenderOp.useIndexes = false;

	Ogre::VertexDeclaration *decl = mRenderOp.vertexData->vertexDeclaration;
	Ogre::VertexBufferBinding *bind = mRenderOp.vertexData->vertexBufferBinding;
	size_t offset = 0;

	// create/bind positions/tex.ccord. buffer
	if (!decl->findElementBySemantic(Ogre::VES_POSITION)) {
		decl->addElement(POS_TEX_BINDING, offset, Ogre::VET_FLOAT3,
				Ogre::VES_POSITION);
	}

	offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);

	if (!decl->findElementBySemantic(Ogre::VES_TEXTURE_COORDINATES)) {
		decl->addElement(POS_TEX_BINDING, offset, Ogre::VET_FLOAT2,
				Ogre::VES_TEXTURE_COORDINATES, 0);
	}

	Ogre::HardwareVertexBufferSharedPtr ptbuf =
			Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
					decl->getVertexSize(POS_TEX_BINDING),
					mRenderOp.vertexData->vertexCount,
					Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY);
	bind->setBinding(POS_TEX_BINDING, ptbuf);

	// Colours - store these in a separate buffer because they change less often
	if (!decl->findElementBySemantic(Ogre::VES_DIFFUSE)) {
		decl->addElement(COLOUR_BINDING, 0, Ogre::VET_COLOUR,
				Ogre::VES_DIFFUSE);
	}

	Ogre::HardwareVertexBufferSharedPtr cbuf =
			Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
					decl->getVertexSize(COLOUR_BINDING),
					mRenderOp.vertexData->vertexCount,
					Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY);
	bind->setBinding(COLOUR_BINDING, cbuf);

	size_t charlen = mCaption.size();
	float *pPCBuff = static_cast<float*>(ptbuf->lock(
			Ogre::HardwareBuffer::HBL_DISCARD));

	float largestWidth = 0;
	float left = 0 * 2.0 - 1.0;
	float top = -((0 * 2.0) - 1.0);

	float spaceWidth = mSpaceWidth;
	// Derive space width from a capital A
	if (spaceWidth < 0.001F)
		spaceWidth = mpFont->getGlyphAspectRatio('A') * mCharHeight * 2.0;

	// for calculation of AABB
	Ogre::Vector3 min, max, currPos;
	Ogre::Real maxSquaredRadius;
	bool first = true;

	// Use iterator
	std::string::iterator i, iend;
	iend = mCaption.end();
	bool newLine = true;
	Ogre::Real len = 0.0F;

	Ogre::Real verticalOffset = 0;
	switch (mVerticalAlignment) {
	case MovableText::V_ABOVE:
		verticalOffset = mCharHeight;
		break;
	case MovableText::V_CENTER:
		verticalOffset = 0.5 * mCharHeight;
		break;
	case MovableText::V_BELOW:
		verticalOffset = 0;
		break;
	}
	// Raise the first line of the caption
	top += verticalOffset;
	for (i = mCaption.begin(); i != iend; ++i) {
		if (*i == '\n')
			top += verticalOffset * 2.0;
	}

	for (i = mCaption.begin(); i != iend; ++i) {
		if (newLine) {
			len = 0.0f;
			for (std::string::iterator j = i; j != iend && *j != '\n'; ++j) {
				if (*j == ' ')
					len += spaceWidth;
				else
					len += mpFont->getGlyphAspectRatio((unsigned char) *j)
							* mCharHeight * 2.0;
			}
			newLine = false;
		}

		if (*i == '\n') {
			left = 0 * 2.0 - 1.0;
			top -= mCharHeight * 2.0;
			newLine = true;
			continue;
		}

		if (*i == ' ') {
			// Just leave a gap, no tris
			left += spaceWidth;
			// Also reduce tri count
			mRenderOp.vertexData->vertexCount -= 6;
			continue;
		}

		Ogre::Real horiz_height = mpFont->getGlyphAspectRatio(
				(unsigned char) *i);
		Ogre::Real u1, u2, v1, v2;
		Ogre::Font::UVRect utmp;
		utmp = mpFont->getGlyphTexCoords((unsigned char) *i);
		u1 = utmp.left;
		u2 = utmp.right;
		v1 = utmp.top;
		v2 = utmp.bottom;

		// each vert is (x, y, z, u, v)
		//-------------------------------------------------------------------------------------
		// First tri
		//
		// Upper left
		if (mHorizontalAlignment == MovableText::H_LEFT)
			*pPCBuff++ = left;
		else
			*pPCBuff++ = left - (len / 2);
		*pPCBuff++ = top;
		*pPCBuff++ = -1.0;
		*pPCBuff++ = u1;
		*pPCBuff++ = v1;

		// Deal with bounds
		if (mHorizontalAlignment == MovableText::H_LEFT) {
			currPos = Ogre::Vector3(left, top, -1.0);
		} else {
			currPos = Ogre::Vector3(left - (len / 2), top, -1.0);
		}
		if (first) {
			min = max = currPos;
			maxSquaredRadius = currPos.squaredLength();
			first = false;
		} else {
			min.makeFloor(currPos);
			max.makeCeil(currPos);
			maxSquaredRadius = std::max(maxSquaredRadius,
					currPos.squaredLength());
		}

		top -= mCharHeight * 2.0;

		// Bottom left
		if (mHorizontalAlignment == MovableText::H_LEFT)
			*pPCBuff++ = left;
		else
			*pPCBuff++ = left - (len / 2);
		*pPCBuff++ = top;
		*pPCBuff++ = -1.0;
		*pPCBuff++ = u1;
		*pPCBuff++ = v2;

		// Deal with bounds
		if (mHorizontalAlignment == MovableText::H_LEFT)
			currPos = Ogre::Vector3(left, top, -1.0);
		else
			currPos = Ogre::Vector3(left - (len / 2), top, -1.0);
		min.makeFloor(currPos);
		max.makeCeil(currPos);
		maxSquaredRadius = std::max(maxSquaredRadius, currPos.squaredLength());

		top += mCharHeight * 2.0;
		left += horiz_height * mCharHeight * 2.0;

		// Top right
		if (mHorizontalAlignment == MovableText::H_LEFT)
			*pPCBuff++ = left;
		else
			*pPCBuff++ = left - (len / 2);
		*pPCBuff++ = top;
		*pPCBuff++ = -1.0;
		*pPCBuff++ = u2;
		*pPCBuff++ = v1;
		//-------------------------------------------------------------------------------------

		// Deal with bounds
		if (mHorizontalAlignment == MovableText::H_LEFT) {
			currPos = Ogre::Vector3(left, top, -1.0);
		} else {
			currPos = Ogre::Vector3(left - (len / 2), top, -1.0);
		}
		min.makeFloor(currPos);
		max.makeCeil(currPos);
		maxSquaredRadius = std::max(maxSquaredRadius, currPos.squaredLength());

		//-------------------------------------------------------------------------------------
		// Second tri
		//
		// Top right (again)
		if (mHorizontalAlignment == MovableText::H_LEFT) {
			*pPCBuff++ = left;
		} else {
			*pPCBuff++ = left - (len / 2);
		}
		*pPCBuff++ = top;
		*pPCBuff++ = -1.0;
		*pPCBuff++ = u2;
		*pPCBuff++ = v1;

		currPos = Ogre::Vector3(left, top, -1.0);
		min.makeFloor(currPos);
		max.makeCeil(currPos);
		maxSquaredRadius = std::max(maxSquaredRadius, currPos.squaredLength());

		top -= mCharHeight * 2.0;
		left -= horiz_height * mCharHeight * 2.0;

		// Bottom left (again)
		if (mHorizontalAlignment == MovableText::H_LEFT)
			*pPCBuff++ = left;
		else
			*pPCBuff++ = left - (len / 2);
		*pPCBuff++ = top;
		*pPCBuff++ = -1.0;
		*pPCBuff++ = u1;
		*pPCBuff++ = v2;

		currPos = Ogre::Vector3(left, top, -1.0);
		min.makeFloor(currPos);
		max.makeCeil(currPos);
		maxSquaredRadius = std::max(maxSquaredRadius, currPos.squaredLength());

		left += horiz_height * mCharHeight * 2.0;

		// Bottom right
		if (mHorizontalAlignment == MovableText::H_LEFT)
			*pPCBuff++ = left;
		else
			*pPCBuff++ = left - (len / 2);
		*pPCBuff++ = top;
		*pPCBuff++ = -1.0;
		*pPCBuff++ = u2;
		*pPCBuff++ = v2;
		//-------------------------------------------------------------------------------------

		currPos = Ogre::Vector3(left, top, -1.0);
		min.makeFloor(currPos);
		max.makeCeil(currPos);
		maxSquaredRadius = std::max(maxSquaredRadius, currPos.squaredLength());

		// Go back up with top
		top += mCharHeight * 2.0;

		float currentWidth = (left + 1) / 2 - 0;
		if (currentWidth > largestWidth)
			largestWidth = currentWidth;
	}

	// Unlock vertex buffer
	ptbuf->unlock();

	// update AABB/Sphere radius
	mAABB = Ogre::AxisAlignedBox(min, max);
	mRadius = Ogre::Math::Sqrt(maxSquaredRadius);

	if (mUpdateColors)
		this->_updateColors();

	mNeedUpdate = false;
}

void yz::MovableText::_updateColors() {
	assert(mpFont);
	assert(!mpMaterial.isNull());

	// Convert to system-specific
	Ogre::RGBA color;
	Ogre::Root::getSingleton().convertColourValue(mColor, &color);
	Ogre::HardwareVertexBufferSharedPtr vbuf =
			mRenderOp.vertexData->vertexBufferBinding->getBuffer(
			COLOUR_BINDING);
	Ogre::RGBA *pDest = static_cast<Ogre::RGBA*>(vbuf->lock(
			Ogre::HardwareBuffer::HBL_DISCARD));
	for (int i = 0; i < (int) mRenderOp.vertexData->vertexCount; ++i) {
		*pDest++ = color;
	}
	vbuf->unlock();
	mUpdateColors = false;
}

const Ogre::Quaternion& yz::MovableText::getWorldOrientation() const {
	assert(mpCam);
	return const_cast<Ogre::Quaternion&>(mpCam->getDerivedOrientation());
}

// Add to build on Shoggoth:
void yz::MovableText::visitRenderables(Ogre::Renderable::Visitor* visitor,
		bool debugRenderables) {
}

const Ogre::Vector3& yz::MovableText::getWorldPosition() const {
	assert (mParentNode);
	return mParentNode->_getDerivedPosition();
}

void yz::MovableText::getWorldTransforms(Ogre::Matrix4 *xform) const {
	if (this->isVisible() && mpCam) {
		Ogre::Matrix3 rot3x3, scale3x3 = Ogre::Matrix3::IDENTITY;

		// store rotation in a matrix
		mpCam->getDerivedOrientation().ToRotationMatrix(rot3x3);

		// parent node position
		Ogre::Vector3 ppos = mParentNode->_getDerivedPosition()
				+ Ogre::Vector3::UNIT_Y * mGlobalTranslation;
		ppos += rot3x3 * mLocalTranslation;

		// apply scale
		scale3x3[0][0] = mParentNode->_getDerivedScale().x / 2;
		scale3x3[1][1] = mParentNode->_getDerivedScale().y / 2;
		scale3x3[2][2] = mParentNode->_getDerivedScale().z / 2;

		// apply all transforms to xform
		*xform = (rot3x3 * scale3x3);
		xform->setTrans(ppos);
	}
}

void yz::MovableText::getRenderOperation(Ogre::RenderOperation &op) {
	if (this->isVisible()) {
		if (mNeedUpdate)
			this->_setupGeometry();
		if (mUpdateColors)
			this->_updateColors();
		op = mRenderOp;
	}
}

void yz::MovableText::_notifyCurrentCamera(Ogre::Camera *cam) {
	this->mpCam = cam;
}

void yz::MovableText::_updateRenderQueue(Ogre::RenderQueue* queue) {
	if (this->isVisible()) {
		if (mNeedUpdate)
			this->_setupGeometry();
		if (mUpdateColors)
			this->_updateColors();

		queue->addRenderable(this, mRenderQueueID,
				OGRE_RENDERABLE_DEFAULT_PRIORITY);
		//queue->addRenderable(this, mRenderQueueID, RENDER_QUEUE_SKIES_LATE);
	}
}
