//=============================================================================
/*! 
    @addtogroup 
    @file       Duct.cpp
    @brief      �_�N�g�I�u�W�F�N�g
    
    Duct�N���X�̒�`
    
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
#include "./Duct.h"
#include "./../../Game/GameManager.h"
#include "./../Player.h"
#include "./../Enemy.h"


//---------------------------------------------------------------------------
/*! 
	@brief Duct::Duct

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Duct::Duct()
{
	this->m_bActive = false;
	this->m_bStart = false;
	this->m_nAnime = 0;
	this->m_nEnemyNum = 0;
	this->m_nFrame = 0;
}


//---------------------------------------------------------------------------
/*! 
	@brief Duct::~Duct

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Duct::~Duct()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Duct::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Duct::Initialize()
{
	this->Release();

	this->mPanel = LBatchPanel::create(100.0f,80.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->SetCenter(-50, 40, 0);
	this->mPanel->SetTexture(Assets::loadTexture(g_szDuctFilePath));
	this->mPanel->setSourceRect(LRect(0,0,100,80));
	this->mPanel->SetPosition(this->mPosition);
	this->mPanel->SetVisible(true);

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Duct::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Duct::Release()
{
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Duct::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Duct::Update()
{
	++this->m_nFrame;
	this->mPanel->SetPosition(this->mPosition);

	//���������i�K���j//�㉺����200�ȉ� ���� ���E����10�ȉ�
	const int y = 150;
	const int x = 100;
	LVector3 myPos = this->mPosition;
	myPos.x += 50;
	myPos.y -= 100;
	if(abs(myPos.y - GameManager::getInstance()->getPlayer()->getPosition().y) <= y && abs(myPos.x - GameManager::getInstance()->getPlayer()->getPosition().x) <= x && this->m_bActive && !this->m_bStart)
	{
		//GameAudio::PlaySE("./Data/Sound/SE/manhole03.wav",100,180);
		GameAudio::PlaySE("./Data/Sound/SE/manhole02.wav",1.00,1.80);
		GameAudio::PlaySE("./Data/Sound/SE/manhole01.wav",1.00,1.60);
		this->m_bStart = true;
	}

	if(this->m_bActive)
	{
		if(this->m_bStart)
		{
			//���A�j���[�V����
			if(this->m_nAnime < 5)
			{
				this->m_nAnime++;
				this->mPanel->setSourceRect(LRect(this->m_nAnime * 100,0,100,80));
			}

			//�G�o��
			if(!(this->m_nFrame % 6)) //2�t���[����1��
			{
				if(this->m_nEnemyNum)
				{
					Enemy* pEnemy = Enemy::createRandom();
					pEnemy->setPosition(LVector3(this->mPosition.x + 62,this->mPosition.y - 100,this->mPosition.z));
					pEnemy->setDefPosition(LVector3(this->mPosition.x + 62,this->mPosition.y - 100,this->mPosition.z));
					pEnemy->setVelocity(LVector3(::rand() % 10 - 5,0,0));

					this->m_nEnemyNum -= 1;
				}
			}
		}

	}

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Duct::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Duct::HandleEvent(u32 event_,void *args_)
{
	return true;
}



//=============================================================================
//								End of File
//=============================================================================