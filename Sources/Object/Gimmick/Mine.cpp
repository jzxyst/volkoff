//=============================================================================
/*! 
    @addtogroup 
    @file       Mine.cpp
    @brief      �n���I�u�W�F�N�g
    
    Mine�N���X�̎���
    
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
#include "./Mine.h"
#include "./../../Game/GameManager.h"
#include "./../Player.h"
#include "./../../Effect/Effect_1.h"
#include "./../attackedobject.h"


//---------------------------------------------------------------------------
/*! 
	@brief Mine::Mine

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Mine::Mine()
{
	this->m_bActive = false;
	this->m_bStart = false;
	this->m_nAnime = 0;
	this->m_nEnemyNum = 0;
	this->m_nFrame = 0;
}


//---------------------------------------------------------------------------
/*! 
	@brief Mine::~Mine

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Mine::~Mine()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Mine::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Mine::Initialize()
{
	this->Release();

	this->mPanel = LBatchPanel::create(20.0f,20.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->setCenterPoint(-10, 10, 0);
	this->mPanel->setTexture(Assets::loadTexture(g_szMineFilePath));
	this->mPanel->setPosition(this->mPosition);
	this->mPanel->setVisible(true);

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Mine::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Mine::Release()
{
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Mine::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Mine::Update()
{
	++this->m_nFrame;
	this->mPanel->setPosition(this->mPosition);

	//���������i�K���j//�㉺����200�ȉ� ���� ���E����10�ȉ�
	const int y = 20;
	const int x = 6;
	LVector3 myPos = this->mPosition;
	myPos.x += 10;
	//myPos.y -= 50;
	if(::abs(GameManager::getInstance()->getPlayer()->getPosition().y - myPos.y) <= y && abs(myPos.x - GameManager::getInstance()->getPlayer()->getPosition().x) <= x && !this->m_bStart)
	{
		LVector3 v(this->mPosition);
		v.z = 0.f;
		new Effect_Explosion(v);
		this->m_bStart = true;

		//�_���[�W��^�������ꍇ�͂����ɏ���
		GameManager::getInstance()->getPlayer()->attackEffect(GameManager::getInstance()->getPlayer(),100,1,1,LVector3(0,6,0),65);
		GameAudio::playSE("./Data/Sound/SE/Explosion01.ogg",0.50,1.30);
		//�����܂�

		GameObjectManager::getInstance()->deleteObject(this);
	}

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Mine::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Mine::HandleEvent(u32 event_,void *args_)
{
	return true;
}


//=============================================================================
//								End of File
//=============================================================================