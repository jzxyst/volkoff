//=============================================================================
/*! 
    @addtogroup 
    @file       Cure_M.cpp
    @brief     �񕜁@(��)�I�u�W�F�N�g
    
    Cure_M�N���X�̎���
    
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
#include "./Cure_M.h"


//---------------------------------------------------------------------------
/*! 
	@brief Cure_M::Cure_M

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Cure_M::Cure_M()
    : mGuideNamePlate   ( NULL )
{
	mColRect.Set( mPosition.x+(13*mScale.x), mPosition.y, (15*mScale.x)+(13*mScale.x), 27*mScale.y );
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_M::~Cure_M

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Cure_M::~Cure_M()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_M::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Cure_M::Initialize()
{
	this->Release();
	this->mScore = 500;
	this->mPanel = LBatchPanel::create(40.0f,40.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->SetCenter(-20, 20, 0);
	this->mPanel->SetTexture(Assets::loadTexture(g_szCure_MFilePath));
	this->mPanel->SetPosition(this->mPosition);
	this->mPanel->SetVisible(true);

    mGuideNamePlate = NEW GuideNamePlate();
    mGuideNamePlate->initialize( this, 1, 20, 0 );

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_M::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Cure_M::Release()
{
    SAFE_DELETE( mGuideNamePlate );
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_M::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Cure_M::Update()
{
	this->mPanel->SetPosition(this->mPosition);

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_M::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Cure_M::HandleEvent(u32 event_,void *args_)
{
	return true;
}

//
// Cure_M::getBoundingRect
//
// �דc�ǉ��E�����蔻���Ԃ�
//
const LRect* Cure_M::getBoundingRect()
{
	mColRect.Set( mPosition.x+(13*mScale.x), mPosition.y, (15*mScale.x)+(13*mScale.x), 27*mScale.y );

	return &mColRect;
}



//=============================================================================
//								End of File
//=============================================================================