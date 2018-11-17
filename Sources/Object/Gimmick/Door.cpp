//=============================================================================
/*! 
    @addtogroup 
    @file       Door.cpp
    @brief      �h�A�I�u�W�F�N�g
    
    Door�N���X�̒�`
    
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
#include "./Door.h"
#include "./../../Game/GameManager.h"
#include "./../Player.h"
#include "./../Enemy.h"


//---------------------------------------------------------------------------
/*! 
	@brief Door::Door

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Door::Door()
{
	this->m_bActive = false;
	this->m_bStart = false;
	this->m_nAnime = 0;
	this->m_nEnemyNum = 0;
	this->m_nFrame = 0;
}


//---------------------------------------------------------------------------
/*! 
	@brief Door::~Door

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Door::~Door()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Door::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Door::Initialize()
{
	this->Release();

	this->mPanel = Sprite3D::Create(140.0f,80.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->SetCenter(-70, 40, 0);
	this->mPanel->SetTexture(Assets::LoadTexture(g_szDoorFilePath));
	this->mPanel->SetSrcRect(LRect(0,0,140,80));
	this->mPanel->SetPosition(this->mPosition);
	this->mPanel->SetVisible(true);

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Door::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Door::Release()
{
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Door::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Door::Update()
{
	++this->m_nFrame;
	this->mPanel->SetPosition(this->mPosition);

	//���������i�K���j//�㉺����200�ȉ� ���� ���E����10�ȉ�
	const int y = 100;
	const int x = 200;
	LVector3 myPos = this->mPosition;
	myPos.x += 50;
	if(abs(myPos.y - GameManager::getInstance()->getPlayer()->getPosition().y) <= y && abs(myPos.x - GameManager::getInstance()->getPlayer()->getPosition().x) <= x && this->m_bActive && !this->m_bStart)
	{
		GameAudio::PlaySE("./Data/Sound/SE/doorclose2.wav",1.00,1.00);
		GameAudio::PlaySE("./Data/Sound/SE/doorclose3.wav",0.90,0.80);
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
				this->mPanel->SetSrcRect(LRect(this->m_nAnime * 140,0,140,80));
			}

			//�G�o��
			if(!(this->m_nFrame % 6)) //2�t���[����1��
			{
				if(this->m_nEnemyNum)
				{
					//Weapon::CreateData wdata2;
					//wdata2.Data.WeaponType  = WEAPON_STICK;
					//wdata2.Data.UseCount    = 30;
					//wdata2.Position         = LVector3(this->mPosition.x + 62 + ::rand() % 40 - 20,this->mPosition.y,this->mPosition.z);
					//Weapon* test_weapon2 = Weapon::create( &wdata2 );

					//Enemy *pEnemy = Enemy::create(NULL);
					//pEnemy->setPosition(LVector3(this->mPosition.x + 62,this->mPosition.y - 80,this->mPosition.z));
					//pEnemy->setVelocity(LVector3(::rand() % 10 - 5,0,0));

					Enemy* pEnemy = Enemy::createRandom();
					pEnemy->setPosition(LVector3(this->mPosition.x + 62,this->mPosition.y - 80,this->mPosition.z));
					pEnemy->setDefPosition(LVector3(this->mPosition.x + 62,this->mPosition.y - 80,this->mPosition.z));
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
	@brief Door::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Door::HandleEvent(u32 event_,void *args_)
{
	return true;
}



//=============================================================================
//								End of File
//=============================================================================