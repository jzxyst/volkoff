//=============================================================================
/*! 
    @addtogroup 
    @file       GateKey.cpp
    @brief     ���I�u�W�F�N�g
    
    GateKey�N���X�̎���
    
    @attention  -
    @note       -
    @author     matsui
    @date       2011/10/27
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/27 matsui
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "./Key.h"



//---------------------------------------------------------------------------
/*! 
	@brief GateKey::GateKey

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
GateKey::GateKey()
    : mGuideNamePlate   ( NULL )
{
	mColRect.set( mPosition.x, mPosition.y, 40*mScale.x, 40*mScale.y );
}


//---------------------------------------------------------------------------
/*! 
	@brief GateKey::~GateKey

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
GateKey::~GateKey()
{
	this->Release();
}


void GateKey::setExit( bool f_ )
{
    GameObject::setExit( f_ );
}


//---------------------------------------------------------------------------
/*! 
	@brief GateKey::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ��
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool GateKey::Initialize()
{
	this->Release();
	this->mScore = 500; 
	this->mPanel = LBatchPanel::create(40.0f,40.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->setCenterPoint(-20, 20, 0);
	this->mPanel->setTexture(Assets::loadTexture(g_szKeyFilePath));
	this->mPanel->setPosition(this->mPosition);
	this->mPanel->setVisible(true);


    mGuideNamePlate = NEW GuideNamePlate();
    mGuideNamePlate->initialize( this, 1, 20, 0 );

    //printf( "�� key h:%d p:%p\n", this->getHandle(), this );
         
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief GateKey::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool GateKey::Release()
{
    SAFE_DELETE( mGuideNamePlate );
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief GateKey::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool GateKey::Update()
{
	this->mPanel->setPosition(this->mPosition);

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief GateKey::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int GateKey::HandleEvent(u32 event_,void *args_)
{
	return true;
}

//
// GateKey::getBoundingRect
//
// �דc�ǉ��E�����蔻���Ԃ�
//
const LRect* GateKey::getBoundingRect()
{
	mColRect.set( mPosition.x, mPosition.y, 40*mScale.x, 40*mScale.y );

	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================