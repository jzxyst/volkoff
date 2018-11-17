//=============================================================================
//�y SceneRanking �z
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

#define MAX_RANKING_NUM 8	// �����N�C����

//=============================================================================
// �� SceneRanking �N���X
//-----------------------------------------------------------------------------
///**
//  @brief		�����L���O���
//*/
//=============================================================================
class SceneRanking : public LGameScene
{
public:

    /// �V�[����
    virtual const char* getSceneName() { return "SceneRanking"; }

	/// �J�n����
	virtual void onStart();

    /// �t���[���X�V
	virtual void onUpdate();

    /// �I������
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