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

    LSprite     mCharacterSprite;
    LSprite     mWeaponSprite;

	LTexture	mResultTexture;
	LSprite		mScoreLineSprites[3];
	LSprite		mTotalLineSprite;
	LSprite		mTimeSprite[6];
	LSprite		mRankSprite;
	LSprite		mScoreNumberSprites[10];
	LSprite		mTimeNumberSprites[10];
	LSprite		mRankNumberSprites[10];
	LSprite		mTotalNumberSprites[10];
	LSprite		mRankingFrameSprite;

	FloatAnimationCurve	mCommandFadeInX;
	FloatAnimationCurve	mCommandFadeInOpacity;

	bool								mIsNewRecord;
	int									mRankingNo;
	LSprite								mNewRecordSprite;
#if MIGRATION
#else
	Core::Animation::RoundTripValue<float>	mNewRecordOpacity;
	Core::Animation::FadeValue<float>			mNameplateOpacity;
#endif
	LSprite								mNewRecordBGSprite;

	LSprite		mMessageSprite;
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