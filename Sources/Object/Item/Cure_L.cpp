//=============================================================================
/*! 
    @addtogroup 
    @file       Cure_L.cpp
    @brief     �񕜁@(��)�I�u�W�F�N�g
    
    Cure_L�N���X�̎���
    
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
#include "./Cure_L.h"


//---------------------------------------------------------------------------
/*! 
	@brief Cure_L::Cure_L

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Cure_L::Cure_L()
    : mGuideNamePlate   ( NULL )
{
	this->mColRect.Set(
		this->mPosition.x+( 11 * this->mScale.x ),
		this->mPosition.y, ( 19 * this->mScale.x ) + ( 11 * this->mScale.x ),
		34 * this->mScale.y );
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_L::~Cure_L

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Cure_L::~Cure_L()
{
    
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_L::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Cure_L::Initialize()
{
	this->Release();
	this->mScore = 1000;
	this->mPanel = Sprite3D::Create(40.0f,40.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->SetCenter(-20, 20, 0);
	this->mPanel->SetTexture(Assets::LoadTexture(g_szCure_LFilePath));
	this->mPanel->SetPosition(this->mPosition);
	this->mPanel->SetVisible(true);

    mGuideNamePlate = NEW GuideNamePlate();
    mGuideNamePlate->initialize( this, 1, 20, 0 );

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_L::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Cure_L::Release()
{
    SAFE_DELETE( mGuideNamePlate );
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_L::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Cure_L::Update()
{
	this->mPanel->SetPosition(this->mPosition);

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_L::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Cure_L::HandleEvent(u32 event_,void *args_)
{
	return true;
}

//
// Ladder::getBoundingRect
//
// �דc�ǉ��E�����蔻���Ԃ�
//
const LRect* Cure_L::getBoundingRect()
{
	this->mColRect.Set(
		this->mPosition.x+( 11 * this->mScale.x ),
		this->mPosition.y, ( 19 * this->mScale.x ) + ( 11 * this->mScale.x ),
		34 * this->mScale.y );

	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================