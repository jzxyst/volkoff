//=============================================================================
//【 Effect_2 】
//-----------------------------------------------------------------------------
///**
//  @file       Effect_2.h
//  @brief      Effect_2
//  @author     yama
//*/
//=============================================================================

#pragma once

#include "EffectBase.h"

//=============================================================================
// ■ Effect_ValfirleDead クラス
//-----------------------------------------------------------------------------
///**
//  @brief		Valfirle を倒した時のエフェクト
//*/
//=============================================================================
class Effect_ValfirleDead
    : public EffectBase
{
public:

	/// コンストラクタ
    Effect_ValfirleDead( const LVector3& pos_ );

    /// デストラクタ
    ~Effect_ValfirleDead();

public:

    /// フレーム更新 (false を返すと解放する)
    virtual bool update();

private:

    int             mFrameCount;
    Ref<LPanel>          mLinePanels[ 4 ];
#if MIGRATION
#else
    LParticle       mParticle;
    LParticle       mFirstParticle;
#endif

};



//=============================================================================
//								end of file
//=============================================================================
