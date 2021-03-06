//=============================================================================
//【 SceneGameover 】
//-----------------------------------------------------------------------------
///**
//  @file       SceneGameover.h
//  @brief      SceneGameover
//  @author     yama
//*/
//=============================================================================

#pragma once
#include "../Utility/FormatText.h"

class PointCursor;

//=============================================================================
// ■ SceneGameover クラス
//-----------------------------------------------------------------------------
///**
//  @brief		ゲームオーバー画面
//*/
//=============================================================================
class SceneGameover
    : public LGameScene
{
public:

    /// シーン名
    virtual const char* getSceneName() { return "SceneGameover"; }

	/// 開始処理
	virtual void onStart();

    /// フレーム更新
	virtual void onUpdate();

    /// 終了処理
	virtual void onTerminate();

private:

    /// 選択している項目を変更した
    void _onSelectIndex();

private:

    ln::Ref<ln::UISprite>     mBlindSprite;
    ln::Ref<ln::UISprite>     mBlindSprite2;

    int         mStep;
    int         mFrameCount;
    int         mGotoScene;
    int         mSelectIndex;

	EasingValue<float>	mLogoFadeValue;
	EasingValue<float>	mFadeValue;

    ln::Ref<ln::UISprite>     mLogoSprite;

    ln::Ref<ln::UISprite>     mDescWindowSprite;      // 説明ウィンドウの枠
    ln::Ref<ln::UISprite>     mDescContentsSprite;
    LTexture    mDescContents;          // 説明ウィンドウの内容
    Ref<LFont>       mDescTitleFont;
    int         mWindowFadeCount;
    Utility::FormatText mFormatText;

    ln::Ref<ln::UISprite>     mCommandSprite[ 2 ];

    PointCursor*    mPointCursor;

};

//=============================================================================
//								end of file
//=============================================================================