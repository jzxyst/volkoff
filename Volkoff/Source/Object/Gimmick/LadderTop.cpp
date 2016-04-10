//=============================================================================
/*! 
    @addtogroup 
    @file       LadderTop.cpp
    @brief      �͂����I�u�W�F�N�g
    
    LadderTop�N���X�̎���
    
    @attention  -
    @note       -
    @author     matsui
    @date       2011/10/19
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/19 matsui
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include "./LadderTop.h"


//---------------------------------------------------------------------------
/*! 
	@brief LadderTop::LadderTop

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
LadderTop::LadderTop()
{
	mColRect.Set( mPosition.x, mPosition.y, 60*mScale.x, 40*mScale.y );
}


//---------------------------------------------------------------------------
/*! 
	@brief LadderTop::~LadderTop

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
LadderTop::~LadderTop()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief LadderTop::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool LadderTop::Initialize()
{
	this->Release();

	this->mPanel = Sprite3D::Create(60.0f,20.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->SetCenter(-30, 10, 0);
	this->mPanel->SetTexture(Assets::LoadTexture("./Data/Graphics/Object/Ladder.png"));
	this->mPanel->SetPosition(this->mPosition);
	this->mPanel->SetVisible(true);

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief LadderTop::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool LadderTop::Release()
{
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief LadderTop::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool LadderTop::Update()
{
	this->mPanel->SetPosition(this->mPosition);

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief LadderTop::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int LadderTop::HandleEvent(u32 event_,void *args_)
{
	return true;
}

//
// LadderTop::getBoundingRect
//
// �דc�ǉ��E�����蔻���Ԃ�
//
const LRect* LadderTop::getBoundingRect()
{
	mColRect.Set( mPosition.x, mPosition.y, 60*mScale.x, 40*mScale.y );

	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================