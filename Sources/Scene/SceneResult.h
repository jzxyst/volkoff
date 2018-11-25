//=============================================================================
//【 SceneResult 】
//-----------------------------------------------------------------------------
///**
//  @file       SceneResult.h
//  @brief      SceneResult
//  @author     yama
//*/
//=============================================================================

#pragma once

#include "../Frontend/rapidnumber.h"
#include "../Frontend/RankingNameplate.h"

class SceneResult;

/// Main.cpp のイベントリスナーから onKeyEvent() を呼び出すために用意。SceneResult が存在していなければ NULL。もう美しさとかいいよね…
extern SceneResult* gSceneResult;

//=============================================================================
// ■ SceneResult クラス
//-----------------------------------------------------------------------------
///**
//  @brief		リザルト画面
//*/
//=============================================================================
class SceneResult : public LGameScene
{
public:

    /// コンストラクタ (プレイヤーが最後に装備していた武器番号を渡す)
    SceneResult( int weapon_no_ )
        : mWeaponNo ( weapon_no_ )
    {
		memset( mRankingName, 0, sizeof(mRankingName) );
	}

public:

    /// シーン名
    virtual const char* getSceneName() { return "SceneResult"; }

	/// 開始処理
	virtual void onStart();

    /// フレーム更新
	virtual void onUpdate();

    /// 終了処理
	virtual void onTerminate();

	/// Main.cpp のイベントリスナーから呼ばれる
	void onkeyEvent( char code_ );

private:

	static const int MAX_RANKING_NAME_LEN = 10;

	int			mScore;
	int			mTime;		// (スコア値)
	int			mRank;		// (スコア値)
	int			mTotalScore;
    int         mWeaponNo;
    int         mPhase;
    int         mFrameCount;

	RapidNumber<int>	mScoreRapid;
	RapidNumber<int>	mTimeRapid;
	RapidNumber<int>	mRankRapid;
	RapidNumber<int>	mTotalRapid;

    ln::Ref<ln::UISprite>     mCharacterSprite;
    ln::Ref<ln::UISprite>     mWeaponSprite;

	LTexture	mResultTexture;
    ln::Ref<ln::UISprite>		mScoreLineSprites[3];
    ln::Ref<ln::UISprite>		mTotalLineSprite;
    ln::Ref<ln::UISprite>		mTimeSprite[6];
    ln::Ref<ln::UISprite>		mRankSprite;
    ln::Ref<ln::UISprite>		mScoreNumberSprites[10];
    ln::Ref<ln::UISprite>		mTimeNumberSprites[10];
    ln::Ref<ln::UISprite>		mRankNumberSprites[10];
    ln::Ref<ln::UISprite>		mTotalNumberSprites[10];
    ln::Ref<ln::UISprite>		mRankingFrameSprite;

	FloatAnimationCurve	mCommandFadeInX;
	FloatAnimationCurve	mCommandFadeInOpacity;

	bool								mIsNewRecord;
	int									mRankingNo;
    ln::Ref<ln::UISprite>								mNewRecordSprite;
#if MIGRATION
#else
	Core::Animation::RoundTripValue<float>	mNewRecordOpacity;
	Core::Animation::FadeValue<float>			mNameplateOpacity;
#endif
    ln::Ref<ln::UISprite>								mNewRecordBGSprite;

    ln::Ref<ln::UISprite>		mMessageSprite;
#if MIGRATION
#else
	RankingNameplate	mRankingNameplate;
#endif

	lnChar	mRankingName[MAX_RANKING_NAME_LEN + 1];

	static const int LINE_MARGIN_X = 36;
	static const int LINE_MARGIN_Y = 82;

};

//=============================================================================
//								end of file
//=============================================================================