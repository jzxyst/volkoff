//=============================================================================
//【 SceneStartup 】
//-----------------------------------------------------------------------------
///**
//  @file       SceneStartup.h
//  @brief      SceneStartup
//  @author     yama
//  @par
//              起動後、一番最初に実行されるシーン。
//              前まで SceneLogo とか名前がついてたもの。
//*/
//=============================================================================

#pragma once

//=============================================================================
// ■ SceneStartup クラス
//-----------------------------------------------------------------------------
///**
//  @brief		起動後、一番最初に実行されるシーン
//*/
//=============================================================================
class SceneStartup : public LGameScene
{
public:

    /// シーン名
    virtual const TCHAR* getSceneName() { return _T("SceneStartup"); }

	/// 開始処理
	virtual void onStart();

    /// フレーム更新
	virtual void onUpdate();

    /// 終了処理
	virtual void onTerminate();

private:
	ln::Ref<ln::UISprite> mLogoSprite;
    ln::Ref<ln::UISprite> mFlashSprite;
    ln::Ref<ln::UISprite> mTitleSubTextSprite;
	EasingValue<float>	mFlashScale;
	int         mStep;
	int         mFrameCount;
};

//=============================================================================
//								end of file
//=============================================================================