

#pragma once
#define MIGRATION 1

#define NOMINMAX
#include "targetver.h"
#include <winsock2.h>
#include <tchar.h>

#define LN_MSVC_AUTO_LINK_LIBRARIES
#include <LuminoEngine.hpp>
using namespace ln;

#include "../../Sources/LuminoFoundation/LFramework.h"
#include "../../Sources/LuminoFoundation/LGameScene.h"
#include "../../Sources/LuminoFoundation/Accessor.h"
using namespace LNote;

#define NEW					LN_NEW
#define SAFE_DELETE			LN_SAFE_DELETE
#define SAFE_DELETE_ARRAY	LN_SAFE_DELETE_ARRAY
#define nil					nullptr
#define LN_ASSERT_S(r, ...)	LN_CHECK(r)

typedef uint8_t		u8;
typedef int32_t		s32;
typedef uint32_t	u32;
typedef uint32_t	lnU32;

typedef ln::Vector2			    LVector2;
typedef ln::Vector3			    LVector3;
typedef ln::Matrix			    LMatrix;
typedef ln::PointI			    LPoint;
typedef ln::Rect			    LRect;
typedef ln::UISprite		    LSprite;
typedef ln::Sprite		        LPanel;
typedef ln::Sprite		        LBatchPanel;
typedef ln::Ref<ln::Texture2D>	LTexture;
typedef ln::Font                LFont;

#define LN_BUTTON_UP	InputButtons::Up
#define LN_BUTTON_DOWN	InputButtons::Down
#define LN_BUTTON_LEFT	InputButtons::Left
#define LN_BUTTON_RIGHT	InputButtons::Right
#define LN_BUTTON_A		InputButtons::Submit
#define LN_BUTTON_B		InputButtons::Cancel
#define LN_BUTTON_C		_T("Guard")
#define LN_BUTTON_X		_T("Action")

#pragma warning(disable : 4996)
#pragma warning(disable : 4477)