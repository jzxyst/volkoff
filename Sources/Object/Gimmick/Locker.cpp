//=============================================================================
/*! 
    @addtogroup 
    @file       Locker.cpp
    @brief      ���b�J�[�I�u�W�F�N�g
    
    Locker�N���X�̎���
    
    @attention  -
    @note       -
    @author     matsui
    @date       2011/11/2
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/11/2 matsui
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "./Locker.h"
#include "./../../Game/GameManager.h"
#include "./../Player.h"
#include "./../Enemy.h"


//---------------------------------------------------------------------------
/*! 
	@brief Locker::Locker

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Locker::Locker()
{
	this->m_bActive = false;
	this->m_bStart = false;
	this->m_nAnime = 0;
	this->m_nEnemyNum = 0;
	this->m_nFrame = 0;
}


//---------------------------------------------------------------------------
/*! 
	@brief Locker::~Locker

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Locker::~Locker()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Locker::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Locker::Initialize()
{
	this->Release();

	this->mPanel = LBatchPanel::create(80.0f,80.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->setCenterPoint(-40, 40, 0);
	this->mPanel->setTexture(Assets::loadTexture(g_szLockerFilePath));
	this->mPanel->setSourceRect(LRect(0,0,80,80));
	this->mPanel->setPosition(this->mPosition);
	this->mPanel->setVisible(true);

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Locker::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Locker::Release()
{
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Locker::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Locker::Update()
{
	++this->m_nFrame;
	this->mPanel->setPosition(this->mPosition);

	//���������i�K���j//�㉺����200�ȉ� ���� ���E����150�ȉ�
	const int y = 80;
	const int x = 150;
	LVector3 myPos = this->mPosition;
	myPos.x += 50;
	if(abs(myPos.y - GameManager::getInstance()->getPlayer()->getPosition().y) <= y && abs(myPos.x - GameManager::getInstance()->getPlayer()->getPosition().x) <= x && this->m_bActive && !this->m_bStart)
	{
		//Enemy *pEnemy = NULL;
		//for(int i = 0;i < this->m_nEnemyNum;++i)
		//{
		//	pEnemy = Enemy::create(NULL);
		//	pEnemy->setPosition(LVector3(this->getPosition().x + 62,this->getPosition().y - 80,this->getPosition().z));
		//	pEnemy->setVelocity(LVector3(::rand() % 10 - 5,0,0));
		//}

		GameAudio::playSE("./Data/Sound/SE/doorclose2.wav",1.00,0.60);
		GameAudio::playSE("./Data/Sound/SE/doorclose2.wav",1.00,1.00);
		this->m_bStart = true;
	}

	if(this->m_bActive)
	{
		if(this->m_bStart)
		{
			//�A�j���[�V����
			if(this->m_nAnime < 4)
			{
				this->m_nAnime++;
				this->mPanel->setSourceRect(LRect(this->m_nAnime * 80,0,80,80));
			}

			//�G�o��
			if(this->m_nFrame % 2) //2�t���[����1��
			{
				if(this->m_nEnemyNum)
				{
					Enemy* pEnemy = Enemy::createRandom();
					pEnemy->setPosition(LVector3(this->mPosition.x + 25,this->mPosition.y - 75,this->mPosition.z));
					pEnemy->setDefPosition(LVector3(this->mPosition.x + 25,this->mPosition.y - 75,this->mPosition.z));
					pEnemy->setVelocity(LVector3(::rand() % 2 - 1,0,0));
                    Enemy::CreateData data;

					this->m_nEnemyNum -= 1;
				}
			}
		}
	}

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Locker::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Locker::HandleEvent(u32 event_,void *args_)
{
	return true;
}


//=============================================================================
//								End of File
//=============================================================================
