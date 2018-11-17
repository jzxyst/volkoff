//=============================================================================
//【 SceneRanking 】
//-----------------------------------------------------------------------------
///**
//  @file       SceneRanking.h
//  @brief      SceneRanking
//  @author     yama
//*/
//=============================================================================

#pragma once

#if MIGRATION
#else
#include "../Frontend/RankingNameplate.h"
#endif

#define MAX_RANKING_NUM 8	// ランクイン数

//=============================================================================
// ■ SceneRanking クラス
//-----------------------------------------------------------------------------
///**
//  @brief		ランキング画面
//*/
//=============================================================================
class SceneRanking : public LGameScene
{
public:

    /// シーン名
    virtual const char* getSceneName() { return "SceneRanking"; }

	/// 開始処理
	virtual void onStart();

    /// フレーム更新
	virtual void onUpdate();

    /// 終了処理
	virtual void onTerminate();

private:

	

    int         mPhase;
    int         mFrameCount;


	LTexture	mRankingTexture;

    LSprite     mBGWhiteSprite;
    LSprite     mWeaponSprite;

#if MIGRATION
#else
	RankingNameplate	mRankingNameplate[MAX_RANKING_NUM];
#endif
};

//=============================================================================
//								end of file
//=============================================================================