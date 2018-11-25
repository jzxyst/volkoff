//=============================================================================
/*! 
    @addtogroup 
    @file       Ladder.cpp
    @brief      �͂����I�u�W�F�N�g
    
    Ladder�N���X�̎���
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/19
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/19 Hi-ra Mizuo
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "./Ladder.h"


//---------------------------------------------------------------------------
/*! 
	@brief Ladder::Ladder

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Ladder::Ladder()
{
	mColRect.set( mPosition.x, mPosition.y, 60*mScale.x, 40*mScale.y );
}


//---------------------------------------------------------------------------
/*! 
	@brief Ladder::~Ladder

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Ladder::~Ladder()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Ladder::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Ladder::Initialize()
{
	this->Release();

	this->mPanel = LBatchPanel::create(60.0f,20.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->setCenterPoint(-30, 10, 0);
	this->mPanel->setTexture(Assets::loadTexture(g_szLaderFilePath));
	this->mPanel->setPosition(this->mPosition);
	this->mPanel->setVisible(true);




	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Ladder::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Ladder::Release()
{
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Ladder::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Ladder::Update()
{
	this->mPanel->setPosition(this->mPosition);

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Ladder::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Ladder::HandleEvent(u32 event_,void *args_)
{
	return true;
}

//
// Ladder::getBoundingRect
//
// �דc�ǉ��E�����蔻���Ԃ�
//
const LRect* Ladder::getBoundingRect()
{
	mColRect.set( mPosition.x, mPosition.y, 60*mScale.x, 40*mScale.y );

	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================