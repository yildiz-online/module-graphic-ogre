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

#ifndef ENUM_CONVERSION
#define ENUM_CONVERSION

#include "stdafx.h"
#include <Ogre.h>
#include <OgreGpuProgram.h>
#include <OgreGpuProgramParams.h>

/**
*@author Grégory Van den Borre
*/
class EnumConversion {

public:
	static Ogre::LayerBlendOperationEx getLayerBlendOperationEx(
			const int value) {
		switch (value) {
		case 0:
			return Ogre::LBX_SOURCE1;
		case 1:
			return Ogre::LBX_SOURCE2;
		case 2:
			return Ogre::LBX_MODULATE;
		case 3:
			return Ogre::LBX_MODULATE_X2;
		case 4:
			return Ogre::LBX_MODULATE_X4;
		case 5:
			return Ogre::LBX_ADD;
		case 6:
			return Ogre::LBX_ADD_SIGNED;
		case 7:
			return Ogre::LBX_ADD_SMOOTH;
		case 8:
			return Ogre::LBX_SUBTRACT;
		case 9:
			return Ogre::LBX_BLEND_DIFFUSE_ALPHA;
		case 10:
			return Ogre::LBX_BLEND_TEXTURE_ALPHA;
		case 11:
			return Ogre::LBX_BLEND_CURRENT_ALPHA;
		case 12:
			return Ogre::LBX_BLEND_MANUAL;
		case 13:
			return Ogre::LBX_DOTPRODUCT;
		case 14:
			return Ogre::LBX_BLEND_DIFFUSE_COLOUR;
		}
	}

	static Ogre::TextureFilterOptions getTextureFilter(const int value) {
		switch (value) {
		case 0:
			return Ogre::TFO_ANISOTROPIC;
		case 1:
			return Ogre::TFO_BILINEAR;
		case 2:
			return Ogre::TFO_NONE;
		case 3:
			return Ogre::TFO_TRILINEAR;
		default:
			return Ogre::TFO_NONE;
		}
	}

	static Ogre::LayerBlendSource getLayerBlendSource(const int value) {
		switch (value) {
		case 0:
			return Ogre::LBS_CURRENT;
		case 1:
			return Ogre::LBS_TEXTURE;
		case 2:
			return Ogre::LBS_DIFFUSE;
		case 3:
			return Ogre::LBS_SPECULAR;
		case 4:
			return Ogre::LBS_MANUAL;
		}
	}
    
    static Ogre::GpuProgramType getGpuProgramType(const int value) {
        switch(value) {
        case 0: return Ogre::GPT_FRAGMENT_PROGRAM;
        case 1: return Ogre::GPT_VERTEX_PROGRAM;
        case 2: return Ogre::GPT_GEOMETRY_PROGRAM;
        }
    }

	static Ogre::SceneBlendFactor getSceneBlendFactor(const int value) {
		switch (value) {
		case 0:
			return Ogre::SBF_ZERO;
		case 1:
			return Ogre::SBF_ONE;
		case 2:
			return Ogre::SBF_DEST_COLOUR;
		case 3:
			return Ogre::SBF_SOURCE_COLOUR;
		case 4:
			return Ogre::SBF_ONE_MINUS_DEST_COLOUR;
		case 5:
			return Ogre::SBF_ONE_MINUS_SOURCE_COLOUR;
		case 6:
			return Ogre::SBF_DEST_ALPHA;
		case 7:
			return Ogre::SBF_SOURCE_ALPHA;
		case 8:
			return Ogre::SBF_ONE_MINUS_DEST_ALPHA;
		case 9:
			return Ogre::SBF_ONE_MINUS_SOURCE_ALPHA;
		}
	}

	static Ogre::ShadowTechnique getShadowTechnique(const int value) {
		switch (value) {
		case 0:
			return Ogre::SHADOWTYPE_NONE;
		case 1:
			return Ogre::SHADOWTYPE_TEXTURE_ADDITIVE;
		case 2:
			return Ogre::SHADOWTYPE_TEXTURE_MODULATIVE;
		case 3:
			return Ogre::SHADOWTYPE_STENCIL_ADDITIVE;
		case 4:
			return Ogre::SHADOWTYPE_STENCIL_MODULATIVE;
		default:
			return Ogre::SHADOWTYPE_NONE;
		}
	}

	static Ogre::BillboardOrigin getBillboardOrigin(const int value) {
		switch (value) {
		case 0:
			return Ogre::BBO_BOTTOM_CENTER;
		case 1:
			return Ogre::BBO_BOTTOM_LEFT;
		case 2:
			return Ogre::BBO_BOTTOM_RIGHT;
		case 3:
			return Ogre::BBO_CENTER;
		case 4:
			return Ogre::BBO_CENTER_LEFT;
		case 5:
			return Ogre::BBO_CENTER_RIGHT;
		case 6:
			return Ogre::BBO_TOP_CENTER;
		case 7:
			return Ogre::BBO_TOP_LEFT;
		case 8:
			return Ogre::BBO_TOP_RIGHT;
		default:
			return Ogre::BBO_CENTER;
		}
	}

	static Ogre::SceneBlendOperation getSceneBlendOperation(const int value) {
		switch (value) {
		case 0:
			return Ogre::SBO_ADD;
		case 1:
			return Ogre::SBO_SUBTRACT;
		case 2:
			return Ogre::SBO_REVERSE_SUBTRACT;
		case 3:
			return Ogre::SBO_MIN;
		case 4:
			return Ogre::SBO_MAX;
		}
	}

	static Ogre::LayerBlendOperation getLayerBlendOperation(const int value) {
		switch (value) {
		case 0:
			return Ogre::LBO_REPLACE;
		case 1:
			return Ogre::LBO_ADD;
		case 2:
			return Ogre::LBO_MODULATE;
		case 3:
			return Ogre::LBO_ALPHA_BLEND;
		}
	}

	static Ogre::BillboardType getBillboardType(const int value) {
		switch (value) {
		case 0:
			return Ogre::BBT_POINT;
		case 1:
			return Ogre::BBT_ORIENTED_COMMON;
		case 2:
			return Ogre::BBT_ORIENTED_SELF;
		case 3:
			return Ogre::BBT_PERPENDICULAR_COMMON;
		case 4:
			return Ogre::BBT_PERPENDICULAR_SELF;
		}
	}

	static Ogre::GpuProgramParameters::AutoConstantType getGpuProgramParameterAuto(
			const int value) {
		switch (value) {
		case 0:
			return Ogre::GpuProgramParameters::ACT_WORLD_MATRIX;
		case 1:
			return Ogre::GpuProgramParameters::ACT_INVERSE_WORLD_MATRIX;
		case 2:
			return Ogre::GpuProgramParameters::ACT_TRANSPOSE_WORLD_MATRIX;
		case 3:
			return Ogre::GpuProgramParameters::ACT_INVERSE_TRANSPOSE_WORLD_MATRIX;
		case 4:
			return Ogre::GpuProgramParameters::ACT_WORLD_MATRIX_ARRAY_3x4;
		case 5:
			return Ogre::GpuProgramParameters::ACT_WORLD_MATRIX_ARRAY;
		case 6:
			return Ogre::GpuProgramParameters::ACT_WORLD_DUALQUATERNION_ARRAY_2x4;
		case 7:
			return Ogre::GpuProgramParameters::ACT_WORLD_SCALE_SHEAR_MATRIX_ARRAY_3x4;
		case 8:
			return Ogre::GpuProgramParameters::ACT_VIEW_MATRIX;
		case 9:
			return Ogre::GpuProgramParameters::ACT_INVERSE_VIEW_MATRIX;
		case 10:
			return Ogre::GpuProgramParameters::ACT_TRANSPOSE_VIEW_MATRIX;
		case 11:
			return Ogre::GpuProgramParameters::ACT_INVERSE_TRANSPOSE_VIEW_MATRIX;
		case 12:
			return Ogre::GpuProgramParameters::ACT_PROJECTION_MATRIX;
		case 13:
			return Ogre::GpuProgramParameters::ACT_INVERSE_PROJECTION_MATRIX;
		case 14:
			return Ogre::GpuProgramParameters::ACT_TRANSPOSE_PROJECTION_MATRIX;
		case 15:
			return Ogre::GpuProgramParameters::ACT_INVERSE_TRANSPOSE_PROJECTION_MATRIX;
		case 16:
			return Ogre::GpuProgramParameters::ACT_VIEWPROJ_MATRIX;
		case 17:
			return Ogre::GpuProgramParameters::ACT_INVERSE_VIEWPROJ_MATRIX;
		case 18:
			return Ogre::GpuProgramParameters::ACT_TRANSPOSE_VIEWPROJ_MATRIX;
		case 19:
			return Ogre::GpuProgramParameters::ACT_INVERSE_TRANSPOSE_VIEWPROJ_MATRIX;
		case 20:
			return Ogre::GpuProgramParameters::ACT_WORLDVIEW_MATRIX;
		case 21:
			return Ogre::GpuProgramParameters::ACT_INVERSE_WORLDVIEW_MATRIX;
		case 22:
			return Ogre::GpuProgramParameters::ACT_TRANSPOSE_WORLDVIEW_MATRIX;
		case 23:
			return Ogre::GpuProgramParameters::ACT_INVERSE_TRANSPOSE_WORLDVIEW_MATRIX;
		case 24:
			return Ogre::GpuProgramParameters::ACT_WORLDVIEWPROJ_MATRIX;
		case 25:
			return Ogre::GpuProgramParameters::ACT_INVERSE_WORLDVIEWPROJ_MATRIX;
		case 26:
			return Ogre::GpuProgramParameters::ACT_TRANSPOSE_WORLDVIEWPROJ_MATRIX;
		case 27:
			return Ogre::GpuProgramParameters::ACT_INVERSE_TRANSPOSE_WORLDVIEWPROJ_MATRIX;
		case 28:
			return Ogre::GpuProgramParameters::ACT_RENDER_TARGET_FLIPPING;
		case 29:
			return Ogre::GpuProgramParameters::ACT_VERTEX_WINDING;
		case 30:
			return Ogre::GpuProgramParameters::ACT_FOG_COLOUR;
		case 31:
			return Ogre::GpuProgramParameters::ACT_FOG_PARAMS;
		case 32:
			return Ogre::GpuProgramParameters::ACT_SURFACE_AMBIENT_COLOUR;
		case 33:
			return Ogre::GpuProgramParameters::ACT_SURFACE_DIFFUSE_COLOUR;
		case 34:
			return Ogre::GpuProgramParameters::ACT_SURFACE_SPECULAR_COLOUR;
		case 35:
			return Ogre::GpuProgramParameters::ACT_SURFACE_EMISSIVE_COLOUR;
		case 36:
			return Ogre::GpuProgramParameters::ACT_SURFACE_SHININESS;
		case 37:
			return Ogre::GpuProgramParameters::ACT_LIGHT_COUNT;
		case 38:
			return Ogre::GpuProgramParameters::ACT_AMBIENT_LIGHT_COLOUR;
		case 39:
			return Ogre::GpuProgramParameters::ACT_LIGHT_DIFFUSE_COLOUR;
		case 40:
			return Ogre::GpuProgramParameters::ACT_LIGHT_SPECULAR_COLOUR;
		case 41:
			return Ogre::GpuProgramParameters::ACT_LIGHT_ATTENUATION;
		case 42:
			return Ogre::GpuProgramParameters::ACT_SPOTLIGHT_PARAMS;
		case 43:
			return Ogre::GpuProgramParameters::ACT_LIGHT_POSITION;
		case 44:
			return Ogre::GpuProgramParameters::ACT_LIGHT_POSITION_OBJECT_SPACE;
		case 45:
			return Ogre::GpuProgramParameters::ACT_LIGHT_POSITION_VIEW_SPACE;
		case 46:
			return Ogre::GpuProgramParameters::ACT_LIGHT_DIRECTION;
		case 47:
			return Ogre::GpuProgramParameters::ACT_LIGHT_DIRECTION_OBJECT_SPACE;
		case 48:
			return Ogre::GpuProgramParameters::ACT_LIGHT_DIRECTION_VIEW_SPACE;
		case 49:
			return Ogre::GpuProgramParameters::ACT_LIGHT_DISTANCE_OBJECT_SPACE;
		case 50:
			return Ogre::GpuProgramParameters::ACT_LIGHT_POWER_SCALE;
		case 51:
			return Ogre::GpuProgramParameters::ACT_LIGHT_DIFFUSE_COLOUR_POWER_SCALED;
		case 52:
			return Ogre::GpuProgramParameters::ACT_LIGHT_SPECULAR_COLOUR_POWER_SCALED;
		case 53:
			return Ogre::GpuProgramParameters::ACT_LIGHT_DIFFUSE_COLOUR_ARRAY;
		case 54:
			return Ogre::GpuProgramParameters::ACT_LIGHT_SPECULAR_COLOUR_ARRAY;
		case 55:
			return Ogre::GpuProgramParameters::ACT_LIGHT_DIFFUSE_COLOUR_POWER_SCALED_ARRAY;
		case 56:
			return Ogre::GpuProgramParameters::ACT_LIGHT_SPECULAR_COLOUR_POWER_SCALED_ARRAY;
		case 57:
			return Ogre::GpuProgramParameters::ACT_LIGHT_ATTENUATION_ARRAY;
		case 58:
			return Ogre::GpuProgramParameters::ACT_LIGHT_POSITION_ARRAY;
		case 59:
			return Ogre::GpuProgramParameters::ACT_LIGHT_POSITION_OBJECT_SPACE_ARRAY;
		case 60:
			return Ogre::GpuProgramParameters::ACT_LIGHT_POSITION_VIEW_SPACE_ARRAY;
		case 61:
			return Ogre::GpuProgramParameters::ACT_LIGHT_DIRECTION_ARRAY;
		case 62:
			return Ogre::GpuProgramParameters::ACT_LIGHT_DIRECTION_OBJECT_SPACE_ARRAY;
		case 63:
			return Ogre::GpuProgramParameters::ACT_LIGHT_DIRECTION_VIEW_SPACE_ARRAY;
		case 64:
			return Ogre::GpuProgramParameters::ACT_LIGHT_DISTANCE_OBJECT_SPACE_ARRAY;
		case 65:
			return Ogre::GpuProgramParameters::ACT_LIGHT_POWER_SCALE_ARRAY;
		case 66:
			return Ogre::GpuProgramParameters::ACT_SPOTLIGHT_PARAMS_ARRAY;
		case 67:
			return Ogre::GpuProgramParameters::ACT_DERIVED_AMBIENT_LIGHT_COLOUR;
		case 68:
			return Ogre::GpuProgramParameters::ACT_DERIVED_SCENE_COLOUR;
		case 69:
			return Ogre::GpuProgramParameters::ACT_DERIVED_LIGHT_DIFFUSE_COLOUR;
		case 70:
			return Ogre::GpuProgramParameters::ACT_DERIVED_LIGHT_SPECULAR_COLOUR;
		case 71:
			return Ogre::GpuProgramParameters::ACT_DERIVED_LIGHT_DIFFUSE_COLOUR_ARRAY;
		case 72:
			return Ogre::GpuProgramParameters::ACT_DERIVED_LIGHT_SPECULAR_COLOUR_ARRAY;
		case 73:
			return Ogre::GpuProgramParameters::ACT_LIGHT_NUMBER;
		case 74:
			return Ogre::GpuProgramParameters::ACT_LIGHT_CASTS_SHADOWS;
		case 75:
			return Ogre::GpuProgramParameters::ACT_SHADOW_EXTRUSION_DISTANCE;
		case 76:
			return Ogre::GpuProgramParameters::ACT_CAMERA_POSITION;
		case 77:
			return Ogre::GpuProgramParameters::ACT_CAMERA_POSITION_OBJECT_SPACE;
		case 78:
			return Ogre::GpuProgramParameters::ACT_TEXTURE_VIEWPROJ_MATRIX;
		case 79:
			return Ogre::GpuProgramParameters::ACT_TEXTURE_VIEWPROJ_MATRIX_ARRAY;
		case 80:
			return Ogre::GpuProgramParameters::ACT_TEXTURE_WORLDVIEWPROJ_MATRIX;
		case 81:
			return Ogre::GpuProgramParameters::ACT_TEXTURE_WORLDVIEWPROJ_MATRIX_ARRAY;
		case 82:
			return Ogre::GpuProgramParameters::ACT_SPOTLIGHT_VIEWPROJ_MATRIX;
		case 83:
			return Ogre::GpuProgramParameters::ACT_SPOTLIGHT_VIEWPROJ_MATRIX_ARRAY;
		case 84:
			return Ogre::GpuProgramParameters::ACT_SPOTLIGHT_WORLDVIEWPROJ_MATRIX;
		case 85:
			return Ogre::GpuProgramParameters::ACT_CUSTOM;
		case 86:
			return Ogre::GpuProgramParameters::ACT_TIME;
		case 87:
			return Ogre::GpuProgramParameters::ACT_TIME_0_X;
		case 88:
			return Ogre::GpuProgramParameters::ACT_COSTIME_0_X;
		case 89:
			return Ogre::GpuProgramParameters::ACT_SINTIME_0_X;
		case 90:
			return Ogre::GpuProgramParameters::ACT_TANTIME_0_X;
		case 91:
			return Ogre::GpuProgramParameters::ACT_TIME_0_X_PACKED;
		case 92:
			return Ogre::GpuProgramParameters::ACT_TIME_0_1;
		case 93:
			return Ogre::GpuProgramParameters::ACT_COSTIME_0_1;
		case 94:
			return Ogre::GpuProgramParameters::ACT_SINTIME_0_1;
		case 95:
			return Ogre::GpuProgramParameters::ACT_TANTIME_0_1;
		case 96:
			return Ogre::GpuProgramParameters::ACT_TIME_0_1_PACKED;
		case 97:
			return Ogre::GpuProgramParameters::ACT_TIME_0_2PI;
		case 98:
			return Ogre::GpuProgramParameters::ACT_COSTIME_0_2PI;
		case 99:
			return Ogre::GpuProgramParameters::ACT_SINTIME_0_2PI;
		case 100:
			return Ogre::GpuProgramParameters::ACT_TANTIME_0_2PI;
		case 101:
			return Ogre::GpuProgramParameters::ACT_TIME_0_2PI_PACKED;
		case 102:
			return Ogre::GpuProgramParameters::ACT_FRAME_TIME;
		case 103:
			return Ogre::GpuProgramParameters::ACT_FPS;
		case 104:
			return Ogre::GpuProgramParameters::ACT_VIEWPORT_WIDTH;
		case 105:
			return Ogre::GpuProgramParameters::ACT_VIEWPORT_HEIGHT;
		case 106:
			return Ogre::GpuProgramParameters::ACT_INVERSE_VIEWPORT_WIDTH;
		case 107:
			return Ogre::GpuProgramParameters::ACT_INVERSE_VIEWPORT_HEIGHT;
		case 108:
			return Ogre::GpuProgramParameters::ACT_VIEWPORT_SIZE;
		case 109:
			return Ogre::GpuProgramParameters::ACT_VIEW_DIRECTION;
		case 110:
			return Ogre::GpuProgramParameters::ACT_VIEW_SIDE_VECTOR;
		case 111:
			return Ogre::GpuProgramParameters::ACT_VIEW_UP_VECTOR;
		case 112:
			return Ogre::GpuProgramParameters::ACT_FOV;
		case 113:
			return Ogre::GpuProgramParameters::ACT_NEAR_CLIP_DISTANCE;
		case 114:
			return Ogre::GpuProgramParameters::ACT_FAR_CLIP_DISTANCE;
		case 115:
			return Ogre::GpuProgramParameters::ACT_PASS_NUMBER;
		case 116:
			return Ogre::GpuProgramParameters::ACT_PASS_ITERATION_NUMBER;
		case 117:
			return Ogre::GpuProgramParameters::ACT_ANIMATION_PARAMETRIC;
		case 118:
			return Ogre::GpuProgramParameters::ACT_TEXEL_OFFSETS;
		case 119:
			return Ogre::GpuProgramParameters::ACT_SCENE_DEPTH_RANGE;
		case 120:
			return Ogre::GpuProgramParameters::ACT_SHADOW_SCENE_DEPTH_RANGE;
		case 121:
			return Ogre::GpuProgramParameters::ACT_SHADOW_COLOUR;
		case 122:
			return Ogre::GpuProgramParameters::ACT_TEXTURE_SIZE;
		case 123:
			return Ogre::GpuProgramParameters::ACT_INVERSE_TEXTURE_SIZE;
		case 124:
			return Ogre::GpuProgramParameters::ACT_PACKED_TEXTURE_SIZE;
		case 125:
			return Ogre::GpuProgramParameters::ACT_TEXTURE_MATRIX;
		case 126:
			return Ogre::GpuProgramParameters::ACT_LOD_CAMERA_POSITION;
		case 127:
			return Ogre::GpuProgramParameters::ACT_LOD_CAMERA_POSITION_OBJECT_SPACE;
		case 128:
			return Ogre::GpuProgramParameters::ACT_LIGHT_CUSTOM;
		default:
			return Ogre::GpuProgramParameters::ACT_CAMERA_POSITION;
		}
	}
};

#endif
