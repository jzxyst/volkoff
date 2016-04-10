//=============================================================================
/*! 
    @addtogroup 
    @file       Cure_S.cpp
    @brief     �񕜁@(��)�I�u�W�F�N�g
    
    Cure_S�N���X�̎���
    
    @attention  -
    @note       -
    @author     matsui
    @date       2011/10/31
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/31 matsui
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include "./Cure_S.h"


//---------------------------------------------------------------------------
/*! 
	@brief Cure_S::Cure_S

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Cure_S::Cure_S()
    : mGuideNamePlate   ( NULL )
{
	mColRect.Set( mPosition.x+(16*mScale.x), mPosition.y, (9*mScale.x)+(16*mScale.x), 21*mScale.y );
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_S::~Cure_S

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Cure_S::~Cure_S()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_S::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Cure_S::Initialize()
{
	this->Release();
	this->mScore = 200;
	this->mPanel = Sprite3D::Create(40.0f,40.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->SetCenter(-20, 20, 0);
	this->mPanel->SetTexture(Assets::LoadTexture(g_szCure_SFilePath));
	this->mPanel->SetPosition(this->mPosition);
	this->mPanel->SetVisible(true);

    mGuideNamePlate = NEW GuideNamePlate();
    mGuideNamePlate->initialize( this, 1, 20, 0 );

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_S::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Cure_S::Release()
{
    SAFE_DELETE( mGuideNamePlate );
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_S::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Cure_S::Update()
{
	this->mPanel->SetPosition(this->mPosition);

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_S::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Cure_S::HandleEvent(u32 event_,void *args_)
{
	return true;
}

//
// Ladder::getBoundingRect
//
// �דc�ǉ��E�����蔻���Ԃ�
//
const LRect* Cure_S::getBoundingRect()
{
	mColRect.Set( mPosition.x+(16*mScale.x), mPosition.y, (9*mScale.x)+(16*mScale.x), 21*mScale.y );

	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================