//=============================================================================
/*! 
    @addtogroup 
    @file       Exit.cpp
    @brief      �o���I�u�W�F�N�g
    
    Exit�N���X�̒�`
    
    @attention  -
    @note       -
    @author     matui
    @date       2011/11/25
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/11/25 matsui
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "./Exit.h"


//---------------------------------------------------------------------------
/*! 
	@brief Exit::Exit

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Exit::Exit()
    : mGuideNamePlate   ( NULL )
{
	mColRect.Set( mPosition.x+40, mPosition.y, 60*mScale.x, 80*mScale.y );
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit::~Exit

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Exit::~Exit()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Exit::Initialize()
{
	this->Release();

	this->mPanel = LBatchPanel::create(140.0f,80.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->SetCenter(-70, 40, 0);
	this->mPanel->SetTexture(Assets::loadTexture(g_szExitFilePath));
	this->mPanel->setSourceRect(LRect(0,0,140,80));
	this->mPanel->SetPosition(this->mPosition);
	this->mPanel->SetVisible(true);

    mGuideNamePlate = NEW GuideNamePlate();
    mGuideNamePlate->initialize( this, 2, 70, 20 );

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Exit::Release()
{
    SAFE_DELETE( mGuideNamePlate );
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Exit::Update()
{
	this->mPanel->SetPosition(this->mPosition);

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Exit::HandleEvent(u32 event_,void *args_)
{
	return true;
}
const LRect* Exit::getBoundingRect()
{
	mColRect.Set( mPosition.x+40, mPosition.y, 60*mScale.x, 80*mScale.y );

	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================