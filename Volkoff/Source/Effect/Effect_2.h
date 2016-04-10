//=============================================================================
//�y Effect_2 �z
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
// �� Effect_ValfirleDead �N���X
//-----------------------------------------------------------------------------
///**
//  @brief		Valfirle ��|�������̃G�t�F�N�g
//*/
//=============================================================================
class Effect_ValfirleDead
    : public EffectBase
{
public:

	/// �R���X�g���N�^
    Effect_ValfirleDead( const LVector3& pos_ );

    /// �f�X�g���N�^
    ~Effect_ValfirleDead();

public:

    /// �t���[���X�V (false ��Ԃ��Ɖ������)
    virtual bool update();

private:

    int             mFrameCount;
    LPanel          mLinePanels[ 4 ];
#if MIGRATION
#else
    LParticle       mParticle;
    LParticle       mFirstParticle;
#endif

};



//=============================================================================
//								end of file
//=============================================================================