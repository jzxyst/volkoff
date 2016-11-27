// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once
#define MIGRATION 1

#define NOMINMAX
#include "targetver.h"
#include <winsock2.h>
#include <LuminoEngine.h>
using namespace ln;

#include "LuminoFoundation/LFramework.h"
#include "LuminoFoundation/LGameScene.h"
#include "LuminoFoundation/Accessor.h"
using namespace LNote;

#define NEW					LN_NEW
#define SAFE_DELETE			LN_SAFE_DELETE
#define SAFE_DELETE_ARRAY	LN_SAFE_DELETE_ARRAY
#define nil					nullptr
#define LN_ASSERT_S(r, ...)	LN_THROW(r, InvalidOperationException, __VA_ARGS__);

typedef uint8_t		u8;
typedef int32_t		s32;
typedef uint32_t	u32;
typedef uint32_t	lnU32;

typedef ln::Vector2			LVector2;
typedef ln::Vector3			LVector3;
typedef ln::Matrix			LMatrix;
typedef ln::PointI			LPoint;
typedef ln::Rect			LRect;
typedef ln::Sprite2DPtr		LSprite;
typedef ln::Sprite3DPtr		LPanel;
typedef ln::Sprite3DPtr		LBatchPanel;
typedef ln::Texture2DPtr	LTexture;
typedef ln::FontPtr			LFont;

#define LN_BUTTON_UP	InputButtons::Up
#define LN_BUTTON_DOWN	InputButtons::Down
#define LN_BUTTON_LEFT	InputButtons::Left
#define LN_BUTTON_RIGHT	InputButtons::Right
#define LN_BUTTON_A		InputButtons::Ok
#define LN_BUTTON_B		InputButtons::Cancel
#define LN_BUTTON_C		_T("Guard")
#define LN_BUTTON_X		_T("Action")

#pragma warning(disable : 4996)
#pragma warning(disable : 4477)

