//=============================================================================
/*! 
    @addtogroup 
    @file       Box.cpp
    @brief     ���I�u�W�F�N�g
    
    Box�N���X�̎���
    
    @attention  -
    @note       -
    @author     matsui
    @date       2011/10/26
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/26 matsui
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "./Box.h"
#include "./../Weapon.h"
#include "./../Player.h"
#include "./../../Game/GameManager.h"

//---------------------------------------------------------------------------
/*! 
	@brief Box::Box

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Box::Box()
{
	// �U���ΏۃO���[�v�͓G��
    setAttackedGroup( ATKGROUP_ENEMY );
	mColRect.Set( mPosition.x+20, mPosition.y-20, 60*mScale.x, 60*mScale.y );
}


//---------------------------------------------------------------------------
/*! 
	@brief Box::~Box

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Box::~Box()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Box::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Box::Initialize()
{
	this->Release();

	this->mPanel = Sprite3D::Create(100.0f,80.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->SetCenter(-50, 40, 0);
	this->mPanel->SetTexture(Assets::LoadTexture(g_szBoxFilePath));
	this->mPanel->SetSrcRect(LRect(0,0,100,80));
	this->mPanel->SetPosition(this->mPosition);
	this->mPanel->SetVisible(true);

	this->mLife = 1;
	this->m_nAnime = 0;
	this->m_nFrame = 0;
	this->m_bCreate = false;
	this->mScore = 500;

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Box::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Box::Release()
{
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Box::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Box::Update()
{
	if ( this->mLife > 0 )
	{
		this->mPanel->SetPosition(this->mPosition);
	}



	if ( this->mLife <= 0)
	{
		this->mLife = 0;
		this->m_nFrame++;
		if(m_nFrame==1)
		{
			GameAudio::PlaySE("./Data/Sound/SE/don01.wav",0.50,1.70);
			GameAudio::PlaySE("./Data/Sound/SE/don01.wav",0.50,1.20);
			GameManager::getInstance()->setScore(GameManager::getInstance()->getScore()+(this->getScore()*(GameManager::getInstance()->getFloorNum()+1)*GameManager::getInstance()->getPlayer()->getLife()*((GameManager::getInstance()->getRank()+1)*2))); 
    
		}
		if(m_nFrame%2==0)
		{
			this->m_nAnime++;
			this->mPanel->SetSrcRect(LRect(this->m_nAnime * 100,0,100,80));
		}

		if(m_nAnime >=5)
		{
			this->setExit( true );
		}
		
	}

	//�A�C�e�����o��
	if ( this->mLife <= 0 && !this->m_bCreate)
	{
		// �o�����̑��a
		int rate_max = 0;
		for ( int i = 0; i < WEAPON_NORMAL_MAX_NUM; ++i )
		{
			if ( gWeaponBaseData[ i ].BoxRate )
			{
				rate_max += gWeaponBaseData[ i ].BoxRate;
			}
		}

		// �l���ЂƂ��߂�
		int value = rand() % rate_max;

		// �l�ɑΉ����镐���T��
		int i = 0;
		for ( ; 0 < WEAPON_NORMAL_MAX_NUM; ++i )
		{
			int rating = gWeaponBaseData[ i ].BoxRate;
			if ( rating > 0 )
			{
				if ( rating > value )
				{
					break;
				}
				value -= rating;
			}
		}

		if(i)
		{
			Weapon::CreateData wdata;

			wdata.Data.WeaponType  = static_cast<WeaponType>(i);
			wdata.Data.UseCount    = gWeaponBaseData[i].UseCount;

			LVector3 v = this->mPosition;
			//v.y += 100;
			wdata.Position = v;
			Weapon::create( &wdata );
		}

		this->m_bCreate = true;
	}

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Box::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Box::HandleEvent(u32 event_,void *args_)
{
	AttackedObject::HandleEvent( event_, args_ );

    switch ( event_ )
	{
		case EV_APPLY_DAMAGE:
			// �_���[�W�󂯂���
			this->mLife -= 50;
			break;
	}

	//if ( this->mLife <= 0 )
	//{
	//	this->mLife = 0;
	//		this->setExit( true );
	//		return true;
	//}

	return true;
}

//
// Box::getBoundingRect
//
// �דc�ǉ��E�����蔻���Ԃ�
//
const LRect* Box::getBoundingRect()
{
	mColRect.Set( mPosition.x+20, mPosition.y-20, 60*mScale.x, 60*mScale.y );

	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================