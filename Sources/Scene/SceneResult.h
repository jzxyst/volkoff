//=============================================================================
//�y SceneResult �z
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

/// Main.cpp �̃C�x���g���X�i�[���� onKeyEvent() ���Ăяo�����߂ɗp�ӁBSceneResult �����݂��Ă��Ȃ���� NULL�B�����������Ƃ�������ˁc
extern SceneResult* gSceneResult;

//=============================================================================
// �� SceneResult �N���X
//-----------------------------------------------------------------------------
///**
//  @brief		���U���g���
//*/
//=============================================================================
class SceneResult : public LGameScene
{
public:

    /// �R���X�g���N�^ (�v���C���[���Ō�ɑ������Ă�������ԍ���n��)
    SceneResult( int weapon_no_ )
        : mWeaponNo ( weapon_no_ )
    {
		memset( mRankingName, 0, sizeof(mRankingName) );
	}

public:

    /// �V�[����
    virtual const char* getSceneName() { return "SceneResult"; }

	/// �J�n����
	virtual void onStart();

    /// �t���[���X�V
	virtual void onUpdate();

    /// �I������
	virtual void onTerminate();

	/// Main.cpp �̃C�x���g���X�i�[����Ă΂��
	void onkeyEvent( char code_ );

private:

	static const int MAX_RANKING_NAME_LEN = 10;

	int			mScore;
	int			mTime;		// (�X�R�A�l)
	int			mRank;		// (�X�R�A�l)
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