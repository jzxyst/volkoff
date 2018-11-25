//=============================================================================
/*! 
    @addtogroup 
    @file       Exit_Lock.cpp
    @brief      ���t���o���I�u�W�F�N�g
    
    Exit_Lock�N���X�̒�`
    
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
#include "./Exit_Lock.h"
#include "./../GameObjectManager.h"
#include "./../../Game/GameManager.h"
#include "./../../Map/MapManager.h"
//---------------------------------------------------------------------------
/*! 
	@brief Exit_Lock::Exit_Lock

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Exit_Lock::Exit_Lock()
    : mGuideNamePlate   ( NULL )
{
	mColRect.set( mPosition.x+40, mPosition.y, 60*mScale.x, 80*mScale.y );
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit_Lock::~Exit_Lock

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Exit_Lock::~Exit_Lock()
{

	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit_Lock::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Exit_Lock::Initialize()
{
	this->Release();

	this->mPanel = LBatchPanel::create(140.0f,80.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->setCenterPoint(-70, 40, 0);
	this->mPanel->setTexture(Assets::loadTexture(g_szExit_LockFilePath));
	this->mPanel->setSourceRect(LRect(0,0,140,80));
	this->mPanel->setPosition(this->mPosition);
	this->mPanel->setVisible(true);
	this->mFlameCnt = 0;
    mGuideNamePlate = NEW GuideNamePlate();
    mGuideNamePlate->initialize( this, 2, 70, 20 );

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit_Lock::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Exit_Lock::Release()
{
    SAFE_DELETE( mGuideNamePlate );
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit_Lock::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Exit_Lock::Update()
{
	this->mPanel->setPosition(this->mPosition);

	if(GameManager::getInstance()->getOpenflag())
	{
		mFlameCnt++;

     
        if(mFlameCnt ==10)
		{
			Accessor::ToneLayer->ChangeTone(ToneF(-1, -1, -1, 0), 15.f / 60);
        }

		if(mFlameCnt ==15)
		{
			GameAudio::playSE("./Data/Sound/SE/doorclose2.wav",1.00,1.00);
			GameAudio::playSE("./Data/Sound/SE/doorclose3.wav",0.90,0.80);


            
            
		}
		if((mFlameCnt>=15)&&(mFlameCnt <=21))
		{
			this->mPanel->setSourceRect(LRect((this->mFlameCnt-15) * 140,0,140,80));
		}
		if(mFlameCnt == 25)
		{
// �R���e�B�j���[�ɔ����ăo�b�N�A�b�v�����
                GameManager::getInstance()->commit();
			GameManager::getInstance()->setOpenflag(0);
			GameManager::getInstance()->setKeyflag(0);
			GameObjectManager::getInstance()->deleteStageObject();
			GameManager::getInstance()->NextFloor();
            
			MapManager::getInstance()->changeMap(GameManager::getInstance()->getFloorNum());	
		}
	}

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit_Lock::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Exit_Lock::HandleEvent(u32 event_,void *args_)
{
	return true;
}

const LRect* Exit_Lock::getBoundingRect()
{
	mColRect.set( mPosition.x+40, mPosition.y, 60*mScale.x, 80*mScale.y );

	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================
